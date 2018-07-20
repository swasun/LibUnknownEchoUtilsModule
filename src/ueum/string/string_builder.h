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
 *  @file      string_builder.h
 *  @brief     A string builder is a stream of string use to concatenate easily
 *             several types into a single string.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef UNKNOWNECHOUTILSMODULE_STRING_BUILDER_H
#define UNKNOWNECHOUTILSMODULE_STRING_BUILDER_H

#include <ueum/compiler/bool.h>

#include <stddef.h>

typedef struct {
    char *data;
    size_t max_size;
    size_t position;
} ueum_string_builder;

ueum_string_builder *ueum_string_builder_create();

ueum_string_builder *ueum_string_builder_create_size(size_t max_size);

bool ueum_string_builder_append(ueum_string_builder *s, char *data, size_t data_len);

bool ueum_string_builder_append_variadic(ueum_string_builder *s, const char *format, ...);

void ueum_string_builder_clean_up(ueum_string_builder *s);

void ueum_string_builder_destroy(ueum_string_builder *s);

char *ueum_string_builder_get_data(ueum_string_builder *s);

size_t ueum_string_builder_get_position(ueum_string_builder *s);

#endif
