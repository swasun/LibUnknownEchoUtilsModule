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
    const char *file_name, *out_data;
    char *read_data;

    ei_init();
    ei_logger_use_symbol_levels();

    file_name = "hello.tmp";
    out_data = "hello";

    ei_logger_info("Check if file %s exists", file_name);
    if (ueum_is_file_exists(file_name)) {
        ei_logger_info("File %s already exist. Reading...", file_name);
        if ((read_data = ueum_read_file(file_name)) == NULL) {
            ei_stacktrace_push_msg("Failed to read file %s", file_name);
            goto clean_up;
        }
        ei_logger_info("The content of the file is: %s", read_data);
        ueum_safe_free(read_data);
    } else {
        ei_logger_info("File %s doesn't exist. Writing...", file_name);
        if (!ueum_write_file(file_name, out_data)) {
            ei_stacktrace_push_msg("Failed to write to file %s", file_name);
        }
    }

clean_up:
    if (ei_stacktrace_is_filled()) {
        ei_logger_stacktrace("An error occurred with the following stacktrace :");
    }
    ei_uninit();
    return 0;
}
