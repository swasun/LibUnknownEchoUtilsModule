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

#include <ueum/byte/hex_utility.h>
#include <ueum/safe/safe_alloc.h>

#include <string.h>

char *ueum_bytes_to_hex(unsigned char *bytes, size_t bytes_count) {
    char *hex;
    size_t i;

    ei_check_parameter_or_return(bytes);
    ei_check_parameter_or_return(bytes_count > 0);

    hex = NULL;

	ueum_safe_alloc(hex, char, bytes_count * 2 + 3);

    strcat(hex, "0x");
    for (i = 0; i < bytes_count; i++) {
        sprintf(hex + (i * 2) + 2, "%02x", bytes[i]);
    }

    return hex;
}

bool ueum_hex_print(unsigned char *bytes, size_t bytes_count, FILE *fd) {
    char *hex;

    ei_check_parameter_or_return(bytes);
    ei_check_parameter_or_return(bytes_count > 0);
    ei_check_parameter_or_return(fd);

    if ((hex = ueum_bytes_to_hex(bytes, bytes_count)) == NULL) {
        ei_stacktrace_push_msg("Failed to convert input bytes to hex string");
        return false;
    }

    fprintf(fd, "%s\n", hex);

    ueum_safe_free(hex);

    return true;
}
