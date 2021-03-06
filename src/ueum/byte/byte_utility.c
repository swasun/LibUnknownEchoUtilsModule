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

#include <ueum/byte/byte_utility.h>
#include <ueum/safe/safe_alloc.h>
#include <ei/ei.h>

#include <string.h>

unsigned char *ueum_bytes_create_from_string(const char *str) {
    unsigned char *new_bytes;
    size_t len;

    new_bytes = NULL;
    len = strlen(str);

    ueum_safe_alloc(new_bytes, unsigned char, len);
    memcpy(new_bytes, str, len * sizeof(unsigned char));

    return new_bytes;
}

unsigned char *ueum_bytes_create_from_bytes(unsigned char *bytes, size_t size) {
    unsigned char *new_bytes;

    new_bytes = NULL;
    ueum_safe_alloc(new_bytes, unsigned char, size);
    memcpy(new_bytes, bytes, size * sizeof(unsigned char));

    return new_bytes;
}

void ueum_int_to_bytes(int n, unsigned char *bytes) {
    bytes[0] = (n >> 24) & 0xFF;
    bytes[1] = (n >> 16) & 0xFF;
    bytes[2] = (n >> 8) & 0xFF;
    bytes[3] = n & 0xFF;
}

bool ueum_bytes_to_int(unsigned char *bytes, int *n) {
    ei_check_parameter_or_return(bytes);

    *n = (bytes[0] << 24) | (bytes[1] << 16) | (bytes[2] << 8) | bytes[3];

    return true;
}

bool ueum_bytes_starts_with(unsigned char *data, size_t data_size, unsigned char *target, size_t target_size) {
    ei_check_parameter_or_return(data);
    ei_check_parameter_or_return(data_size > 0);
    ei_check_parameter_or_return(target);
    ei_check_parameter_or_return(target_size);

    if (data_size < target_size) {
        ei_logger_warn("Target > than data. The comparaison will be performed with the data size and not the target size.");
        return memcmp(data, target, data_size) == 0;
    }

    return memcmp(data, target, target_size) == 0;
}

bool ueum_bytes_contains(unsigned char *data, size_t data_size, unsigned char *target, size_t target_size) {
    size_t i, counter;

    ei_check_parameter_or_return(data);
    ei_check_parameter_or_return(data_size > 0);
    ei_check_parameter_or_return(target);
    ei_check_parameter_or_return(target_size);

    if (data_size < target_size) {
        ei_logger_warn("Target > than data.");
        return false;
    }

    counter = 0;

    for (i = 0; i < data_size; i++) {
        if (data[i] == target[counter]) {
            counter++;
        } else {
            if (counter > 0) {
                i -= counter;
            }
            counter = 0;
        }
        if (counter == target_size) {
            return true;
        }
    }

    return false;
}
