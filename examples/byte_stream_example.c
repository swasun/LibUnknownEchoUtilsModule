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

int main() {
    ueum_byte_stream *x, *y, *z;

    ei_init_or_die();
    ei_logger_use_symbol_levels();

    /* Allocate streams */
    ei_logger_info("Creating x, y and z byte streams");
    x = ueum_byte_stream_create();
    y = ueum_byte_stream_create();
    z = ueum_byte_stream_create();

    /* Create stream x with Hello world content */
    ei_logger_info("Adding Hello world string to the stream x");
    ueum_byte_writer_append_string(x, "Hello world !");

    /* Copy x stream to y */
    ei_logger_info("Write x stream to y stream");
    ueum_byte_writer_append_stream(y, x);

    /* Set the virtual cursor of y to the begining */
    ueum_byte_stream_set_position(y, 0);

    /* Read next datas as a stream and copy it to z */
    ei_logger_info("Read y stream and copy it to z stream");
    ueum_byte_read_next_stream(y, z);

    /**
     * Print all streams in hexadecimals format.
     * It's excepted that x is equal to z. y is a little bigger
     * because it contains the size of x.
     */
    ei_logger_info("Print the content of the streams in hex format. y is a little bigger that x and z because it contains the size of x.");
    ueum_byte_stream_print_hex(x, stdout);
    ueum_byte_stream_print_hex(y, stdout);
    ueum_byte_stream_print_hex(z, stdout);

    /* Clean-up streams */
    ueum_byte_stream_destroy(x);
    ueum_byte_stream_destroy(y);
    ueum_byte_stream_destroy(z);

    if (ei_stacktrace_is_filled()) {
        ei_logger_error("Error(s) occurred with the following stacktrace(s):");
        ei_stacktrace_print_all();
    }

    ei_uninit();

    return 0;
}
