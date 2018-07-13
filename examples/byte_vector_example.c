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

#include <stdio.h>

int main() {
    ueum_byte_vector *data;

    data = NULL;

    ei_init();

    ei_logger_info("Creating an empty byte vector");
    if ((data = ueum_byte_vector_create_empty()) == NULL) {
        ei_stacktrace_push_msg("Failed to create empty byte vector data");
        goto clean_up;
    }

    ei_logger_info("Append hello world string");
    if (!ueum_byte_vector_append_string(data, "Hello world !")) {
        ei_stacktrace_push_msg("Failed to append string to byte vector data");
        goto clean_up;
    }

    ei_logger_info("Checking is byte vector is empty");
    if (ueum_byte_vector_is_empty(data)) {
        ei_stacktrace_push_msg("byte vector data is empty but it shouldn't")
        goto clean_up;
    }

    ei_logger_info("The byte vector 'data' contains:");
    ueum_byte_vector_print(data, stdout);

clean_up:
    ueum_byte_vector_destroy(data);
    if (ei_stacktrace_is_filled()) {
        ei_stacktrace_print_all();
    }
    ei_uninit();
    return 0;
}
