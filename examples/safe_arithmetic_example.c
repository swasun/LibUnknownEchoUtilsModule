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

#include <stddef.h>
#include <limits.h>

bool test_add_sizet_overflow() {
    size_t one, two, out;

    one = 7799999999999999990U;
    two = 7799999999999999990U;
    out = 0;
    
    ei_logger_debug("one=%ld", one);
    ei_logger_debug("two=%ld", two);

    if (ueum__add_sizet_overflow(one, two, &out)) {
        ei_logger_info("Buffer overflow detected: %ld + %ld cannot be performed.", one, two);
        return true;
    }

    ei_stacktrace_push_msg("Failed to detect buffer overflow when performing: %ld + %ld."
        " The result appears to be: %ld", one, two, out);
    return false;
}

int main() {
	ei_init_or_die();
    ei_logger_use_symbol_levels();

    if (!test_add_sizet_overflow()) {
        ei_stacktrace_push_msg("Test of ueum__add_sizet_overflow() failed");
        goto clean_up;
    }
    
    ei_logger_info("Succeed !");    

clean_up:
    if (ei_stacktrace_is_filled()) {
        ei_logger_error("Error(s) occurred with the following stacktrace(s):");
        ei_stacktrace_print_all();
    }
    ei_uninit();
    return 0;
}
