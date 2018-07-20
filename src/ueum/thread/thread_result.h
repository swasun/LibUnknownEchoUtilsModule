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

/**
 *  @file      thread_result.h
 *  @brief     Portable way of thread function result.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef UNKNOWNECHOUTILSMODULE_THREAD_RESULT_H
#define UNKNOWNECHOUTILSMODULE_THREAD_RESULT_H

#include <ueum/thread/thread_id_struct.h>
#include <ueum/compiler/bool.h>

typedef struct {
    ueum_thread_id *ti;
    void *result;
} ueum_thread_result;

#define THREAD_RESULTS_MAX 10

ueum_thread_result ueum_thread_results[THREAD_RESULTS_MAX];

void ueum_thread_results_init();

bool ueum_thread_results_is_initialized();

bool ueum_thread_result_exists(ueum_thread_id *ti);

void ueum_thread_result_add(ueum_thread_id *ti);

void ueum_thread_result_remove(ueum_thread_id *ti);

void ueum_thread_result_set(ueum_thread_id *ti, void *result);

void *ueum_thread_result_get(ueum_thread_id *ti);

#endif
