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

#include <ueum/thread/thread_mutex.h>
#include <ueum/alloc.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <ueum/errorHandling/error.h>
#endif

#include <errno.h>

/*
 * For Windows :
 * http://preshing.com/20111124/always-use-a-lightweight-mutex/
 */
ueum_thread_mutex *ueum_thread_mutex_create() {
    ueum_thread_mutex *m;
/*#if defined(_WIN32) || defined(_WIN64)
        char *error_buffer;
#endif*/

    ueum_safe_alloc(m, ueum_thread_mutex, 1);

#if defined(_WIN32) || defined(_WIN64)
        InitializeCriticalSection(&m->lock);
        /*if (!(m->lock = CreateMutex(NULL, FALSE, NULL))) {
            ueum_get_last_werror(error_buffer);
            ei_stacktrace_push_msg(error_buffer);
            ueum_safe_free(error_buffer);
            ueum_safe_free(m);
            return NULL;
        }*/
#else
        if (pthread_mutex_init(&m->lock, NULL) != 0) {
            ueum_safe_free(m);
            ei_stacktrace_push_errno();
            return NULL;
        }
#endif

    return m;
}

bool ueum_thread_mutex_destroy(ueum_thread_mutex *m) {
    bool state;
/*#if defined(_WIN32) || defined(_WIN64)
        char *error_buffer;
#endif*/

    if (!m) {
        return true;
    }

    state = true;

#if defined(_WIN32) || defined(_WIN64)
        DeleteCriticalSection(&m->lock);
        /*if (!CloseHandle(m->lock)) {
            ueum_get_last_werror(error_buffer);
            ei_stacktrace_push_msg(error_buffer);
            ueum_safe_free(error_buffer);
            state = false;
        }*/
#else
        if (pthread_mutex_destroy(&m->lock) != 0) {
            ei_stacktrace_push_errno();
            state = false;
        }
#endif

    ueum_safe_free(m);

    return state;
}

bool ueum_thread_mutex_lock(ueum_thread_mutex *m) {
/*#if defined(_WIN32) || defined(_WIN64)
        char *error_buffer;
#endif*/

    ei_check_parameter_or_return(m)

#if defined(_WIN32) || defined(_WIN64)
        TryEnterCriticalSection(&m->lock);
        /*if (WaitForSingleObject(m->lock, INFINITE) == WAIT_FAILED) {
            ueum_get_last_werror(error_buffer);
            ei_stacktrace_push_msg(error_buffer);
            ueum_safe_free(error_buffer);
            return false;
        }*/
#else
        if (pthread_mutex_lock(&m->lock) != 0) {
            ei_stacktrace_push_errno();
            return false;
        }
#endif

    return true;
}

bool ueum_thread_mutex_unlock(ueum_thread_mutex *m) {
/*#if defined(_WIN32) || defined(_WIN64)
        char *error_buffer;
#endif*/

    ei_check_parameter_or_return(m);

#if defined(_WIN32) || defined(_WIN64)
        LeaveCriticalSection(&m->lock);
        /*if (!ReleaseMutex(m->lock)) {
            ueum_get_last_werror(error_buffer);
            ei_stacktrace_push_msg(error_buffer);
            ueum_safe_free(error_buffer);
            return false;
        }*/
#else
        if (pthread_mutex_unlock(&m->lock) != 0) {
            ei_stacktrace_push_errno();
            return false;
        }
#endif

    return true;
}
