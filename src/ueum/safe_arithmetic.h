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

#define ueum__warn_result __attribute__((__warn_unused_result__))

#elif defined(__GNUC__)

#define ueum__warn_result __attribute__((warn_unused_result))

#elif defined(_MSC_VER) && (_MSC_VER >= 1700)

#define ueum__warn_result _Check_return_

#else

#error (No warn_unused_result builtin found)

#endif

static inline bool ueum__warn_result ueum__warn_unused(bool x) {
	return x;
}


/* compile-time assertion that 'x' and 'y' are equivalent types */
#ifdef __cplusplus
#define ueum__type_check(x, y) do { \
	__typeof__(x) _x; \
	__typeof__(y) _y; \
	(void)(&_x == &_y, "overflow arithmetic: incompatible types"); \
} while (0)
#else
#define ueum__type_check(x, y) do { \
	_Static_assert(__builtin_types_compatible_p(__typeof(x),__typeof(y)), \
			"overflow arithmetic: incompatible types"); \
} while (0)
#endif


#define typename(x) _Generic((x),                                                 \
        _Bool: "_Bool",                  unsigned char: "unsigned char",          \
         char: "char",                     signed char: "signed char",            \
    short int: "short int",         unsigned short int: "unsigned short int",     \
          int: "int",                     unsigned int: "unsigned int",           \
     long int: "long int",           unsigned long int: "unsigned long int",      \
long long int: "long long int", unsigned long long int: "unsigned long long int", \
        float: "float",                         double: "double",                 \
  long double: "long double",                   char *: "pointer to char",        \
       void *: "pointer to void",                int *: "pointer to int",         \
      default: "unknown")


/* Use clang/gcc compiler intrinsics whenever pueumsible */
#if (SIZE_MAX == ULONG_MAX) && __has_builtin(__builtin_uaddl_overflow)

# define ueum__add_sizet_overflow(one, two, out) \
	__builtin_uaddl_overflow(one, two, out)

# define ueum__mul_sizet_overflow(one, two, out) \
	__builtin_umull_overflow(one, two, out)

# define ueum__sub_sizet_overflow(one, two, out) \
    __builtin_usubl_overflow(one, two, out);

#elif (SIZE_MAX == UINT_MAX) && __has_builtin(__builtin_uadd_overflow)

# define ueum__add_sizet_overflow(one, two, out) \
	__builtin_uadd_overflow(one, two, out)

# define ueum__mul_sizet_overflow(one, two, out) \
	__builtin_umul_overflow(one, two, out)

# define ueum__sub_sizet_overflow(one, two, out) \
    __builtin_usub_overflow(one, two, out);

#else

/**
 * Sets `one + two` into `out`, unless the arithmetic would overflow.
 * @return true if the result fits in a `size_t`, false on overflow.
 */
ueum__inline(bool) ueum__add_sizet_overflow(size_t one, size_t two, size_t *out) {
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
ueum__inline(bool) ueum__mul_sizet_overflow(size_t one, size_t two, size_t *out) {
	if (one && ULONG_MAX / one < two) {
		return true;
    }
	*out = one * two;
	return false;
}

/**
 * @source inspired from https://wiki.sei.cmu.edu/confluence/display/c/INT30-C.+Ensure+that+unsigned+integer+operations+do+not+wrap
 */
ueum__inline(bool) ueum__sub_sizet_overflow(size_t one, size_t two, size_t *out) {
    if (one < two) {
        return true;
    }
    *out = one - two;
    return false;
}

#endif

/*
 * Facilities for performing type- and overflow-checked arithmetic. These
 * functions return non-zero if overflow occured, zero otherwise. In either case,
 * the potentially overflowing operation is fully performed, mod the size of the
 * output type. See:
 * https://gcc.gnu.org/onlinedocs/gcc/Integer-Overflow-Builtins.html
 * http://clang.llvm.org/docs/LanguageExtensions.html#checked-arithmetic-builtins
 * for full details.
 *
 * The compiler enforces that users of ueum__*_overflow() check the return value to
 * determine whether overflow occured.
 */

#if __has_builtin(__builtin_add_overflow) && \
    __has_builtin(__builtin_sub_overflow) && \
    __has_builtin(__builtin_mul_overflow)

#define ueum__add_overflow(a, b, res) ueum__warn_unused(__builtin_add_overflow((a), (b), (res)))
#define ueum__sub_overflow(a, b, res) ueum__warn_unused(__builtin_sub_overflow((a), (b), (res)))
#define ueum__mul_overflow(a, b, res) ueum__warn_unused(__builtin_mul_overflow((a), (b), (res)))

#else

#define __ueum__add_overflow_func(T,U,V) _Generic((T), \
		unsigned:           __builtin_uadd_overflow, \
		unsigned long:      __builtin_uaddl_overflow, \
		unsigned long long: __builtin_uaddll_overflow, \
		int:                __builtin_sadd_overflow, \
		long:               __builtin_saddl_overflow, \
		long long:          __builtin_saddll_overflow \
	)(T,U,V)

