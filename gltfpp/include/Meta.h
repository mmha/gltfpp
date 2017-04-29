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

		template <typename T>
		struct is_fundamental_json_type
			: disjunction<std::is_arithmetic<T>, std::is_same<T, std::string>, std::is_same<T, nlohmann::json>> {};

		template <typename T>
		struct is_fundamental_json_type<std::vector<T>> : is_fundamental_json_type<T> {};
	}	// namespace v1
}	// namespace gltfpp
