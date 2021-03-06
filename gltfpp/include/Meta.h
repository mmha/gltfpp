#pragma once
#include <json.hpp>
#include <type_traits>

namespace gltfpp {
	inline namespace v1 {
		/*
		 * Detection Idiom
		 */

		template <typename...>
		using void_t = void;

		enum class nonesuch {};

		namespace detail {
			template <typename Default, typename AlwaysVoid, template <typename...> class Op, typename... Args>
			struct detector {
				using value_t = std::false_type;
				using type = Default;
			};

			template <typename Default, template <typename...> class Op, typename... Args>
			struct detector<Default, void_t<Op<Args...>>, Op, Args...> {
				using value_t = std::true_type;
				using type = Op<Args...>;
			};
		}    // namespace detail

		template <template <typename...> class Op, typename... Args>
		using is_detected = typename detail::detector<nonesuch, void, Op, Args...>::value_t;

		template <template <typename...> class Op, typename... Args>
		using detected_t = typename detail::detector<nonesuch, void, Op, Args...>::type;

		template <typename Default, template <typename...> class Op, typename... Args>
		using detected_or = detail::detector<Default, void, Op, Args...>;

		/*******************************************************************************************************/

		/**
		 * is_nothrow_swappable from mpark/variant
		 */
		namespace detail {
			namespace swappable {
				using std::swap;

				template <typename T>
				struct is_swappable_impl {
					private:
					template <typename U, typename = decltype(swap(std::declval<U &>(), std::declval<U &>()))>
					inline static std::true_type test(int);

					template <typename U>
					inline static std::false_type test(...);

					public:
					using type = decltype(test<T>(0));
				};

				template <typename T>
				using is_swappable = typename is_swappable_impl<T>::type;

				template <typename T, bool = is_swappable<T>::value>
				struct is_nothrow_swappable {
					static constexpr bool value = noexcept(swap(std::declval<T &>(), std::declval<T &>()));
				};

				template <typename T>
				struct is_nothrow_swappable<T, false> : std::false_type {};

			}    // namespace swappable
		}        // namespace detail

		template <typename T>
		using is_swappable = detail::swappable::is_swappable<T>;

		template <typename T>
		using is_nothrow_swappable = detail::swappable::is_nothrow_swappable<T>;

		/*******************************************************************************************************/

		template <typename...>
		struct disjunction : std::false_type {};
		template <typename B1>
		struct disjunction<B1> : B1 {};
		template <typename B1, typename... Bn>
		struct disjunction<B1, Bn...> : std::conditional_t<bool(B1::value), B1, disjunction<Bn...>> {};

		template <typename T, template <typename...> class Base>
		struct is_specialization_of : public std::false_type {};
		template <template <typename...> class Base, typename... Args>
		struct is_specialization_of<Base<Args...>, Base> : public std::true_type {};
		template <typename T, template <typename...> class Base>
		constexpr bool is_specialization_of_v = is_specialization_of<T, Base>::value;

		template <typename T, typename... Seq>
		using is_any_of = disjunction<std::is_same<T, Seq>...>;

		namespace detail {
			template <typename T>
			using detect_better_enum = typename T::_enumerated;

			template <typename T>
			constexpr bool is_enumeration = is_detected<detect_better_enum, T>::value;

			template <typename T>
			constexpr bool is_fundamental_json_type =
			    !is_enumeration<T> &&
			    disjunction<std::is_arithmetic<T>, is_any_of<T, std::string, nlohmann::json>>::value;

			// Make this public as customization point?
			template <typename T>
			constexpr bool is_field_list = is_specialization_of_v<T, std::vector>;

			// FIXME proper concept checking
			template <typename T>
			constexpr bool is_field_aggregate = !is_fundamental_json_type<T> && !is_field_list<T> && !is_enumeration<T>;
		}    // namespace detail
	}        // namespace v1
}    // namespace gltfpp
