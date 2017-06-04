#pragma once
#define BOOST_OUTCOME_ENABLE_ADVANCED
#include <boost/outcome.hpp>
#include <system_error>

namespace gltfpp {
	inline namespace v1 {
		struct gltf_error : std::error_code {
			enum cases { key_not_found, index_out_of_range, type_error, unimplemented, decode_error };

			gltf_error() = default;
			inline gltf_error(cases error);
		};
	}	// namespace v1
}	// namespace gltfpp

namespace std {
	template <>
	struct is_error_code_enum<gltfpp::gltf_error::cases> : std::true_type {};
}	// namespace std

namespace gltfpp {
	inline namespace v1 {
		namespace detail {
			struct gltf_error_category final : std::error_category {
				char const *name() const noexcept override {
					return "glTF error";
				}

				std::string message(int error) const noexcept override {
					switch(error) {
						case gltf_error::key_not_found:
							return "Key not found";
						case gltf_error::index_out_of_range:
							return "Index out of range";
						case gltf_error::type_error:
							return "Unexpected data type";
						case gltf_error::unimplemented:
							return "glTF Feature is unimplemented";
						case gltf_error::decode_error:
							return "Unexpected input when decoding";
						default:
							return "Unknown Error";
					}
				}

				std::error_condition default_error_condition(int error) const noexcept override {
					switch(error) {
						case gltf_error::key_not_found:
							return std::errc::bad_message;
						case gltf_error::index_out_of_range:
							return std::errc::result_out_of_range;
						case gltf_error::type_error:
							return std::errc::argument_out_of_domain;
						case gltf_error::unimplemented:
							return std::errc::function_not_supported;
						case gltf_error::decode_error:
							return std::errc::bad_message;	// TODO
						default:
							return std::error_condition(error, *this);
					}
				}
			};
		}	// namespace detail

		inline detail::gltf_error_category const &gltf_error_category() {
			static detail::gltf_error_category c;
			return c;
		}

		gltf_error::gltf_error(gltf_error::cases e)
			: std::error_code{e, gltf_error_category()} {
		}

		inline gltf_error make_error_code(gltf_error::cases e) {
			return gltf_error{e};
		}

		using BOOST_OUTCOME_V1_NAMESPACE::expected;
		using BOOST_OUTCOME_V1_NAMESPACE::make_unexpected;
		using BOOST_OUTCOME_V1_NAMESPACE::option;
		using BOOST_OUTCOME_V1_NAMESPACE::empty_t;

		template <typename T>
		using gltf_result = expected<T, gltf_error>;

		template <typename T>
		constexpr gltf_result<T> make_expected(T &&v) {
			return BOOST_OUTCOME_V1_NAMESPACE::make_expected<T, gltf_error>(std::forward<T>(v));
		}

		template <typename T, typename E>
		constexpr option<T> as_option(expected<T, E> ex) {
			if(ex) {
				return *ex;
			}
			return empty_t{};
		}
	}	// namespace v1
}	// namespace gltfpp
