/******************************************************************************************
 * Copyright (C) 2018 by Charly Lamothe													  *
 *																						  *
 * This file is part of LibUnknownEchoUtilsModule.										  *
 *																						  *
 *   LibUnknownEchoUtilsModule is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by				  *
 *   the Free Software Foundation, either version 3 of the License, or					  *
 *   (at your option) any later version.												  *
 *																						  *
 *   LibUnknownEchoUtilsModule is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *   GNU General Public License for more details.										  *
 *																						  *
 *   You should have received a copy of the GNU General Public License					  *
 *   along with LibUnknownEchoUtilsModule.  If not, see <http://www.gnu.org/licenses/>.   *
 ******************************************************************************************/

/*
 * This code is inspired from integer.h of libgit2.
 * 
 * Copyright (C) the libgit2 contributors. All rights reserved.
 *
 * This file is part of libgit2, distributed under the GNU GPL v2 with
 * a Linking Exception. For full terms see the included COPYING file.
 */

#ifndef UNKNOWNECHOUTILSMODULE_SAFE_ARITHMETIC_H
#define UNKNOWNECHOUTILSMODULE_SAFE_ARITHMETIC_H

#include <ueum/inline.h>
#include <ueum/bool.h>

#include <stddef.h>
#include <stdint.h>
#include <limits.h>

#if defined(__unix__)
	#include <sys/cdefs.h>
#endif

/* Support for gcc/clang __has_builtin intrinsic */
#ifndef __has_builtin
# define __has_builtin(x) 0
#endif


#if defined(__clang__)

#define UEUM_WARN_RESULT __attribute__((__warn_unused_result__))

#elif defined(__GNUC__)

#define UEUM_WARN_RESULT __attribute__((warn_unused_result))

#elif defined(_MSC_VER) && (_MSC_VER >= 1700)

#define UEUM_WARN_RESULT _Check_return_

#else

#error (No warn_unused_result builtin found)

#endif

static inline bool UEUM_WARN_RESULT ueum_warn_unused(bool x) {
	return x;
}


/* Use clang/gcc compiler intrinsics whenever possible */
#if (SIZE_MAX == ULONG_MAX) && __has_builtin(__builtin_uaddl_overflow)

# define ueum__add_sizet_overflow(one, two, out) \
	__builtin_uaddl_overflow(one, two, out)

# define ueum__multiply_sizet_overflow(one, two, out) \
	__builtin_umull_overflow(one, two, out)

# define ueum__sub_sizet_overflow(one, two, out) \
    __builtin_usubl_overflow(one, two, out);

#elif (SIZE_MAX == UINT_MAX) && __has_builtin(__builtin_uadd_overflow)

# define ueum__add_sizet_overflow(one, two, out) \
	__builtin_uadd_overflow(one, two, out)

# define ueum__multiply_sizet_overflow(one, two, out) \
	__builtin_umul_overflow(one, two, out)

# define ueum__sub_sizet_overflow(one, two, out) \
    __builtin_usub_overflow(one, two, out);

#else

/**
 * Sets `one + two` into `out`, unless the arithmetic would overflow.
 * @return true if the result fits in a `size_t`, false on overflow.
 */
UEUM_INLINE(bool) ueum__add_sizet_overflow(size_t one, size_t two, size_t *out) {
	if (ULONG_MAX - one < two) {
		return true;
    }
	*out = one + two;
	return false;
}

/**
 * Sets `one * two` into `out`, unless the arithmetic would overflow.
 * @return true if the result fits in a `size_t`, false on overflow.
 */
UEUM_INLINE(bool) ueum__multiply_sizet_overflow(size_t one, size_t two, size_t *out) {
	if (one && ULONG_MAX / one < two) {
		return true;
    }
	*out = one * two;
	return false;
}

/**
 * @source inspired from https://wiki.sei.cmu.edu/confluence/display/c/INT30-C.+Ensure+that+unsigned+integer+operations+do+not+wrap
 */
UEUM_INLINE(bool) ueum__sub_sizet_overflow(size_t one, size_t two, size_t *out) {
    if (one < two) {
        return true;
    }
    *out = one - two;
    return false;
}

#endif

#if __has_builtin(__builtin_uaddl_overflow)

/*
 * Facilities for performing type- and overflow-checked arithmetic. These
 * functions return non-zero if overflow occured, zero otherwise. In either case,
 * the potentially overflowing operation is fully performed, mod the size of the
 * output type. See:
 * https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
 * http://clang.llvm.org/docs/LanguageExtensions.html#checked-arithmetic-builtins
 * for full details.
 *
 * The compiler enforces that users of os_*_overflow() check the return value to
 * determine whether overflow occured.
 */

