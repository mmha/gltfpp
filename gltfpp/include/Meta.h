#pragma once
#include <json.hpp>
#include <type_traits>

namespace gltfpp {
	inline namespace v1 {
		template <typename...>
		struct disjunction : std::false_type {};
		template <typename B1>
		struct disjunction<B1> : B1 {};
		template <typename B1, typename... Bn>
		struct disjunction<B1, Bn...> : std::conditional_t<bool(B1::value), B1, disjunction<Bn...>> {};

		template<typename T, template<typename...> class Base>
		struct is_specialization_of : public std::false_type {};
		template<template<typename...> class Base, typename... Args>
		struct is_specialization_of<Base<Args...>, Base> : public std::true_type {};
		template<typename T, template<typename...> class Base>
		constexpr bool is_specialization_of_v = is_specialization_of<T, Base>::value;

		namespace detail {
			template <typename T>
			constexpr bool is_fundamental_json_type = disjunction<
				std::is_arithmetic<T>,
				std::is_same<T, std::string>,
				std::is_same<T, nlohmann::json>
			>::value;

			// Make this public as customization point?
			template<typename T>
			constexpr bool is_field_list = is_specialization_of_v<T, std::vector>;

			// FIXME proper concept checking
			template<typename T>
			constexpr bool is_field_aggregate = !is_fundamental_json_type<T> && !is_field_list<T>;

			// TODO We need fancy enums with hana::strings
			template<typename T>
			constexpr bool is_enumeration = std::is_enum<T>::value;
		}
	}	// namespace v1
}	// namespace gltfpp
