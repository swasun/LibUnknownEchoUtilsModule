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

#include <ueum/container/byte_vector.h>
#include <ueum/byte/byte_utility.h>
#include <ueum/safe/safe_alloc.h>
#include <ei/ei.h>

#include <string.h>

static ueum_byte_vector_element *new_element(unsigned char *data, size_t size) {
    ueum_byte_vector_element *element;

    element = NULL;

    ueum_safe_alloc(element, ueum_byte_vector_element, 1);
    element->data = data;
    element->size = size;

    return element;
}

ueum_byte_vector *ueum_byte_vector_create_empty() {
    ueum_byte_vector *vector;

    vector = NULL;

    ueum_safe_alloc(vector, ueum_byte_vector, 1);

    vector->elements = NULL;
    vector->number = 0;

    return vector;
}

void ueum_byte_vector_clean_up(ueum_byte_vector *vector) {
    int i;

    if (!vector) {
        return;
    }

    for (i = 0; i < vector->number; i++) {
        if (vector->elements[i]) {
            ueum_safe_free(vector->elements[i]->data);
            ueum_safe_free(vector->elements[i]);
        }
    }
    ueum_safe_free(vector->elements);
    vector->number = 0;
}

void ueum_byte_vector_destroy(ueum_byte_vector *vector) {
    int i;

    if (!vector) {
        return;
    }

    if (vector->elements) {
        for (i = 0; i < vector->number; i++) {
            if (vector->elements[i]) {
                ueum_safe_free(vector->elements[i]->data);
                ueum_safe_free(vector->elements[i]);
            }
        }
        ueum_safe_free(vector->elements);
    }

    ueum_safe_free(vector);
}

bool ueum_byte_vector_append_string(ueum_byte_vector *vector, const char *new_string) {
    int i;

    ei_check_parameter_or_return(vector);

    if (!vector->elements) {
        ueum_safe_alloc(vector->elements, ueum_byte_vector_element *, 1);
        vector->elements[0] = new_element(ueum_bytes_create_from_string(new_string), strlen(new_string));
        vector->number++;
    } else {
        for (i = 0; i < vector->number; i++) {
            if (!vector->elements[i]) {
                vector->elements[i] = new_element(ueum_bytes_create_from_string(new_string), strlen(new_string));
                return true;
            }
        }

        ueum_safe_realloc(vector->elements, ueum_byte_vector_element *, vector->number, 1);
        vector->elements[vector->number] = new_element(ueum_bytes_create_from_string(new_string), strlen(new_string));
        vector->number++;
    }

    return true;
}

bool ueum_byte_vector_append_bytes(ueum_byte_vector *vector, unsigned char *new_bytes, size_t new_bytes_size) {
    int i;

    ei_check_parameter_or_return(vector);

    if (!vector->elements) {
        ueum_safe_alloc(vector->elements, ueum_byte_vector_element *, 1);
        vector->elements[0] = new_element(ueum_bytes_create_from_bytes(new_bytes, new_bytes_size), new_bytes_size);
        vector->number++;
    } else {
        for (i = 0; i < vector->number; i++) {
            if (!vector->elements[i]) {
                vector->elements[i] = new_element(ueum_bytes_create_from_bytes(new_bytes, new_bytes_size), new_bytes_size);
                return true;
            }
        }

        ueum_safe_realloc(vector->elements, ueum_byte_vector_element *, vector->number, 1);
        vector->elements[vector->number] = new_element(ueum_bytes_create_from_bytes(new_bytes, new_bytes_size), new_bytes_size);
        vector->number++;
    }

    return true;
}

bool ueum_byte_vector_append_vector(ueum_byte_vector *from, ueum_byte_vector *to) {
    int i;
    ueum_byte_vector_element *current_element;

    ei_check_parameter_or_return(from);
    ei_check_parameter_or_return(to);

    for (i = 0; i < from->number; i++) {
        current_element = ueum_byte_vector_get(from, i);
        if (!ueum_byte_vector_append_bytes(to, current_element->data, current_element->size)) {
            return false;
        }
    }

    return true;
}

bool ueum_byte_vector_remove(ueum_byte_vector *vector, int index) {
    if (!vector) {
        return true;
    }

    if (!vector->elements) {
        return true;
    }

    if (ueum_byte_vector_size(vector) < index) {
        ei_stacktrace_push_msg("Index out of range");
        return false;
    }

    ueum_safe_free(vector->elements[index]);

    return true;
}

int ueum_byte_vector_size(ueum_byte_vector *vector) {
    if (!vector) {
        return -1;
    }

    if (!vector->elements) {
        return -1;
    }

    return vector->number;
}

ueum_byte_vector_element *ueum_byte_vector_get(ueum_byte_vector *vector, int index) {
    ei_check_parameter_or_return(vector);
    ei_check_parameter_or_return(vector->elements);

    if (ueum_byte_vector_size(vector) < index) {
        ei_stacktrace_push_msg("Index out of range");
        return NULL;
    }

    return vector->elements[index];
}

bool ueum_byte_vector_is_empty(ueum_byte_vector *vector) {
    ei_check_parameter_or_return(vector);

    return !vector->elements || vector->number <= 0;
}

bool ueum_byte_vector_print(ueum_byte_vector *vector, FILE *out) {
    int i;
    size_t j;

    ei_check_parameter_or_return(vector);
    ei_check_parameter_or_return(out);

    if (ueum_byte_vector_is_empty(vector)) {
        return false;
    }

    for (i = 0; i < vector->number; i++) {
        for (j = 0; j < vector->elements[i]->size; j++) {
            fprintf(out, "%c", vector->elements[i]->data[j]);
        }
        fprintf(out, "\n");
    }

    return true;
}

bool ueum_byte_vector_print_element(ueum_byte_vector *vector, int index, FILE *out) {
    ueum_byte_vector_element *element;
    size_t i;

    if ((element = ueum_byte_vector_get(vector, index)) == NULL) {
        ei_stacktrace_push_msg("Failed to found element at index %d", index);
        return false;
    }

    for (i = 0; i < element->size; i++) {
        fprintf(out, "%c", element->data[i]);
    }
    fprintf(out, "\n");

    return true;
}

bool ueum_byte_vector_contains(ueum_byte_vector *vector, unsigned char *target, size_t target_size) {
    int i;

    ei_check_parameter_or_return(vector);
    ei_check_parameter_or_return(target);

    if (vector->number == 0) {
        return false;
    }

    for (i = 0; i < vector->number; i++) {
        if (vector->elements[i] && memcmp(vector->elements[i]->data, target, target_size) == 0) {
            return true;
        }
    }

    return false;
}

bool ueum_byte_vector_element_print_string(ueum_byte_vector_element *element, FILE *out) {
    size_t i;

    ei_check_parameter_or_return(element);
    ei_check_parameter_or_return(element->data);
    ei_check_parameter_or_return(element->size);
    ei_check_parameter_or_return(out);

    for (i = 0; i < element->size; i++) {
        fprintf(out, "%c", element->data[i]);
    }
    fprintf(out, "\n");

    return true;
}
