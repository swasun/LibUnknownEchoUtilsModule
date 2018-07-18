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

#include <ueum/ueum.h>
#include <ei/ei.h>

int main() {
    ueum_string_vector *data;

    data = NULL;

    ei_init_or_die();
    ei_logger_use_symbol_levels();

    ei_logger_info("Creating an empty string vector");
    if ((data = ueum_string_vector_create_empty()) == NULL) {
        ei_stacktrace_push_msg("Failed to create empty string vector data");
        goto clean_up;
    }

    ei_logger_info("string hello world string");
    if (!ueum_string_vector_append(data, "Hello world !")) {
        ei_stacktrace_push_msg("Failed to string string to string vector data");
        goto clean_up;
    }

    ei_logger_info("Checking is string vector is empty");
    if (ueum_string_vector_is_empty(data)) {
        ei_stacktrace_push_msg("string vector data is empty but it shouldn't")
        goto clean_up;
    }

    ei_logger_info("The string vector isn't empty and contains %d element", ueum_string_vector_size(data));

    ei_logger_info("The string vector 'data' contains:");
    ueum_string_vector_print(data, stdout);

clean_up:
    ueum_string_vector_destroy(data);
    if (ei_stacktrace_is_filled()) {
        ei_logger_error("Error(s) occurred with the following stacktrace(s):");
        ei_stacktrace_print_all();
    }
    ei_uninit();
    return 0;
}
