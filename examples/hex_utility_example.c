/*******************************************************************************
 * Copyright (C) 2018 Charly Lamothe                                           *
 *                                                                             *
 * This file is part of LibUnknownEchoUtilsModule.                             *
 *                                                                             *
 *   Licensed under the Apache License, Version 2.0 (the "License");           *
 *   you may not use this file except in compliance with the License.          *
 *   You may obtain a copy of the License at                                   *
 *                                                                             *
 *   http://www.apache.org/licenses/LICENSE-2.0                                *
 *                                                                             *
 *   Unless required by applicable law or agreed to in writing, software       *
 *   distributed under the License is distributed on an "AS IS" BASIS,         *
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 *   See the License for the specific language governing permissions and       *
 *   limitations under the License.                                            *
 *******************************************************************************/

#include <ueum/ueum.h>
#include <ei/ei.h>

#include <string.h>

int main() {
    unsigned char *bytes;

    ei_init_or_die();
    ei_logger_use_symbol_levels();    

    ei_logger_info("Creating bytes from Hello world string...");
    if ((bytes = ueum_bytes_create_from_string("Hello world !")) == NULL) {
        ei_stacktrace_push_msg("Failed to create bytes from string");
        goto clean_up;
    }
    
    if (!ueum_hex_print(bytes, strlen("Hello world"), stdout)) {
        ei_stacktrace_push_msg("Failed to print bytes to stdout");
        goto clean_up;
    }

    ei_logger_info("Succeed !");

clean_up:
    ueum_safe_free(bytes);
    if (ei_stacktrace_is_filled()) {
        ei_logger_error("Error(s) occurred with the following stacktrace(s):");
        ei_stacktrace_print_all();
    }
    ei_uninit();
    return 0;
}
