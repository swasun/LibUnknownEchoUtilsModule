/******************************************************************************************
 * Copyright (C) 2018 by Charly Lamothe                                                   *
 *                                                                                        *
 * This file is part of LibUnknownEchoUtilsModule.                                        *
 *                                                                                        *
 *   LibUnknownEchoUtilsModule is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by                 *
 *   the Free Software Foundation, either version 3 of the License, or                    *
 *   (at your option) any later version.                                                  *
 *                                                                                        *
 *   LibUnknownEchoUtilsModule is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of                       *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                        *
 *   GNU General Public License for more details.                                         *
 *                                                                                        *
 *   You should have received a copy of the GNU General Public License                    *
 *   along with LibUnknownEchoUtilsModule.  If not, see <http://www.gnu.org/licenses/>.   *
 ******************************************************************************************/

#ifndef UNKNOWNECHOUTILSMODULE_TYPECHECK_H
#define UNKNOWNECHOUTILSMODULE_TYPECHECK_H

#ifndef typecheck

#include <ueum/compiler/typeof.h>

#if __STDC_VERSION__ >= 201112L

/* Compile-time assertion that check if 'x' and 'y' are equivalent types */
#define typecheck(x, y) do { \
    _Static_assert(__builtin_types_compatible_p(__typeof__(x),__typeof__(y)), \
        "Arithmetic overflow detected: incompatible types"); \
} while (0)

#else

/*
 * SPDX-License-Identifier: GPL-2.0
 * 
 * from https://github.com/torvalds/linux/blob/master/include/linux/typecheck.h
 * 
 * Check at compile time that something is of a particular type.
 * Always evaluates to 1 so you may use it easily in comparisons.
 */
#define typecheck(type, x) \
({    type __dummy; \
    __typeof__(x) __dummy2; \
    (void)(&__dummy == &__dummy2); \
    1; \
})

#endif

#endif

#endif
