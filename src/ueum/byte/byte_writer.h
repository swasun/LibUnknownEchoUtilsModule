/******************************************************************************************
 * Copyright (C) 2018 by Charly Lamothe													                          *
 *																						                                            *
 * This file is part of LibUnknownEchoUtilsModule.										                    *
 *																						                                            *
 *   LibUnknownEchoUtilsModule is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by				          *
 *   the Free Software Foundation, either version 3 of the License, or					          *
 *   (at your option) any later version.												                          *
 *																						                                            *
 *   LibUnknownEchoUtilsModule is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of						            *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						            *
 *   GNU General Public License for more details.										                      *
 *																						                                            *
 *   You should have received a copy of the GNU General Public License					          *
 *   along with LibUnknownEchoUtilsModule.  If not, see <http://www.gnu.org/licenses/>.   *
 ******************************************************************************************/

 /**
  *  @file      byte_writer.h
  *  @brief     Functions to append different data types into a byte stream.
  *  @author    Charly Lamothe
  *  @copyright GNU Public License.
  *  @see       byte_stream_struct.h
  *  @see       byte_stream.h
  *  @see       byte_reader.h
  */

#ifndef UNKNOWNECHOUTILSMODULE_BYTE_WRITER_H
#define UNKNOWNECHOUTILSMODULE_BYTE_WRITER_H

#include <ueum/compiler/bool.h>
#include <ueum/byte/byte_stream_struct.h>

#include <stddef.h>

bool ueum_byte_writer_append_bytes(ueum_byte_stream *stream, unsigned char *bytes, size_t bytes_len);

bool ueum_byte_writer_append_string(ueum_byte_stream *stream, const char *string);

bool ueum_byte_writer_append_byte(ueum_byte_stream *stream, unsigned char byte);

bool ueum_byte_writer_append_int(ueum_byte_stream *stream, int n);

bool ueum_byte_writer_append_long(ueum_byte_stream *stream, long n);

bool ueum_byte_writer_append_stream(ueum_byte_stream *stream, ueum_byte_stream *to_copy);

#endif
