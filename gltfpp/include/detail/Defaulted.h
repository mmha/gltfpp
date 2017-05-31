#pragma once
#include "../Meta.h"
#include <utility>

namespace gltfpp {
	inline namespace v1 {
		template <typename T>
		struct defaulted {
			private:
			T val;

			public:
			defaulted() = delete;

			template <typename... Args>
			constexpr defaulted(Args &&... args) noexcept(noexcept(T(std::forward<Args>(args)...)))
				: val(std::forward<Args>(args)...) {
			}

			template <typename U>
			constexpr defaulted operator=(U &&rhs) noexcept(noexcept(val = std::forward<U>(rhs))) {
				val = std::forward<U>(rhs);
				return *this;
			}

			constexpr operator T &() noexcept {
				return val;
			}

			constexpr operator T const &() const noexcept {
				return val;
			}

			constexpr T &value() noexcept {
				return val;
			}

			constexpr T const &value() const noexcept {
				return val;
			}

			constexpr T *operator->() noexcept {
				return &val;
			}

			constexpr const T *operator->() const noexcept {
				return &val;
			}

#define DEFAULTED_COMPARISON_OVERLOAD(op)                                                                       \
	template <typename U>                                                                                       \
	constexpr friend bool operator op(const defaulted<T> &lhs,                                                  \
									  const defaulted<U> &rhs) noexcept(noexcept(lhs.value() op rhs.value())) { \
		return lhs.value() op rhs.value();                                                                      \
	}

			DEFAULTED_COMPARISON_OVERLOAD(==)
			DEFAULTED_COMPARISON_OVERLOAD(!=)
			DEFAULTED_COMPARISON_OVERLOAD(<=)
			DEFAULTED_COMPARISON_OVERLOAD(>=)
			DEFAULTED_COMPARISON_OVERLOAD(<)
			DEFAULTED_COMPARISON_OVERLOAD(>)

#undef DEFAULTED_COMPARISON_OVERLOAD

			friend void swap(defaulted &self,
							 defaulted &other) noexcept(detail::swappable::is_nothrow_swappable<T>::value) {
				using std::swap;
				swap(self.val, other.val);
			}
		};
	}	// namespace v1
}	// namespace gltfpp
