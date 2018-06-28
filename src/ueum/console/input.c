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

#include <ueum/console/input.h>
#include <ueum/string/string_utility.h>
#include <ueum/alloc.h>
#include <ueum/ssize_t.h>

#include <ei/ei.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>  /* for errno */

#if defined(__unix__)
	#include <unistd.h> /* for EINTR */
#endif

char *ueum_input_string(char *prefix) {
	char input[256], *result;
	int i;

	result = NULL;

	printf("%s", prefix);

  	if (fgets(input, 256, stdin)) {
  		if (input[0] == 10) {
  			return NULL;
  		}
  		for (i = 0; i < 256; i++) {
  			if (input[i] != ' ') {
  				result = ueum_string_create_from(input);
  				ueum_remove_last_char(result);
  				break;
  			}
  		}
  	}

  	return result;
}

#if defined(__unix__)

#include <termios.h>
#include <sys/time.h>

/**
 * Get the password enter in input stream without print it in the terminal.
 * It only works on Linux/Mac.
 *
 * Read a string from stream into password masking keypress with mask char.
 * getpasswd will read upto max_size - 1 chars into password, null-terminating
 * the resulting string. On success, the number of characters in
 * password are returned, -1 otherwise.
 *
 * @param password where to password will be stored. It have to be allocated by the caller.
 * @param max_size max size of the password, set by the caller.
 * @param stream   input stream, e.g. stdin.
 * @return the size of the input password.
 * @todo record error messages in place of print them.
 *
 * @source https://stackoverflow.com/a/32421674
 */
static ssize_t get_input_password_unix(char **password, size_t max_size, int mask, FILE *stream) {
    size_t idx; /* index, number of chars in read   */
    int c;
    struct termios old_kbd_mode; /* Orig keyboard settings   */
    struct termios new_kbd_mode;

    /**
     * Validate input
     * @todo check each parameter to detail error message
     */
    if (!password || !max_size || !stream) {
        ei_stacktrace_push_msg("At least one invalid parameter");
        return -1;
    }

    idx = 0;
    c = 0;

    /* Save orig settings */
    if (tcgetattr(0, &old_kbd_mode)) {
        ei_stacktrace_push_msg("tcgetattr failed");
        return -1;
    }

    /* Copy old to new */
    memcpy(&new_kbd_mode, &old_kbd_mode, sizeof(struct termios));

    new_kbd_mode.c_lflag &= ~(ICANON | ECHO); /* New kbd flags */
    new_kbd_mode.c_cc[VTIME] = 0;
    new_kbd_mode.c_cc[VMIN] = 1;
    if (tcsetattr(0, TCSANOW, &new_kbd_mode)) {
        ei_stacktrace_push_msg("tcsetattr failed with new flags");
        return -1;
    }

    /* Read chars from stream, mask if valid char specified */
    while (((c = fgetc(stream)) != '\n' && c != EOF && idx < max_size - 1) ||
            (idx == max_size - 1 && c == 127)) {
        if (c != 127) {
            /* Valid ascii char */
            if (31 < mask && mask < 127) {
                fputc(mask, stdout);
            }
            (*password)[idx++] = c;
        }
        else if (idx > 0) {
            /* Handle backspace (del) */
            if (31 < mask && mask < 127) {
                fputc(0x8, stdout);
                fputc(' ', stdout);
                fputc(0x8, stdout);
            }
            (*password)[--idx] = 0;
        }
    }
    /* Set null-terminate */
    (*password)[idx] = 0;

    /* Reset original keyboard */
    if (tcsetattr(0, TCSANOW, &old_kbd_mode)) {
        ei_stacktrace_push_msg("tcsetattr failed to set previous flags");
        return -1;
    }

    /* Warn if password truncated */
    if (idx == max_size - 1 && c != '\n') {
        ei_logger_warn("Truncated at %zu chars", max_size - 1);
    }

    return idx;
}

#endif

#if defined(_WIN32) || defined(_WIN64)

/**
 * @see http://www.cplusplus.com/articles/E6vU7k9E/
 */
static ssize_t get_input_password_windows(char **password, size_t max_size, FILE *stream) {
	(void)password;
	(void)max_size;
	(void)stream;
	ei_stacktrace_push_msg("Not implemented");
    return -1;
}

#endif

/**
 * Get the password enter in input stream without print it in the terminal.
 */
char *ueum_input_password(const char *prompt_message, size_t max_size) {
    char *password;
    size_t size;

    ueum_safe_alloc(password, char, max_size);
    size = 0;

#if defined(__unix__)
    printf("%s", prompt_message);
    size = get_input_password_unix(&password, max_size, '*', stdin);
    printf("\n");
#elif defined(_WIN32) || defined(_WIN64)
    printf("%s", prompt_message);
    size = get_input_password_windows(&password, max_size, stdin);
    printf("\n");
#else
    #error Unsupported operating system
#endif

    if (size == -1) {
        ueum_safe_free(password);
        return password;
    }

    if (size < max_size) {
        ueum_safe_realloc(password, char, size, max_size - size);
    }

    return password;
}