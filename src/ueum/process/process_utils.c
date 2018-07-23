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

#if defined(_WIN32)

#include <Windows.h>

#endif

/**
 * @todo add unix version
 * @todo check if there is an error in Windows XP as it doesn't return ERROR_INSUFFICIENT_BUFFER
 */
char *ueum_get_current_process_name() {
#if defined(_WIN32)
    char *szFileName, *error_buffer;

    ueum_safe_alloc(szFileName, char, MAX_PATH + 1);

    if (GetModuleFileNameA(NULL, szFileName, MAX_PATH + 1) == ERROR_INSUFFICIENT_BUFFER) {
        ei_get_last_werror(error_buffer);
        ei_stacktrace_push_msg("GetModuleFileNameA failed error message: %s", error_buffer);
        ueum_safe_free(szFileName);
        return NULL;
    }

    return szFileName;
#endif

    ei_stacktrace_push_msg("Unsupported OS");
    return NULL;
}
