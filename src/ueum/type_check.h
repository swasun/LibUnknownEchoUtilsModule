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

#ifndef UNKNOWNECHOUTILSMODULE_TYPE_CHECK_H
#define UNKNOWNECHOUTILSMODULE_TYPE_CHECK_H

/* Compile-time assertion that check if 'x' and 'y' are equivalent types */

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

#endif
