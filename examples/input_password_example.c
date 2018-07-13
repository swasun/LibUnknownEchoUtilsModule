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
#include <stdlib.h>

int main() {
    char *password;

    password = NULL;

    if (!ei_init()) {
        goto clean_up;
    }

    ei_logger_info("LibUnknownEchoUtilsModule is correctly initialized");
    
    if ((password = ueum_input_password("Enter a password: ", 32)) == NULL) {
        ei_stacktrace_push_msg("Failed to get input password");
        goto clean_up;
    }

    ei_logger_info("The password is: %s", password);

clean_up:
    ueum_safe_free(password);
    if (ei_stacktrace_is_filled()) {
        ei_logger_stacktrace("An error occurred with the following stacktrace :");
    }
    ei_uninit();
    return EXIT_SUCCESS;
}
