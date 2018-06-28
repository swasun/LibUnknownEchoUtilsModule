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
    ueum_byte_stream *x, *y, *z;

    ei_init();

    /* Allocate streams */
    x = ueum_byte_stream_create();
    y = ueum_byte_stream_create();
    z = ueum_byte_stream_create();

    /* Create stream x with Hello world content */
    ueum_byte_writer_append_string(x, "Hello world !");

    /* Copy x stream to y */
    ueum_byte_writer_append_stream(y, x);

    /* Set the virtual cursor of y to the begining */
    ueum_byte_stream_set_position(y, 0);

    /* Read next datas as a stream and copy it to z */
    ueum_byte_read_next_stream(y, z);

    /**
     * Print all streams in hexadecimals format.
     * It's excepted that x is equal to z. y is a little bigger
     * because it contains the size of x.
     */
    ueum_byte_stream_print_hex(x, stdout);
    ueum_byte_stream_print_hex(y, stdout);
    ueum_byte_stream_print_hex(z, stdout);

    /* Clean-up streams */
    ueum_byte_stream_destroy(x);
    ueum_byte_stream_destroy(y);
    ueum_byte_stream_destroy(z);

    ei_uninit();

    return 0;
}
