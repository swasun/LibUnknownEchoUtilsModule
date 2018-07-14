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

/** Support for gcc/clang __has_builtin intrinsic */
#ifndef __has_builtin
# define __has_builtin(x) 0
#endif

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
	if (SIZE_MAX - one < two) {
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
	if (one && SIZE_MAX / one < two) {
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

#endif
