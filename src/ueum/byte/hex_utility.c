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

#include <ueum/byte/hex_utility.h>
#include <ueum/alloc.h>

#include <string.h>

char *ueum_bytes_to_hex(unsigned char *bytes, size_t bytes_count) {
    char *hex;
    size_t i;

    hex = NULL;

	ueum_safe_alloc(hex, char, bytes_count * 2 + 3);

    strcat(hex, "0x");
    for(i = 0; i < bytes_count; i++) {
        sprintf(hex + (i * 2), "%02x", bytes[i]);
    }

    return hex;
}
