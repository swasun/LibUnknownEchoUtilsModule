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

#ifndef UNKNOWNECHOUTILSMODULE_PRAGMA_H
#define UNKNOWNECHOUTILSMODULE_PRAGMA_H

/* Check if Microsoft Visual C++ compiler is used */
#if defined(_MSC_VER)

/**
 * @brief Disable a warning on win platform for MSC
 *           You must call UEUM_DISABLE_WIN32_PRAGMA_WARN_END afterwards.
 *
 * @source: https://stackoverflow.com/a/13577924
 */
#define UEUM_DISABLE_WIN32_PRAGMA_WARN(nnn) \
    __pragma (warning (push)) \
    __pragma (warning(disable : nnn)) \

#define UEUM_DISABLE_WIN32_PRAGMA_WARN_END() \
    __pragma (warning (pop)) \

/**
 * @brief Disable the warning https://docs.microsoft.com/fr-fr/cpp/error-messages/compiler-warnings/compiler-warning-level-1-c4047
 *           for MSC 
 */
#define UEUM_DISABLE_Wtype_limits() \
    UEUM_DISABLE_WIN32_PRAGMA_WARN(4047) \

#define UEUM_DISABLE_Wtype_limits_END() \
    UEUM_DISABLE_WIN32_PRAGMA_WARN_END() \

/* Check if GCC-like compiler is used */
#elif defined(__GNUC__)

#define UEUM_DISABLE_Wtype_limits() \
    _Pragma("GCC diagnostic push") \
    _Pragma("GCC diagnostic ignored \"-Wtype-limits\"") \

#define UEUM_DISABLE_Wtype_limits_END() \
    _Pragma("GCC diagnostic pop") \

/* Set empty defines otherwise */
#else

#define UEUM_DISABLE_Wtype_limits()
#define UEUM_DISABLE_Wtype_limits_END()

#endif

#endif
