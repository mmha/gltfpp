#pragma once
#include <type_traits>

/**
 * @file Backport of C++17'S std::byte
 * @see
 */

namespace gltfpp {
	inline namespace v1 {
		enum class byte : unsigned char {};

		constexpr byte operator""_b(unsigned long long b) {
			return static_cast<byte>(b);
		}

		template <typename Integer>
		constexpr auto to_integer(byte &b) noexcept -> std::enable_if_t<std::is_integral<Integer>::value, Integer> {
			return Integer(b);
		}

		template <typename Integer>
		constexpr auto operator<<=(byte &b, Integer shift) noexcept
			-> std::enable_if_t<std::is_integral<Integer>::value, byte &> {
			return b = byte(static_cast<unsigned char>(b) << shift);
		}

		template <typename Integer>
		constexpr auto operator>>=(byte &b, Integer shift) noexcept
			-> std::enable_if_t<std::is_integral<Integer>::value, byte &> {
			return b = byte(static_cast<unsigned char>(b) >> shift);
		}

		template <typename Integer>
		constexpr auto operator<<(byte &b, Integer shift) noexcept
			-> std::enable_if_t<std::is_integral<Integer>::value, byte> {
			return byte(static_cast<unsigned char>(b) << shift);
		}

		template <typename Integer>
		constexpr auto operator>>(byte &b, Integer shift) noexcept
			-> std::enable_if_t<std::is_integral<Integer>::value, byte> {
			return byte(static_cast<unsigned char>(b) >> shift);
		}

		constexpr byte &operator|=(byte &l, byte r) noexcept {
			return l = byte(static_cast<unsigned char>(l) | static_cast<unsigned char>(r));
		}

		constexpr byte &operator&=(byte &l, byte r) noexcept {
			return l = byte(static_cast<unsigned char>(l) & static_cast<unsigned char>(r));
		}

		constexpr byte &operator^=(byte &l, byte r) noexcept {
			return l = byte(static_cast<unsigned char>(l) ^ static_cast<unsigned char>(r));
		}

		constexpr byte operator|(byte l, byte r) noexcept {
			return byte(static_cast<unsigned char>(l) | static_cast<unsigned char>(r));
		}

		constexpr byte operator&(byte l, byte r) noexcept {
			return byte(static_cast<unsigned char>(l) | static_cast<unsigned char>(r));
		}

		constexpr byte operator^(byte l, byte r) noexcept {
			return byte(static_cast<unsigned char>(l) | static_cast<unsigned char>(r));
		}
	}	// namespace v1
}	// namespace gltfpp
