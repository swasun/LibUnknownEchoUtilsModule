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

/**
 *  @file      string_vector.h
 *  @brief     A container that represent a vector of strings.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef UNKNOWNECHOUTILSMODULE_STRING_VECTOR_H
#define UNKNOWNECHOUTILSMODULE_STRING_VECTOR_H

#include <ueum/compiler/bool.h>

#include <stdio.h>

typedef struct {
    char **elements;
    int number;
} ueum_string_vector;

ueum_string_vector *ueum_string_vector_create_empty();

void ueum_string_vector_clean_up(ueum_string_vector *v);

void ueum_string_vector_destroy(ueum_string_vector *v);

bool ueum_string_vector_append(ueum_string_vector *v, const char *new_string);

bool ueum_string_vector_append_vector(ueum_string_vector *from, ueum_string_vector *to);

bool ueum_string_vector_remove(ueum_string_vector *v, int index);

int ueum_string_vector_size(ueum_string_vector *v);

char *ueum_string_vector_get(ueum_string_vector *v, int index);

bool ueum_string_vector_is_empty(ueum_string_vector *v);

bool ueum_string_vector_print(ueum_string_vector *v, FILE *out);

bool ueum_string_vector_contains(ueum_string_vector *v, char *target);

#endif
