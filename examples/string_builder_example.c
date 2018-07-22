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

#include <ueum/ueum.h>
#include <ei/ei.h>

#include <string.h>

int main() {
    ueum_string_builder *builder;

    ei_init_or_die();
    ei_logger_use_symbol_levels();
    
    ei_logger_info("Creating string builder...");
    if ((builder = ueum_string_builder_create()) == NULL) {
        ei_stacktrace_push_msg("Failed to create new string builder");
        goto clean_up;
    }

    ei_logger_info("Append string to builder...");
    if (!ueum_string_builder_append(builder, "Hello world !", strlen("Hello world !"))) {
        ei_stacktrace_push_msg("Failed to append string to builder");
        goto clean_up;
    }

    ei_logger_info("The string builder contains %ld chars with data: %s",
        ueum_string_builder_get_position(builder),
        ueum_string_builder_get_data(builder)
    );

clean_up:
    ueum_string_builder_destroy(builder);
    if (ei_stacktrace_is_filled()) {
        ei_logger_error("Error(s) occurred with the following stacktrace(s):");
        ei_stacktrace_print_all();
    }
    ei_uninit();
    return 0;
}
