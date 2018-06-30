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

/**
 *  @file      thread.h
 *  @brief     Portable way of thread functions manipulation.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef UNKNOWNECHOUTILSMODULE_THREAD_H
#define UNKNOWNECHOUTILSMODULE_THREAD_H

#include <ueum/thread/thread_id_struct.h>
#include <ueum/bool.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <ueum/thread/thread_result.h>
    #include <ei/ei.h>
#endif

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
#elif defined(__unix__)
    #include <pthread.h>
#endif

ueum_thread_id *ueum_thread_create(void *function, void *arg);

bool ueum_thread_join(ueum_thread_id *ti, void **result);

bool ueum_thread_detach(ueum_thread_id *ti);

#if defined(_WIN32) || defined(_WIN64)
    #define ueum_get_current_thread_id() GetCurrentThreadId()
#else
    #define ueum_get_current_thread_id() pthread_self()
#endif

#define ueum_thread_resolve_current_id(ti) ti->id = ueum_get_current_thread_id();

#if defined(_WIN32) || defined(_WIN64)
    #define ueum_thread_begin(type, name) { type *name; ueum_thread_id *current;
#else
    #define ueum_thread_begin(type, name) type *name; {
#endif

#define ueum_thread_end_windows(r) \
    ueum_thread_resolve_current_id(current); \
    if (!ueum_thread_results_is_initialized()) { \
        ueum_thread_results_init(); \
    } \
    ueum_thread_result_set(current, (void *)r); \
    return NULL; \

#if defined(_WIN32) || defined(_WIN64)
    #define ueum_thread_exit(r) ueum_thread_end_windows(r)
#else
    #define ueum_thread_end(r) pthread_exit(r); }
#endif

bool ueum_thread_cancel(ueum_thread_id *ti);

#endif
