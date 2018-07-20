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

#ifndef UNKNOWNECHOUTILSMODULE_INPUT_H
#define UNKNOWNECHOUTILSMODULE_INPUT_H

#include <ueum/compiler/ssize_t.h>

typedef enum {
    UNKNOWNECHOUTILSMODULE_STDIN_INPUT,
    UNKNOWNECHOUTILSMODULE_PUSH_INPUT
} ueum_user_input_mode;

char *ueum_input_string(char *prefix);

char *ueum_input_password(const char *prompt_message, ssize_t max_size);

#endif
