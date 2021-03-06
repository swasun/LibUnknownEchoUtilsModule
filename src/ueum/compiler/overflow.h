/*******************************************************************************
 * Copyright (C) 2018 Charly Lamothe                                           *
 *                                                                             *
 * This file is part of LibUnknownEchoUtilsModule.                             *
 *                                                                             *
 *   Licensed under the Apache License, Version 2.0 (the "License");           *
 *   you may not use this file except in compliance with the License.          *
 *   You may obtain a copy of the License at                                   *
 *                                                                             *
 *   http://www.apache.org/licenses/LICENSE-2.0                                *
 *                                                                             *
 *   Unless required by applicable law or agreed to in writing, software       *
 *   distributed under the License is distributed on an "AS IS" BASIS,         *
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 *   See the License for the specific language governing permissions and       *
 *   limitations under the License.                                            *
 *******************************************************************************/

#ifndef UNKNOWNECHOUTILSMODULE_OVERFLOW_H
#define UNKNOWNECHOUTILSMODULE_OVERFLOW_H

#include <ueum/compiler/inline.h>
#include <ueum/compiler/bool.h>
#include <ueum/compiler/warn_unused_result.h>
#include <ueum/compiler/typecheck.h>
#include <ueum/compiler/typeof.h>

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

#define ueum__add_overflow(a, b, res) ueum__warn_unused_result(__builtin_add_overflow((a), (b), (res)))
#define ueum__sub_overflow(a, b, res) ueum__warn_unused_result(__builtin_sub_overflow((a), (b), (res)))
#define ueum__mul_overflow(a, b, res) ueum__warn_unused_result(__builtin_mul_overflow((a), (b), (res)))

 /* C11 */
#elif __STDC_VERSION__ >= 201112L

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

#define ueum__add_overflow(a, b, res) ueum__warn_unused_result(__extension__({ \
    typecheck((a), (b)); \
    typecheck((b), *(res)); \
    __ueum__add_overflow_func((a), (b), (res)); \
}))

#define ueum__sub_overflow(a, b, res) ueum__warn_unused_result(__extension__({ \
    typecheck((a), (b)); \
    typecheck((b), *(res)); \
    __ueum__sub_overflow_func((a), (b), (res)); \
}))

#define ueum__mul_overflow(a, b, res) ueum__warn_unused_result(__extension__({ \
    typecheck((a), (b)); \
    typecheck((b), *(res)); \
    __ueum__mul_overflow_func((a), (b), (res)); \
}))

#else

#define ueum__add_overflow(a, b, res) 0

#define ueum__sub_overflow(a, b, res) 0

#define ueum__mul_overflow(a, b, res) 0

#endif /* __has_builtin(...) */

/* ueum__add3_overflow(a, b, c) -> (a + b + c) */
#define ueum__add3_overflow(a, b, c, res) ueum__warn_unused_result(__extension__({ \
    __typeof__(*(res)) _tmp; \
    bool _s, _t; \
    _s = ueum__add_overflow((a), (b), &_tmp); \
    _t = ueum__add_overflow((c), _tmp, (res)); \
    _s | _t; \
}))

/* ueum__add_and_mul_overflow(a, b, x) -> (a + b)*x */
#define ueum__add_and_mul_overflow(a, b, x, res) ueum__warn_unused_result(__extension__({ \
    __typeof__(*(res)) _tmp; \
    bool _s, _t; \
    _s = ueum__add_overflow((a), (b), &_tmp); \
    _t = ueum__mul_overflow((x), _tmp, (res)); \
    _s | _t; \
}))

/* ueum__mul_and_add_overflow(a, x, b) -> a*x + b */
#define ueum__mul_and_add_overflow(a, x, b, res) ueum__warn_unused_result(__extension__({ \
    __typeof__(*(res)) _tmp; \
    bool _s, _t; \
    _s = ueum__mul_overflow((a), (x), &_tmp); \
    _t = ueum__add_overflow((b), _tmp, (res)); \
    _s | _t; \
}))

#endif
