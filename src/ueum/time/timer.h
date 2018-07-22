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
 *  @file      timer.h
 *  @brief     Portable and accurate way to measure the elapsed time
 *             between two parts in the code.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef UNKNOWNECHOUTILSMODULE_TIMER_H
#define UNKNOWNECHOUTILSMODULE_TIMER_H

#include <ueum/time/timer_struct.h>
#include <ueum/time/timer_measure_struct.h>
#include <ueum/time/timer_measure.h>
#include <ueum/time/real_current_time.h>
#include <ueum/compiler/bool.h>

#include <time.h>

ueum_timer *ueum_timer_create_empty();

void ueum_timer_destroy(ueum_timer *tm);

bool ueum_timer_start_impl(ueum_timer *tm, unsigned int id, int timestamp);

bool ueum_timer_stop_impl(ueum_timer *tm, unsigned int id, int timestamp);

void ueum_timer_average_impl(ueum_timer *tm, unsigned int id, double *result);

bool ueum_timer_average_print_impl(ueum_timer *tm, unsigned int id, char *prefix_message);

void ueum_timer_total_impl(ueum_timer *tm, unsigned int id, double *result);

bool ueum_timer_total_print_impl(ueum_timer *tm, unsigned int id, char *prefix_message);

bool ueum_timer_set_unity_impl(ueum_timer *tm, unsigned int id, char *unity);

/**
 * Replace thread storage by libuv uv_key API
 */

/*#define ueum_timer_set_unity(id, unity) \
    ueum_timer_set_unity_impl(ueum_thread_storage_get_timer(), id, unity); \

#define ueum_timer_start(id) \
    ueum_timer_start_impl(ueum_thread_storage_get_timer(), id, ueum_get_real_current_time()); \

#define ueum_timer_stop(id) \
    ueum_timer_stop_impl(ueum_thread_storage_get_timer(), id, ueum_get_real_current_time()); \

#define ueum_timer_average(id, result) \
    ueum_timer_average_impl(ueum_thread_storage_get_timer(), id, &result); \

#define ueum_timer_average_print(id, message) \
    ueum_timer_average_print_impl(ueum_thread_storage_get_timer(), id, message); \

#define ueum_timer_total(id, result) \
    ueum_timer_total_impl(ueum_thread_storage_get_timer(), id, &result); \

#define ueum_timer_total_print(id, message) \
    ueum_timer_total_print_impl(ueum_thread_storage_get_timer(), id, message); \*/

#endif
