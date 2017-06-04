#pragma once
#include "../Error.h"
#include "../Meta.h"
#include "../detail/Byte.h"
#include "detail/Defaulted.h"
#include <algorithm>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <boost/hana.hpp>
#include <boost/hana/define_struct.hpp>
#include <functional>
#include <json.hpp>

namespace gltfpp {
	inline namespace v1 {
		struct glTF;

		struct ParseContext {
			glTF *root = nullptr;
			nlohmann::json const *json = nullptr;
		};

		template <typename T, typename std::enable_if_t<detail::is_field_aggregate<T>> * = nullptr>
		auto parse(T &target) noexcept;

		template <typename T, typename std::enable_if_t<detail::is_fundamental_json_type<T>> * = nullptr>
		auto parse(T &target) noexcept;

		template <typename T, typename std::enable_if_t<detail::is_field_list<T>> * = nullptr>
		auto parse(T &target) noexcept;

		template <typename T, typename std::enable_if_t<detail::is_enumeration<T>> * = nullptr>
		auto parse(T &target) noexcept;

		template <typename T>
		auto field(option<T> &target, char const *key) noexcept {
			return [&target, key ](ParseContext ctx) noexcept->gltf_result<ParseContext> {
				auto valIt = ctx.json->find(key);
				if(valIt != ctx.json->end()) {
					target.set_value();
					auto newCtx = ParseContext{ctx.root, std::addressof(*valIt)};
					auto res = parse(target.value())(newCtx);
					static_assert(std::is_same<gltf_result<ParseContext>, decltype(res)>{},
								  "Return type of the parser function must be gltf_result<ParseContext>");
				} else {
					target = {};
				}
				return ctx;
			};
		}

		template <typename T>
		auto field(T &target, char const *key) noexcept {
			return [&target, key ](ParseContext ctx) noexcept->gltf_result<ParseContext> {
				auto valIt = ctx.json->find(key);
				if(valIt != ctx.json->end()) {
					auto newCtx = ParseContext{ctx.root, std::addressof(*valIt)};
					auto res = parse(target)(newCtx);
					static_assert(std::is_same<gltf_result<ParseContext>, decltype(res)>{},
								  "Return type of the parser function must be gltf_result<ParseContext>");
					if(!res) {
						return res;
					}
					return ctx;
				}
				return make_unexpected(gltf_error::key_not_found);
			};
		}

		template <typename T>
		auto field(defaulted<T> &target, char const *key) noexcept {
			return [&target, key ](ParseContext ctx) noexcept->gltf_result<ParseContext> {
				auto valIt = ctx.json->find(key);
				if(valIt != ctx.json->end()) {
					auto newCtx = ParseContext{ctx.root, std::addressof(*valIt)};
					auto res = parse(target.value())(newCtx);
					static_assert(std::is_same<gltf_result<ParseContext>, decltype(res)>{},
								  "Return type of the parser function must be gltf_result<ParseContext>");
				}
				// defaulted<T> is forced to be initialized already, just exit if the default is not overwritten
				return ctx;
			};
		}

		template <typename T>
		auto aggregate(T &target) noexcept {
			return [&target](ParseContext ctx) noexcept->gltf_result<ParseContext> {
				using namespace boost::hana;
				constexpr auto accessor = accessors<T>();
				auto names = transform(accessor, first);
				auto members = transform(accessor, second);
				auto refs = transform(members, [&](auto acc) { return std::ref(acc(target)); });

				auto res = fold(zip(names, refs), gltf_result<ParseContext>{ctx}, [&](auto c, auto entry) {
					if(!c) {
						return c;	// I hope the optimizer understands that...
					}
					auto name = to<char const *>(entry[size_c<0>]);
					auto &member = entry[size_c<1>].get();
					return c >> field(member, name);
				});
				if(!res) {
					return res;
				}
				return ctx;
			};
		}

		template <typename T, typename std::enable_if_t<detail::is_field_aggregate<T>> *>
		auto parse(T &target) noexcept {
			return aggregate(target);
		}

		template <typename T, typename std::enable_if_t<detail::is_fundamental_json_type<T>> *>
		auto parse(T &target) noexcept {
			return [&target](ParseContext ctx) noexcept->gltf_result<ParseContext> {
				// TODO avoid catching exception
				try {
					if(ctx.json) {
						target = ctx.json->template get<T>();
						return ctx;
					}
					return make_unexpected(gltf_error::key_not_found);
				}
				catch(const std::domain_error &) {
					return make_unexpected(gltf_error::type_error);
				}
			};
		}

		template <typename T, typename std::enable_if_t<detail::is_field_list<T>> *>
		auto parse(T &target) noexcept {
			return [&target](ParseContext ctx) noexcept->gltf_result<ParseContext> {
				if(!ctx.json) {
					return make_unexpected(gltf_error::key_not_found);
				}
				if(!ctx.json->is_array()) {
					return make_unexpected(gltf_error::type_error);
				}

				target.resize(ctx.json->size());

				auto in = ctx.json->begin();
				auto out = target.begin();
				for(; out != target.end(); ++in, ++out) {
					auto res = parse(*out)({ctx.root, &*in});
					static_assert(std::is_same<gltf_result<ParseContext>, decltype(res)>{},
								  "Return type of the parser function must be gltf_result<ParseContext>");
					if(!res) {
						return res;
					}
				}
				return ctx;
			};
		}

		template <typename T, typename std::enable_if_t<detail::is_enumeration<T>> *>
		auto parse(T &target) noexcept {
			return [&target](ParseContext ctx) noexcept->gltf_result<ParseContext> {
				if(!ctx.json) {
					return make_unexpected(gltf_error::key_not_found);
				}
				auto const str = ctx.json->get<std::string>();
				auto const parsed = T::_from_string_nothrow(str.c_str());
				if(!parsed) {
					return make_unexpected(gltf_error::decode_error);
				}
				target = *parsed;
				return ctx;
			};
		}

		template <typename CharInputIterator, typename ByteOutputIterator>
		auto decode_embedded_base64(CharInputIterator first, CharInputIterator last, ByteOutputIterator out) noexcept {
			using b64 = boost::archive::iterators::transform_width<
				boost::archive::iterators::binary_from_base64<std::string::const_iterator>, 8, 6>;
			return std::transform(b64(first), b64(last), out, [](char c) { return static_cast<byte>(c); });
		}
	}	// namespace v1
}	// namespace gltfpp
