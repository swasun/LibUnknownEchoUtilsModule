/******************************************************************************************
 * Copyright (C) 2018 by Charly Lamothe                        	                          *
 *                                                                                        *
 * This file is part of LibUnknownEchoUtilsModule.                                        *
 *                                                                                        *
 *   LibUnknownEchoUtilsModule is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by                 *
 *   the Free Software Foundation, either version 3 of the License, or        	          *
 *   (at your option) any later version.                                                  *
 *                                                                                        *
 *   LibUnknownEchoUtilsModule is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of                       *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                        *
 *   GNU General Public License for more details.                                         *
 *                                                                                        *
 *   You should have received a copy of the GNU General Public License        	          *
 *   along with LibUnknownEchoUtilsModule.  If not, see <http://www.gnu.org/licenses/>.   *
 ******************************************************************************************/

#ifndef UNKNOWNECHOUTILSMODULE_BYTE_VECTOR_H
#define UNKNOWNECHOUTILSMODULE_BYTE_VECTOR_H

#include <ueum/compiler/bool.h>

#include <stdio.h>
#include <stddef.h>

typedef struct {
    unsigned char *data;
    size_t size;
} ueum_byte_vector_element;

typedef struct {
    ueum_byte_vector_element **elements;
    int number;
} ueum_byte_vector;

ueum_byte_vector *ueum_byte_vector_create_empty();

void ueum_byte_vector_clean_up(ueum_byte_vector *vector);

void ueum_byte_vector_destroy(ueum_byte_vector *vector);

bool ueum_byte_vector_append_string(ueum_byte_vector *vector, const char *new_string);

bool ueum_byte_vector_append_bytes(ueum_byte_vector *vector, unsigned char *new_bytes, size_t new_bytes_size);

bool ueum_byte_vector_append_vector(ueum_byte_vector *from, ueum_byte_vector *to);

bool ueum_byte_vector_remove(ueum_byte_vector *vector, int index);

int ueum_byte_vector_size(ueum_byte_vector *vector);

ueum_byte_vector_element *ueum_byte_vector_get(ueum_byte_vector *vector, int index);

bool ueum_byte_vector_is_empty(ueum_byte_vector *vector);

bool ueum_byte_vector_print(ueum_byte_vector *vector, FILE *out);

bool ueum_byte_vector_print_element(ueum_byte_vector *vector, int index, FILE *out);

bool ueum_byte_vector_contains(ueum_byte_vector *vector, unsigned char *target, size_t target_size);

bool ueum_byte_vector_element_print_string(ueum_byte_vector_element *element, FILE *out);

#endif
