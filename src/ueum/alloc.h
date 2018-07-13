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

/**
 * The __pragma(warning(disable:4127)) is used to disable this warning:
 * https://docs.microsoft.com/fr-fr/cpp/error-messages/compiler-warnings/compiler-warning-level-4-c4127
 * that append when size is not variable, like 1. So 1 == 0 will trigger this warnings.
 *
 *  @file      alloc.h
 *  @brief     Macro functions to safely alloc/desalloc variables.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef UNKNOWNECHOUTILSMODULE_ALLOC_H
#define UNKNOWNECHOUTILSMODULE_ALLOC_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <ei/ei.h>

/**
 * Check if a variable is unsigned
 *
 * @source: https://stackoverflow.com/a/9629354
 * @source: https://stackoverflow.com/a/7317613
 * @todo fix for unsigned char
 */
#if defined(__GNUC__)

//_Pragma("GCC diagnostic push")
//_Pragma("GCC diagnostic ignored \"-Werror\"")
//#pragma GCC diagnostic ignored "-Werror")

//#define ISUNSIGNED(a) (a>=0 && ((a=~a)>=0 ? (a=~a, 1) : (a=~a, 0)))

//#pragma GCC diagnostic pop
//_Pragma("GCC diagnostic pop")

#define ISUNSIGNED(a) (a >= 0 && ~a >= 0)

#else

#define ISUNSIGNED(a) (a >= 0 && ~a >= 0)

#endif

#ifdef _WIN32

/**
 * Disable a warning on win32 platform
 * You must call UEUM_DISABLE_WIN32_PRAGMA_WARN_END afterwards
 *
 * @source: https://stackoverflow.com/a/13577924
 */
 //#define UEUM_DISABLE_WIN32_PRAGMA_WARN(nnn)
//__pragma (warning (push))
//__pragma (warning(disable : nnn))

//#define UEUM_DISABLE_WIN32_PRAGMA_WARN_END
//__pragma (warning (pop))

#define UEUM_DISABLE_WIN32_PRAGMA_WARN(nnn)
#define UEUM_DISABLE_WIN32_PRAGMA_WARN_END

#else

#define UEUM_DISABLE_WIN32_PRAGMA_WARN(nnn)
#define UEUM_DISABLE_WIN32_PRAGMA_WARN_END

#endif

/**
 *  @brief Alloc a variable in a safe way.
 *
 *  Set variable to NULL,
 *  and alloc it to specified size and cast to specified type.
 *  Set all elements to 0 with memset.
 *  Check if variable is correctly allocated.
 */
#define ueum_safe_alloc(var, type, size) \
UEUM_DISABLE_WIN32_PRAGMA_WARN(4127) \
	if ((ISUNSIGNED(size) && size == 0) || (!ISUNSIGNED(size) && size <= 0)) { \
UEUM_DISABLE_WIN32_PRAGMA_WARN_END \
		ei_stacktrace_push_msg("Can't allocate data with a negative or null size"); \
		return 0; \
	} \
	var = NULL; \
	var = (type *)malloc(size * sizeof(type)); \
	memset(var, 0, size * sizeof(type)); \
    ueum_check_alloc(var) \

#define ueum_safe_alloc_ret(var, type, size, ret) \
UEUM_DISABLE_WIN32_PRAGMA_WARN(4127) \
	if ((ISUNSIGNED(size) && size == 0) || (!ISUNSIGNED(size) && size <= 0)) { \
UEUM_DISABLE_WIN32_PRAGMA_WARN_END \
		ei_stacktrace_push_msg("Can't allocate data with a negative or null size"); \
		ret = 0; \
	} else { \
		var = NULL; \
		var = (type *)malloc(size * sizeof(type)); \
		memset(var, 0, size * sizeof(type)); \
	    if (errno == ENOMEM) { \
	        ei_stacktrace_push_errno() \
	        ueum_safe_free(var) \
	        ret = 0; \
		} else if (!var) { \
	        ei_stacktrace_push_msg("No such memory to allocate") \
			ret = 0; \
		} \
		ret = 1; \
	} \

/**
 *  @brief Alloc a variable in a safe way.
 *
 *  Set variable to NULL,
 *  and alloc it to specified size and cast to specified type.
 *  Set all elements to 0 with memset.
 *  Check if variable is correctly allocated. If not, go to specified label
 */
#define ueum_safe_alloc_or_goto(var, type, size, label) \
UEUM_DISABLE_WIN32_PRAGMA_WARN(4127) \
	if ((ISUNSIGNED(size) && size == 0) || (!ISUNSIGNED(size) && size <= 0)) { \
UEUM_DISABLE_WIN32_PRAGMA_WARN_END \
		ei_stacktrace_push_msg("Can't allocate data with a negative or null size"); \
		goto label; \
	} \
	var = NULL; \
	var = (type *)malloc(size * sizeof(type)); \
	memset(var, 0, size * sizeof(type)); \
    ueum_check_alloc_or_goto(var, label) \

