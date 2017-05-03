#pragma once
#include "../Error.h"
#include "../Meta.h"
#include <algorithm>
#include <boost/hana.hpp>
#include <boost/hana/define_struct.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>
#include <functional>
#include <json.hpp>

namespace gltfpp {
	inline namespace v1 {
		struct glTF;

		struct ParseContext {
			glTF *root = nullptr;
			const nlohmann::json *json = nullptr;
		};

		template <typename T, typename std::enable_if_t<detail::is_field_aggregate<T>>* = nullptr>
		auto parse(T &target);

		template <typename T, typename std::enable_if_t<detail::is_fundamental_json_type<T>>* = nullptr>
		auto parse(T &target);

		template <typename T, typename std::enable_if_t<detail::is_field_list<T>>* = nullptr>
		auto parse(T &target);

		template <typename T>
		auto field(option<T> &target, const char *key) {
			return [&, key](ParseContext ctx) -> gltf_result<ParseContext> {
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
		auto field(T &target, const char *key) {
			return [&, key](ParseContext ctx) -> gltf_result<ParseContext> {
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
		auto aggregate(T &target) {
			return [&](ParseContext ctx) -> gltf_result<ParseContext> {
				constexpr auto accessor = boost::hana::accessors<T>();
				auto names = boost::hana::transform(accessor, boost::hana::first);
				auto members = boost::hana::transform(accessor, boost::hana::second);
				auto refs = boost::hana::transform(members, [&](auto acc) { return std::ref(acc(target)); });

				auto res = boost::hana::fold(
					boost::hana::zip(names, refs), gltf_result<ParseContext>{ctx}, [&](auto c, auto entry) {
						if(!c) {
							return c;	// I hope the optimizer understands that...
						}
						auto name = boost::hana::to<const char *>(entry[boost::hana::size_c<0>]);
						auto &member = entry[boost::hana::size_c<1>].get();
						return c >> field(member, name);
					});
				if(!res) {
					return res;
				}
				return ctx;
			};
		}

		template <typename T, typename std::enable_if_t<detail::is_field_aggregate<T>>*>
		auto parse(T &target) {
			return aggregate(target);
		}

		template <typename T, typename std::enable_if_t<detail::is_fundamental_json_type<T>>*>
		auto parse(T &target) {
			return [&](ParseContext ctx) -> gltf_result<ParseContext> {
				// TODO this is not a complete check
				if(ctx.json) {
					target = ctx.json->template get<T>();
					return ctx;
				}
				return make_unexpected(gltf_error::key_not_found);
			};
		}

		template <typename T, typename std::enable_if_t<detail::is_field_list<T>>*>
		auto parse(T &target) {
			return [&](ParseContext ctx) -> gltf_result<ParseContext> {
				if(!ctx.json) {
					return make_unexpected(gltf_error::key_not_found);
				}
				if(!ctx.json->is_array()) {
					return make_unexpected(gltf_error::type_error);
				}

				target.resize(ctx.json->size());

				auto in = ctx.json;
				auto out = target.begin();
				for(; out != target.end(); ++in, ++out) {
					auto res = parse(*out)({ctx.root, in});
					static_assert(std::is_same<gltf_result<ParseContext>, decltype(res)>{},
								  "Return type of the parser function must be gltf_result<ParseContext>");
					if(!res) {
						return res;
					}
				}
				return ctx;
			};
		}

		template<typename String>
		auto is_data_uri(String &&uri) {
			using std::begin;
			using std::end;
			const auto uri_begin = begin(std::forward<String>(uri));
			const auto uri_end = end(std::forward<String>(uri));
			using Result = option<const decltype(uri_begin)>;

			constexpr char expected_prefix[] = "data:";
			const auto prefixMatch = std::mismatch(begin(expected_prefix), end(expected_prefix), uri_begin);
			if(prefixMatch.first == end(expected_prefix)) {
				return Result{};
			}

			// It probably is a data uri, look for ',' in the entire uri
			auto result = std::find(prefixMatch.second, uri_end, ',');
			if(result == uri_end) {
				return Result{};
			}
			return Result{++result};
		}
		
		template<typename CharInputIterator, typename ByteOutputIterator>
		auto decode_embedded_base64(CharInputIterator first, CharInputIterator last, ByteOutputIterator out) {
			using b64 = boost::archive::iterators::transform_width<boost::archive::iterators::binary_from_base64<std::string::const_iterator>, 8, 6>;
			return std::transform(b64(first), b64(last), out, [](char c) {
				return static_cast<byte>(c);
			});
		}
	}	// namespace v1
}	// namespace gltfpp