#if __has_builtin(__builtin_add_overflow) && \
    __has_builtin(__builtin_sub_overflow) && \
    __has_builtin(__builtin_mul_overflow)

#define os_add_overflow(a, b, res) __os_warn_unused(__builtin_add_overflow((a), (b), (res)))
#define os_sub_overflow(a, b, res) __os_warn_unused(__builtin_sub_overflow((a), (b), (res)))
#define os_mul_overflow(a, b, res) __os_warn_unused(__builtin_mul_overflow((a), (b), (res)))

#else

/* compile-time assertion that 'x' and 'y' are equivalent types */
#ifdef __cplusplus
#define __OS_TYPE_CHECK(x, y) do { \
	__typeof__(x) _x; \
	__typeof__(y) _y; \
	(void)(&_x == &_y, "overflow arithmetic: incompatible types"); \
} while (0)
#else
#define __OS_TYPE_CHECK(x, y) do { \
	_Static_assert(__builtin_types_compatible_p(__typeof(x),__typeof(y)), \
			"overflow arithmetic: incompatible types"); \
} while (0)
#endif

#define ueum__add_overflow(T,U,V) _Generic((T), \
		unsigned:           __builtin_uadd_overflow, \
		unsigned long:      __builtin_uaddl_overflow, \
		unsigned long long: __builtin_uaddll_overflow, \
		int:                __builtin_sadd_overflow, \
		long:               __builtin_saddl_overflow, \
		long long:          __builtin_saddll_overflow, \
		size_t:				ueum__add_sizet_overflow \
	)(T,U,V)

#define ueum__sub_overflow(T,U,V) _Generic((T), \
		unsigned:           __builtin_usub_overflow, \
		unsigned long:      __builtin_usubl_overflow, \
		unsigned long long: __builtin_usubll_overflow, \
		int:                __builtin_ssub_overflow, \
		long:               __builtin_ssubl_overflow, \
		long long:          __builtin_ssubll_overflow \
	)(T,U,V)

#define __os_mul_overflow_func(T,U,V) _Generic((T), \
		unsigned:           __builtin_umul_overflow, \
		unsigned long:      __builtin_umull_overflow, \
		unsigned long long: __builtin_umulll_overflow, \
		int:                __builtin_smul_overflow, \
		long:               __builtin_smull_overflow, \
		long long:          __builtin_smulll_overflow \
	)(T,U,V)

#define os_add_overflow(a, b, res) __os_warn_unused(__extension__({ \
	__OS_TYPE_CHECK((a), (b)); \
	__OS_TYPE_CHECK((b), *(res)); \
	__os_add_overflow_func((a), (b), (res)); \
}))

#define os_sub_overflow(a, b, res) __os_warn_unused(__extension__({ \
	__OS_TYPE_CHECK((a), (b)); \
	__OS_TYPE_CHECK((b), *(res)); \
	__os_sub_overflow_func((a), (b), (res)); \
}))

#define os_mul_overflow(a, b, res) __os_warn_unused(__extension__({ \
	__OS_TYPE_CHECK((a), (b)); \
	__OS_TYPE_CHECK((b), *(res)); \
	__os_mul_overflow_func((a), (b), (res)); \
}))

#endif /* __has_builtin(...) */

/* os_add3_overflow(a, b, c) -> (a + b + c) */
#define os_add3_overflow(a, b, c, res) __os_warn_unused(__extension__({ \
	__typeof(*(res)) _tmp; \
	bool _s, _t; \
	_s = os_add_overflow((a), (b), &_tmp); \
	_t = os_add_overflow((c), _tmp, (res)); \
	_s | _t; \
}))

/* os_add_and_mul_overflow(a, b, x) -> (a + b)*x */
#define os_add_and_mul_overflow(a, b, x, res) __os_warn_unused(__extension__({ \
	__typeof(*(res)) _tmp; \
	bool _s, _t; \
	_s = os_add_overflow((a), (b), &_tmp); \
	_t = os_mul_overflow((x), _tmp, (res)); \
	_s | _t; \
}))

/* os_mul_and_add_overflow(a, x, b) -> a*x + b */
#define os_mul_and_add_overflow(a, x, b, res) __os_warn_unused(__extension__({ \
	__typeof(*(res)) _tmp; \
	bool _s, _t; \
	_s = os_mul_overflow((a), (x), &_tmp); \
	_t = os_add_overflow((b), _tmp, (res)); \
	_s | _t; \
}))

#endif

#endif
