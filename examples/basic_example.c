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

#include <ueum/ueum.h> /* include LibUnknownEchoUtilsModule */
#include <ei/ei.h> /* include LibErrorInterceptor */

int main() {
    char *data;

    ei_init(); /* initialize LibErrorInterceptor */

    /* use LibUnknownEchoUtilsModule */

    /* return the content of the file */
    data = ueum_read_file("test.txt");

    /* free data only if it's allocated */
    ueum_safe_free(data);

    /**
     * If the file test.txt doesn't exist or cannot be
     * opened, libueum will used libei to record an error
     * in the stacktrace of the current thread.
     * If so, we can print the stacktrace.
     */
    if (ei_stacktrace_is_filled()) {
        ei_stacktrace_print_all();
    }

    ei_uninit(); /* uninitialize LibErrorInterceptor */

    return 0;
}
