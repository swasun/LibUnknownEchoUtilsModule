/******************************************************************************************
 * Copyright (C) 2018 by Charly Lamothe                        	                          *
 *                                                                                        *
 * This file is part of LibUnknownEchoUtilsModule.                                        *
 *                                                                                        *
 *   LibUnknownEchoUtilsModule is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by                 *
 *   the Free Software Foundation, either version 3 of the License, or        	          *
 *   (at your option) any later version.                                                  *
 *                                                                                        *
 *   LibUnknownEchoUtilsModule is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of                       *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                        *
 *   GNU General Public License for more details.                                         *
 *                                                                                        *
 *   You should have received a copy of the GNU General Public License        	          *
 *   along with LibUnknownEchoUtilsModule.  If not, see <http://www.gnu.org/licenses/>.   *
 ******************************************************************************************/

#include <ueum/console/console.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#else
    #include <sys/ioctl.h>
#endif

#include <stdio.h>

int ueum_console_get_width() {
    int width;

#if defined(_WIN32) || defined(_WIN64)
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        width = csbi.srWindow.Right - csbi.srWindow.Left;
#else
        struct winsize win;
        ioctl(0, TIOCGWINSZ, &win);
        width = win.ws_col;
#endif

    return width;
}

void ueum_console_erase_previous_line() {
    printf("\033[A\033[2K");
}

void ueum_console_erase_previous_lines(int n) {
    int i;

    for (i = 0; i < n; i++) {
        ueum_console_erase_previous_line();
    }

    rewind(stdout);
}
