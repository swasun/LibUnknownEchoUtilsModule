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

int main() {
    char *colored;

    ei_init();

    colored = ueum_colorize_string("colored mother fucker.", UNKNOWNECHOUTILSMODULE_COLOR_ID_ATTRIBUTE_BOLD,
        UNKNOWNECHOUTILSMODULE_COLOR_ID_FOREGROUND_RED, UNKNOWNECHOUTILSMODULE_COLOR_ID_BACKGROUND_CYNAN);
    printf("%s\n", colored);
    ueum_safe_free(colored);

    ei_uninit();

    return 0;
}
