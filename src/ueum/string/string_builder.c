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

#include <ueum/string/string_builder.h>
#include <ueum/safe/safe_alloc.h>
#include <ei/ei.h>

#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdarg.h>

ueum_string_builder *ueum_string_builder_create() {
    return ueum_string_builder_create_size(1);
}

ueum_string_builder *ueum_string_builder_create_size(size_t max_size) {
    ueum_string_builder *builder;

    ei_check_parameter_or_return(max_size > 0);

    builder = NULL;

    ueum_safe_alloc(builder, ueum_string_builder, 1);

    ueum_safe_alloc_or_goto(builder->data, char, max_size + 1, clean_up);

    memset(builder->data, 0, max_size);
    builder->max_size = max_size;
    builder->position = 0;

    return builder;

clean_up:
    ueum_string_builder_destroy(builder);
    return NULL;
}

bool ueum_string_builder_append(ueum_string_builder *s, char *data, size_t data_len) {
    ei_check_parameter_or_return(s);
    ei_check_parameter_or_return(data);
    ei_check_parameter_or_return(data_len > 0 && data_len != 18446744073709551615UL);

    if ((data_len + s->position) > s->max_size) {
        ueum_safe_realloc(s->data, char, s->max_size, data_len + 1);
        s->max_size += data_len + 1;
    }

    memcpy(s->data + s->position, data, data_len);

    s->position += data_len;

    return true;
}

bool ueum_string_builder_append_variadic(ueum_string_builder *s, const char *format, ...) {
    bool result;
    va_list args;
    char *buffer;

    result = false;
    buffer = NULL;

    ueum_safe_alloc(buffer, char, 8192);

    va_start(args, format);
    vsnprintf(buffer, 8192, format, args);
    va_end(args);

    if ((result = ueum_string_builder_append(s, buffer, strlen(buffer))) == false) {
        ei_stacktrace_push_msg("Failed to append concatenated args");
    }

    ueum_safe_free(buffer);

    return result;
}

void ueum_string_builder_clean_up(ueum_string_builder *s) {
    if (!s) {
        return;
    }

    if (!s->data) {
        return;
    }

    memset(s->data, 0, s->max_size);
    s->position = 0;
}

void ueum_string_builder_destroy(ueum_string_builder *s) {
    if (!s) {
        return;
    }

    ueum_safe_free(s->data);
    ueum_safe_free(s);
}

char *ueum_string_builder_get_data(ueum_string_builder *s) {
    if (!s || !s->data) {
        return NULL;
    }

    return s->data;
}

size_t ueum_string_builder_get_position(ueum_string_builder *s) {
    if (!s) {
        ei_stacktrace_push_msg("Specified string builder ptr is null");
        return 0;
    }

    return s->position;
}