#define __ueum__sub_overflow_func(T,U,V) _Generic((T), \
		unsigned:           __builtin_usub_overflow, \
		unsigned long:      __builtin_usubl_overflow, \
		unsigned long long: __builtin_usubll_overflow, \
		int:                __builtin_ssub_overflow, \
		long:               __builtin_ssubl_overflow, \
		long long:          __builtin_ssubll_overflow \
	)(T,U,V)

#define __ueum__mul_overflow_func(T,U,V) _Generic((T), \
		unsigned:           __builtin_umul_overflow, \
		unsigned long:      __builtin_umull_overflow, \
		unsigned long long: __builtin_umulll_overflow, \
		int:                __builtin_smul_overflow, \
		long:               __builtin_smull_overflow, \
		long long:          __builtin_smulll_overflow \
	)(T,U,V)

#define ueum__add_overflow(a, b, res) ueum__warn_unused(__extension__({ \
	ueum__type_check((a), (b)); \
	ueum__type_check((b), *(res)); \
	__ueum__add_overflow_func((a), (b), (res)); \
}))

#define ueum__sub_overflow(a, b, res) ueum__warn_unused(__extension__({ \
	ueum__type_check((a), (b)); \
	ueum__type_check((b), *(res)); \
	__ueum__sub_overflow_func((a), (b), (res)); \
}))

#define ueum__mul_overflow(a, b, res) ueum__warn_unused(__extension__({ \
	ueum__type_check((a), (b)); \
	ueum__type_check((b), *(res)); \
	__ueum__mul_overflow_func((a), (b), (res)); \
}))

#endif /* __has_builtin(...) */

/* ueum__add3_overflow(a, b, c) -> (a + b + c) */
#define ueum__add3_overflow(a, b, c, res) ueum__warn_unused(__extension__({ \
	__typeof(*(res)) _tmp; \
	bool _s, _t; \
	_s = ueum__add_overflow((a), (b), &_tmp); \
	_t = ueum__add_overflow((c), _tmp, (res)); \
	_s | _t; \
}))

/* ueum__add_and_mul_overflow(a, b, x) -> (a + b)*x */
#define ueum__add_and_mul_overflow(a, b, x, res) ueum__warn_unused(__extension__({ \
	__typeof(*(res)) _tmp; \
	bool _s, _t; \
	_s = ueum__add_overflow((a), (b), &_tmp); \
	_t = ueum__mul_overflow((x), _tmp, (res)); \
	_s | _t; \
}))

/* ueum__mul_and_add_overflow(a, x, b) -> a*x + b */
#define ueum__mul_and_add_overflow(a, x, b, res) ueum__warn_unused(__extension__({ \
	__typeof(*(res)) _tmp; \
	bool _s, _t; \
	_s = ueum__mul_overflow((a), (x), &_tmp); \
	_t = ueum__add_overflow((b), _tmp, (res)); \
	_s | _t; \
}))

#define __ueum_safe_add_internal(a, b, res, rollback_expression) \
	if (ueum__add_overflow(a, b, res)) { \
		ei_stacktrace_push_msg("Arithmetic overflow detected when performing: (%s)=(%s)+(%s)", typename(res), \
			typename(a), typename(b)); \
		rollback_expression; \
	} \

#define ueum_safe_add(a, b, res) \
	__ueum_safe_add_internal(a, b, res, return 0); \

#define ueum_safe_add_or_goto(a, b, res, label) \
	__ueum_safe_add_internal(a, b, res, goto label); \

#define __ueum_safe_add3_internal(a, b, c, res, rollback_expression) \
	if (ueum__add3_overflow(a, b, c, res)) { \
		ei_stacktrace_push_msg("Arithmetic overflow detected when performing: (%s)=(%s)+(%s)+(%s)", typename(res), \
			typename(a), typename(b), typename(c)); \
		rollback_expression; \
	} \

#define ueum_safe_add3(a, b, c, res) \
	__ueum_safe_add3_internal(a, b, c, res, return 0); \

#define ueum_safe_add3_or_goto(a, b, c, res, label) \
	__ueum_safe_add3_internal(a, b, c, res, goto label); \

#define __ueum_safe_sub_internal(a, b, res, rollback_expression) \
	if (ueum__sub_overflow(a, b, res)) { \
		ei_stacktrace_push_msg("Arithmetic overflow detected when performing: (%s)=(%s)-(%s)", typename(res), \
			typename(a), typename(b)); \
		rollback_expression; \
	} \

#define ueum_safe_sub(a, b, res) \
	__ueum_safe_sub_internal(a, b, res, return 0); \

#define ueum_safe_sub_or_goto(a, b, res, label) \
	__ueum_safe_sub_internal(a, b, res, goto label); \

#define __ueum_safe_mul_internal(a, b, res, rollback_expression) \
	if (ueum__mul_overflow(a, b, res)) { \
		ei_stacktrace_push_msg("Arithmetic overflow detected when performing: (%s)=(%s)*(%s)", typename(res), \
			typename(a), typename(b)); \
		rollback_expression; \
	} \

#define ueum_safe_mul(a, b, res) \
	__ueum_safe_mul_internal(a, b, res, return 0); \

#define ueum_safe_mul_or_goto(a, b, res, label) \
	__ueum_safe_mul_internal(a, b, res, goto label); \

#endif
