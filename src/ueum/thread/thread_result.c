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

#include <ueum/thread/thread_result.h>
#include <string.h>

bool ueum_thread_results_initialized = false;

void ueum_thread_results_init() {
    unsigned short int i;

    memset(&ueum_thread_results, 0, THREAD_RESULTS_MAX * sizeof(ueum_thread_result));

    for (i = 0; i < THREAD_RESULTS_MAX; i++) {
        memset(&ueum_thread_results[i].ti, 0, sizeof(ueum_thread_id));
        memset(&ueum_thread_results[i].result, 0, sizeof(void *));
    }

    ueum_thread_results_initialized = true;
}

bool ueum_thread_results_is_initialized() {
    return ueum_thread_results_initialized;
}

bool ueum_thread_result_exists(ueum_thread_id *ti) {
    if (!ueum_thread_results_initialized) {
        return false;
    }

    unsigned short int i;

    for (i = 0; i < THREAD_RESULTS_MAX; i++) {
        if (ueum_thread_results[i].ti == ti) {
            return true;
        }
    }

    return false;
}

void ueum_thread_result_add(ueum_thread_id *ti) {
    unsigned short int i;

    if (!ueum_thread_results_initialized || ueum_thread_result_exists(ti)) {
        return;
    }

    for (i = 0; i < THREAD_RESULTS_MAX; i++) {
        if (!ueum_thread_results[i].ti) {
            ueum_thread_results[i].ti = ti;
            break;
        }
    }
}

void ueum_thread_result_remove(ueum_thread_id *ti) {
    unsigned short int i;

    if (!ueum_thread_results_initialized) {
        return;
    }

    for (i = 0; i < THREAD_RESULTS_MAX; i++) {
        if (ueum_thread_results[i].ti == ti) {
            ueum_thread_results[i].ti = NULL;
            ueum_thread_results[i].result = NULL;
            break;
        }
    }
}

void ueum_thread_result_set(ueum_thread_id *ti, void *result) {
    unsigned short int i;

    if (!ueum_thread_results_initialized) {
        return;
    }

    for (i = 0; i < THREAD_RESULTS_MAX; i++) {
        if (ueum_thread_results[i].ti == ti) {
            ueum_thread_results[i].result = result;
            break;
        }
    }
}

void *ueum_thread_result_get(ueum_thread_id *ti) {
    unsigned short int i;
    void *result;

    if (!ueum_thread_results_initialized) {
        return NULL;
    }

    result = NULL;

    for (i = 0; i < THREAD_RESULTS_MAX; i++) {
        if (ueum_thread_results[i].ti == ti) {
            result = ueum_thread_results[i].result;
            ueum_thread_results[i].ti = NULL;
            ueum_thread_results[i].result = NULL;
            break;
        }
    }

    return result;
}