/**
 *  @brief Realloc a variable in a safe way.
 *
 *  If size has to be increase, we add specified more size.
 *  If size has to be reduce, the parameter more_size has to be equal to 0.
 *  Set all elements to 0 with memset.
 *  Check if variable is correctly allocated.
 */
#define ueum_safe_realloc(var, type, old_size, more_size) \
UEUM_DISABLE_WIN32_PRAGMA_WARN(4127) \
	if (!ISUNSIGNED(old_size) && old_size < 0) { \
UEUM_DISABLE_WIN32_PRAGMA_WARN_END \
		ei_stacktrace_push_msg("Can't allocate data with a negative old_size"); \
		return 0; \
	} \
UEUM_DISABLE_WIN32_PRAGMA_WARN(4127) \
	if (old_size == 0 && ((ISUNSIGNED(more_size) && more_size == 0) || (!ISUNSIGNED(more_size) && more_size <= 0))) { \
UEUM_DISABLE_WIN32_PRAGMA_WARN_END \
		ei_stacktrace_push_msg("Can't allocate data with an old_size equal to 0 and a null or negative more_size"); \
	    return 0; \
	} \
	var = (type *)realloc(var, (old_size + more_size + 1) * sizeof(type)); \
	memset(var + old_size, 0, (more_size + 1) * sizeof(type)); \
    ueum_check_alloc(var) \

/**
 *  @brief Realloc a variable in a safe way.
 *
 *  If size has to be increase, we add specified more size.
 *  If size has to be reduce, the parameter more_size has to be equal to 0.
 *  Set all elements to 0 with memset.
 *  Check if variable is correctly allocated. If not, go to specified label
 */
#define ueum_safe_realloc_or_goto(var, type, old_size, more_size, label) \
UEUM_DISABLE_WIN32_PRAGMA_WARN(4127) \
	if (!ISUNSIGNED(old_size) && old_size < 0) { \
UEUM_DISABLE_WIN32_PRAGMA_WARN_END \
		ei_stacktrace_push_msg("Can't allocate data with a negative old_size '%d'", (int)old_size); \
	    goto label; \
	} \
UEUM_DISABLE_WIN32_PRAGMA_WARN(4127) \
	if (old_size == 0 && ((ISUNSIGNED(more_size) && more_size == 0) || (!ISUNSIGNED(more_size) && more_size <= 0))) { \
UEUM_DISABLE_WIN32_PRAGMA_WARN_END \
		ei_stacktrace_push_msg("Can't allocate data with an old_size equal to 0 and a null or negative more_size '%d'", (int)more_size); \
	    goto label; \
	} \
	var = (type *)realloc(var, (old_size + more_size + 1) * sizeof(type)); \
	memset(var + old_size, 0, (more_size + 1) * sizeof(type)); \
    ueum_check_alloc_or_goto(var, label) \

/**
 *  @brief Check if a variable is correctly allocated.
 *
 *  Check if 'errno' variable is equal to value ENOMEM ;
 *  if it is, we add an error message to ei_stacktrace.
 *  Some OS didn't update 'errno' variable in this case, so we check
 *  also if the variable is set to NULL ; if it is, we add an error
 *  message to ei_stacktrace.
 */
#define ueum_check_alloc(var) \
	if (errno == ENOMEM) { \
        ei_stacktrace_push_errno() \
        ueum_safe_free(var) \
        return 0; \
	} else if (!var) { \
        ei_stacktrace_push_msg("No such memory to allocate") \
		return 0; \
	} \

/**
 *  @brief Same behavior than CHECK_ALLOC, but if var isn't
 *  correctly allocated, go to specified label.
 */
#define ueum_check_alloc_or_goto(var, label) \
	if (errno == ENOMEM) { \
        ei_stacktrace_push_errno() \
        ueum_safe_free(var) \
        goto label; \
	} else if (!var) { \
        ei_stacktrace_push_msg("No such memory to allocate") \
		goto label; \
	} \

/**
 *  @brief Free a variable in a safe way.
 *
 *  Check if variable isn't set to NULL ;
 *  if it is, free the variable and set it to NULL.
 */
#define ueum_safe_free(var) \
	if (var) { \
		free((void *)var); \
		var = NULL; \
	} \

#define ueum_safe_str_free(str) \
	if (str) { \
		if (strcmp(str, "") != 0) { \
			free((void *)str); \
			str = NULL; \
		} \
	} \

/**
 *  @brief Close a file in a safe way.
 *
 *  Check if the file descriptor isn't set to NULL ;
 *  if it is, close the file descriptor and set it to NULL.
 */
#define ueum_safe_fclose(fd) \
	if (fd) { \
		fclose(fd); \
		fd = NULL; \
	} \

#endif
