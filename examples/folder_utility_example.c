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

#include <stdlib.h>

int main() {
    const char *directory_name, *file_name, *data;
    char *current_directory, **directories;
    int i, files_count;

    current_directory = NULL;
    directories = NULL;
    files_count = 0;

    ei_init_or_die();
    ei_logger_use_symbol_levels();

    directory_name = "hello";
    file_name = "hello/hello";
    data = "hello";

    ei_logger_info("Getting current directory name...");
    if ((current_directory = ueum_get_current_dir()) == NULL) {
        ei_stacktrace_push_msg("Failed to get current directory name");
        goto clean_up;
    }
    ei_logger_info("The name of the current directory is: %s", current_directory);

    ei_logger_info("Checking if the directory exists...");
    if (!ueum_is_dir_exists(directory_name)) {
        ei_logger_info("%s directory doesn't exist. Creating...", directory_name);
        if (!ueum_create_folder(directory_name)) {
            ei_stacktrace_push_msg("Failed to create folder %s", directory_name);
            goto clean_up;
        }
        ei_logger_info("%s created.", directory_name);
        ei_logger_info("Creating file %s with content %s...", file_name, data);
        if (!ueum_write_file(file_name, data)) {
            ei_stacktrace_push_msg("Failed to write to file %s", file_name);
            goto clean_up;
        }
        ei_logger_info("%s wrote.", file_name);
    } else {
        ei_logger_info("The directory already %s exist and contains %d file(s)", directory_name, ueum_count_dir_files(directory_name, true));
        if ((directories = ueum_list_directory(directory_name, &files_count, true)) == NULL) {
            ei_stacktrace_push_msg("Failed to list the content of the directory %s", directory_name);
            goto clean_up;
        }
        ei_logger_info("The directory %s contains the following files:", directory_name);
        for (i = 0; i < files_count; i++) {
            printf("%s\n", directories[i]);
        }
        ei_logger_info("Removing file %s...", file_name);
        remove(file_name);
        ei_logger_info("Removing directory %s...", directory_name);
        remove(directory_name);
    }

clean_up:
    ueum_safe_free(current_directory);
    if (directories) {
        for (i = 0; i < files_count; i++) {
            ueum_safe_free(directories[i]);
        }
        free((void *)directories);
    }
    if (ei_stacktrace_is_filled()) {
        ei_logger_error("Error(s) occurred with the following stacktrace(s):");
        ei_stacktrace_print_all();
    }
    ei_uninit();
    return 0;
}
