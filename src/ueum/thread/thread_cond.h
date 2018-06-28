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
 *  @file      thread_cond.h
 *  @brief     Portable structure of thread condition variable.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef UNKNOWNECHOUTILSMODULE_THREAD_COND_H
#define UNKNOWNECHOUTILSMODULE_THREAD_COND_H

#include <ueum/bool.h>
#include <ueum/thread/thread_mutex.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <Windows.h>
#elif defined(__unix__)
    #include <pthread.h>
#endif

typedef struct {
#if defined(_WIN32) || defined(_WIN64)
        CONDITION_VARIABLE data;
#elif defined(__unix__)
	    pthread_cond_t data;
#endif
} ueum_thread_cond;

ueum_thread_cond *ueum_thread_cond_create();

void ueum_thread_cond_destroy(ueum_thread_cond *cond);

bool ueum_thread_cond_wait(ueum_thread_cond *cond, ueum_thread_mutex *mutex);

bool ueum_thread_cond_signal(ueum_thread_cond *cond);

bool ueum_thread_cond_broadcast(ueum_thread_cond *cond);

#endif
