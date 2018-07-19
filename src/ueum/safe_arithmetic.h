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

#ifndef UNKNOWNECHOUTILSMODULE_SAFE_ARITHMETIC_H
#define UNKNOWNECHOUTILSMODULE_SAFE_ARITHMETIC_H

#include <ueum/overflow.h>
#include <ueum/typename.h>

#include <ei/ei.h>

#define ueum_safe_add(a, b, res) \
	__ueum_safe_add_internal(a, b, res, return 0); \

#define ueum_safe_add_or_goto(a, b, res, label) \
	__ueum_safe_add_internal(a, b, res, goto label); \

#define ueum_safe_add3(a, b, c, res) \
	__ueum_safe_add3_internal(a, b, c, res, return 0); \

#define ueum_safe_add3_or_goto(a, b, c, res, label) \
	__ueum_safe_add3_internal(a, b, c, res, goto label); \

#define ueum_safe_sub(a, b, res) \
	__ueum_safe_sub_internal(a, b, res, return 0); \

#define ueum_safe_sub_or_goto(a, b, res, label) \
	__ueum_safe_sub_internal(a, b, res, goto label); \

#define ueum_safe_mul(a, b, res) \
	__ueum_safe_mul_internal(a, b, res, return 0); \

#define ueum_safe_mul_or_goto(a, b, res, label) \
	__ueum_safe_mul_internal(a, b, res, goto label); \

#define __ueum_safe_add_internal(a, b, res, rollback_expression) \
	if (ueum__add_overflow(a, b, res)) { \
		ei_stacktrace_push_msg("Arithmetic overflow detected when performing: (%s)=(%s)+(%s)", ueum_typename(res), \
			ueum_typename(a), ueum_typename(b)); \
		rollback_expression; \
	} \

#define __ueum_safe_add3_internal(a, b, c, res, rollback_expression) \
	if (ueum__add3_overflow(a, b, c, res)) { \
		ei_stacktrace_push_msg("Arithmetic overflow detected when performing: (%s)=(%s)+(%s)+(%s)", ueum_typename(res), \
			ueum_typename(a), ueum_typename(b), ueum_typename(c)); \
		rollback_expression; \
	} \

#define __ueum_safe_sub_internal(a, b, res, rollback_expression) \
	if (ueum__sub_overflow(a, b, res)) { \
		ei_stacktrace_push_msg("Arithmetic overflow detected when performing: (%s)=(%s)-(%s)", ueum_typename(res), \
			ueum_typename(a), ueum_typename(b)); \
		rollback_expression; \
	} \

#define __ueum_safe_mul_internal(a, b, res, rollback_expression) \
	if (ueum__mul_overflow(a, b, res)) { \
		ei_stacktrace_push_msg("Arithmetic overflow detected when performing: (%s)=(%s)*(%s)", ueum_typename(res), \
			ueum_typename(a), ueum_typename(b)); \
		rollback_expression; \
	} \

#endif
