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

#include <ueum/thread/thread_cond.h>
#include <ueum/safe/safe_alloc.h>

#include <ei/ei.h>

#include <errno.h>

ueum_thread_cond *ueum_thread_cond_create() {
	ueum_thread_cond *cond;

	cond = NULL;

	ueum_safe_alloc(cond, ueum_thread_cond, 1);

#if defined(_WIN32) || defined(_WIN64)
    InitializeConditionVariable(&cond->data);
#else
    if (pthread_cond_init(&cond->data, NULL) != 0) {
        ei_stacktrace_push_errno();
        ueum_safe_free(cond);
        return NULL;
    }
#endif

    return cond;
}

void ueum_thread_cond_destroy(ueum_thread_cond *cond) {
	if (cond) {
#if defined(_WIN32) || defined(_WIN64)

#else
        pthread_cond_destroy(&cond->data);
#endif
        ueum_safe_free(cond);
	}
}

bool ueum_thread_cond_wait(ueum_thread_cond *cond, ueum_thread_mutex *mutex) {
	ei_check_parameter_or_return(cond);
	ei_check_parameter_or_return(mutex);

#if defined(_WIN32) || defined(_WIN64)
    //SleepConditionVariableCS(&cond->data, &mutex->lock, INFINITE);
#else
    if (pthread_cond_wait(&cond->data, &mutex->lock) != 0) {
        if (errno != ETIMEDOUT) {
            ei_stacktrace_push_errno();
            return false;
        }
    }
#endif

	return true;
}

bool ueum_thread_cond_signal(ueum_thread_cond *cond) {
	ei_check_parameter_or_return(cond);

#if defined(_WIN32) || defined(_WIN64)
    WakeConditionVariable(&cond->data);
#else
	if (pthread_cond_signal(&cond->data) != 0) {
        ei_stacktrace_push_errno();
        return false;
	}
#endif

	return true;
}

bool ueum_thread_cond_broadcast(ueum_thread_cond *cond) {
	ei_check_parameter_or_return(cond);

#if defined(_WIN32) || defined(_WIN64)
    WakeAllConditionVariable(&cond->data);
#else
    if (pthread_cond_broadcast(&cond->data) != 0) {
        ei_stacktrace_push_errno();
        return false;
	}
#endif

	return true;
}
