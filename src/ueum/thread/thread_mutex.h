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
 *  @file      thread_mutex.h
 *  @brief     Portable structure of thread mutex.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef UNKNOWNECHOUTILSMODULE_THREAD_MUTEX_H
#define UNKNOWNECHOUTILSMODULE_THREAD_MUTEX_H

#include <ueum/compiler/bool.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
#else
    #include <pthread.h>
#endif

typedef struct {
#if defined(_WIN32) || defined(_WIN64)
        //HANDLE lock;
        CRITICAL_SECTION lock;
#else
        pthread_mutex_t lock;
#endif
} ueum_thread_mutex;

ueum_thread_mutex *ueum_thread_mutex_create();

/**
 * @todo In UNIX impl, detect EBUSY and try to destroy the mutex with a timeout.
 */
bool ueum_thread_mutex_destroy(ueum_thread_mutex *m);

bool ueum_thread_mutex_lock(ueum_thread_mutex *m);

bool ueum_thread_mutex_unlock(ueum_thread_mutex *m);

#endif
