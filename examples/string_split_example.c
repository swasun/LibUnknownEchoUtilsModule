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

#include <ueum/ueum.h>
#include <ei/ei.h>

int main() {
    const char *string, *delimiter;
    ueum_string_vector *vector;

	ei_init_or_die();
    ei_logger_use_symbol_levels();
    
    string = "oneUEtwoUEtree";
    delimiter = "UE";

    ei_logger_info("Splitting string '%s' with delimiter '%s'...", string, delimiter);
    if ((vector = ueum_string_split(string, delimiter)) == NULL) {
        ei_stacktrace_push_msg("Failed to split string");
        goto clean_up;
    }

    ei_logger_info("Split output:");
    ueum_string_vector_print(vector, stdout);

clean_up:
    ueum_string_vector_destroy(vector);
    if (ei_stacktrace_is_filled()) {
        ei_logger_error("Error(s) occurred with the following stacktrace(s):");
        ei_stacktrace_print_all();
    }
    ei_uninit();
    return 0;
}
