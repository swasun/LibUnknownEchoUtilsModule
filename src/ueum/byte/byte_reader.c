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

#include <ueum/byte/byte_reader.h>
#include <ueum/byte/byte_writer.h>
#include <ei/ei.h>
#include <ueum/safe/safe_alloc.h>
#include <ueum/string/string_utility.h>

#include <string.h>
#include <stddef.h>

bool ueum_byte_read_is_int(ueum_byte_stream *stream, int position, int n) {
    int read;

    if (!stream || !stream->bytes) {
        return false;
    }

    if ((size_t)position + 3 >= stream->size) {
        ei_stacktrace_push_msg("Failed to get int because this would cause a buffer underflow");
        return false;
    }

    read = (stream->bytes[position] << 24) |
        (stream->bytes[position+1] << 16) |
        (stream->bytes[position+2] << 8) |
        stream->bytes[position+3];

    return read == n;
}

bool ueum_byte_read_next_int(ueum_byte_stream *stream, int *n) {
    if (!stream || !stream->bytes) {
        return false;
    }

    if (stream->position + 3 >= stream->size) {
        ei_stacktrace_push_msg("Failed to get int because this would cause a buffer underflow");
        return false;
    }

    *n = (stream->bytes[stream->position] << 24) |
        (stream->bytes[stream->position+1] << 16) |
        (stream->bytes[stream->position+2] << 8) |
        stream->bytes[stream->position+3];

    stream->position += 4;

    return true;
}

bool ueum_byte_read_next_bytes(ueum_byte_stream *stream, unsigned char **bytes, size_t len) {
    if (!stream || !stream->bytes) {
        return false;
    }

    if (stream->position + len >= stream->size) {
        ei_stacktrace_push_msg("Failed to get next bytes because this would cause a buffer underflow");
        return false;
    }

    *bytes = NULL;

    ueum_safe_alloc(*bytes, unsigned char, len);
    memcpy(*bytes, stream->bytes + stream->position, len * sizeof(unsigned char));
    stream->position += len;

    return true;
}

bool ueum_byte_read_next_stream(ueum_byte_stream *stream, ueum_byte_stream *new_stream) {
    int read_int;
    unsigned char *read_bytes;

    if (!stream || !stream->bytes) {
        return false;
    }

    ei_check_parameter_or_return(new_stream);

    if (!ueum_byte_read_next_int(stream, &read_int)) {
        ei_stacktrace_push_msg("Failed to read new stream size");
        return false;
    }

    if (!ueum_byte_read_next_bytes(stream, &read_bytes, (size_t)read_int)) {
        ei_stacktrace_push_msg("Failed to read new stream content");
        return false;
    }

    if (!ueum_byte_writer_append_bytes(new_stream, read_bytes, (size_t)read_int)) {
        ueum_safe_free(read_bytes);
        ei_stacktrace_push_msg("Failed to write new stream content");
        return false;
    }

    ueum_safe_free(read_bytes);

    return true;
}

bool ueum_byte_read_next_string(ueum_byte_stream *stream, const char **string, size_t len) {
    unsigned char *bytes;

    ei_check_parameter_or_return(stream);
    ei_check_parameter_or_return(len > 0);

    if (!ueum_byte_read_next_bytes(stream, &bytes, len)) {
        ei_stacktrace_push_msg("Failed to read next %ld bytes", len);
        return false;
    }

    if ((*string = ueum_string_create_from_bytes(bytes, len)) == NULL) {
        ei_stacktrace_push_msg("Failed to convert %ld bytes to string", len);
        ueum_safe_free(bytes);
        return false;
    }

    ueum_safe_free(bytes);

    return true;
}

/*bool ueum_byte_read_remaining_bytes(ueum_byte_stream *stream, unsigned char **bytes, size_t *len) {
    size_t remaining_bytes_size;

    if (!stream || !stream->bytes) {
        return false;
    }

    ei_logger_debug("stream->size: %ld", stream->size);
    ei_logger_debug("stream->position: %ld", stream->position);
    ei_logger_debug("stream->size - stream->position: %ld", stream->size - stream->position);

    if ((remaining_bytes_size = stream->size - stream->position) <= 0) {
        ei_stacktrace_push_msg("There's no remaining bytes to read");
        return false;
    }

    if (!ueum_byte_read_next_bytes(stream, bytes, remaining_bytes_size)) {
        ei_stacktrace_push_msg("Failed to read remaining bytes");
        return false;
    }

    return true;
}*/
