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

/**
 *  @file      byte_stream.h
 *  @brief     Byte stream base functions, to alloc/desalloc stream, and get/set fields.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 *  @see       byte_stream_struct.h
 *  @see       byte_reader.h
 *  @see       byte_writer.h
 */

#ifndef UNKNOWNECHOUTILSMODULE_BYTE_STREAM_H
#define UNKNOWNECHOUTILSMODULE_BYTE_STREAM_H

#include <ueum/byte/byte_stream_struct.h>
#include <ueum/compiler/bool.h>

#include <stddef.h>
#include <stdio.h>

ueum_byte_stream *ueum_byte_stream_create();

ueum_byte_stream *ueum_byte_stream_create_size(size_t limit);

void ueum_byte_stream_clean_up(ueum_byte_stream *stream);

void ueum_byte_stream_destroy(ueum_byte_stream *stream);

unsigned char *ueum_byte_stream_get_data(ueum_byte_stream *stream);

size_t ueum_byte_stream_get_position(ueum_byte_stream *stream);

bool ueum_byte_stream_set_position(ueum_byte_stream *stream, size_t position);

size_t ueum_byte_stream_get_size(ueum_byte_stream *stream);

bool ueum_byte_stream_is_empty(ueum_byte_stream *stream);

void ueum_byte_stream_print_hex(ueum_byte_stream *stream, FILE *fd);

void ueum_byte_stream_print_string(ueum_byte_stream *stream, FILE *fd);

ueum_byte_stream *ueum_byte_stream_copy(ueum_byte_stream *stream);

#endif
