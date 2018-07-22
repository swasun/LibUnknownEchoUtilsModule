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

#ifndef UNKNOWNECHOUTILSMODULE_WARN_UNUSED_RESULT_H
#define UNKNOWNECHOUTILSMODULE_WARN_UNUSED_RESULT_H

#include <ueum/compiler/bool.h>
#include <ueum/compiler/inline.h>

#if defined(__unix__)
    #include <sys/cdefs.h>
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

ueum__inline(bool) ueum__warn_result ueum__warn_unused_result(bool x) {
    return x;
}

#endif
