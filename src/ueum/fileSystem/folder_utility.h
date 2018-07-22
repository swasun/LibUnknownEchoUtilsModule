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
 *  @file      folder_utility.h
 *  @brief     Utility functions relative to folder manipulations.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef UNKNOWNECHOUTILSMODULE_FOLDER_UTILITY_H
#define UNKNOWNECHOUTILSMODULE_FOLDER_UTILITY_H

#include <ueum/compiler/bool.h>

bool ueum_is_dir_exists(const char *dir_name);

int ueum_count_dir_files(const char *dir_name, bool recursively);

char **ueum_list_directory(const char *dir_name, int *files, bool recursively);

char *ueum_get_current_dir();

bool ueum_create_folder(const char *path_name);

#endif
