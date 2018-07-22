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

#include <ueum/console/color.h>
#include <ueum/string/string_utility.h>
#include <ueum/safe/safe_alloc.h>

#include <stdio.h>
#include <string.h>
#include <stddef.h>

static bool color_is_valid_attribute(int color_id) {
    return color_id == 0 || color_id == 1 || color_id == 2 ||
        color_id == 3 || color_id == 4 || color_id == 5 ||
        color_id == 6 || color_id == 7 || color_id == 8;
}

static bool color_is_valid_foreground(int color_id) {
    return color_id == 30 || color_id == 31 || color_id == 32 ||
        color_id == 33 || color_id == 34 || color_id == 35 ||
        color_id == 36 || color_id == 37;
}

static bool color_is_valid_background(int color_id) {
    return color_id == 40 || color_id == 41 || color_id == 42 ||
        color_id == 43 || color_id == 44 || color_id == 45 ||
        color_id == 46 || color_id == 47;
}

char *ueum_colorize_string(const char *string, int attribute_id, int foreground_id, int background_id) {
    char *colored, *attribute, *foreground, *background;
    size_t colored_length, string_length;

    colored = NULL;
    attribute = NULL;
    foreground = NULL;
    background = NULL;
    string_length = strlen(string);

    colored_length = 8 + string_length + strlen(UNKNOWNECHOUTILSMODULE_COLOR_ESCAPE_RESET);

    if (color_is_valid_attribute(attribute_id)) {
        colored_length += 2;
        ueum_safe_alloc(attribute, char, 13);
        sprintf(attribute, "%d", attribute_id);
    } else {
        attribute = ueum_string_create_from("");
    }

    if (color_is_valid_foreground(foreground_id)) {
        colored_length += 2;
        ueum_safe_alloc(foreground, char, 13);
        sprintf(foreground, ";%d", foreground_id);
    } else {
        foreground = ueum_string_create_from("");
    }

    if (color_is_valid_background(background_id)) {
        colored_length += 2;
        ueum_safe_alloc(background, char, 13);
        sprintf(background, ";%d", background_id);
    } else {
        background = ueum_string_create_from("");
    }

    ueum_safe_alloc(colored, char, colored_length);

    sprintf(colored, "%c[%s%s%sm%s%s", 0x1B, attribute, foreground, background, string, UNKNOWNECHOUTILSMODULE_COLOR_ESCAPE_RESET);
    colored[colored_length - 1] = '\0';

    ueum_safe_free(attribute);
    ueum_safe_free(foreground);
    ueum_safe_free(background);

    return colored;
}

