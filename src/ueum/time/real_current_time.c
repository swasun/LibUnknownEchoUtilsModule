/*******************************************************************************
 * Copyright (C) 2018 Charly Lamothe                                           *
 *                                                                             *
 * This file is part of LibUnknownEchoUtilsModule.                             *
 *                                                                             *
 *   Licensed under the Apache License, Version 2.0 (the "License");           *
 *   you may not use this file except in compliance with the License.          *
 *   You may obtain a copy of the License at                                   *
 *                                                                             *
 *   http://www.apache.org/licenses/LICENSE-2.0                                *
 *                                                                             *
 *   Unless required by applicable law or agreed to in writing, software       *
 *   distributed under the License is distributed on an "AS IS" BASIS,         *
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.  *
 *   See the License for the specific language governing permissions and       *
 *   limitations under the License.                                            *
 *******************************************************************************/

#include <ueum/time/real_current_time.h>
#include <ueum/time/current_time.h>
#include <ei/ei.h>

#include <time.h>

#if defined(__unix__)

#include <sys/time.h>

#elif defined(_WIN32) || defined(_WIN64)

#undef UNICODE
#define UNICODE
#undef _WINSOCKAPI_
#define _WINSOCKAPI_
#include <Windows.h>
#include <winsock2.h>

#endif

#if defined(_WIN32) || defined(_WIN64)

#define BILLION (1E9)
static BOOL g_first_time = 1;
static LARGE_INTEGER g_counts_per_sec;

int clock_gettime_windows(struct timespec *ct)
{
    LARGE_INTEGER count;

    if (g_first_time)
    {
        g_first_time = 0;

        if (0 == QueryPerformanceFrequency(&g_counts_per_sec))
        {
            g_counts_per_sec.QuadPart = 0;
        }
    }

    if ((NULL == ct) || (g_counts_per_sec.QuadPart <= 0) ||
            (0 == QueryPerformanceCounter(&count)))
    {
        return -1;
    }

    ct->tv_sec = count.QuadPart / g_counts_per_sec.QuadPart;
    ct->tv_nsec = (long)(((count.QuadPart % g_counts_per_sec.QuadPart) * BILLION) / g_counts_per_sec.QuadPart);

    return 0;
}

#endif

/**
 * Source : https://stackoverflow.com/a/37920181
 */
unsigned long long ueum_get_real_current_time() {
    //struct timespec ts = {0, 0};
    struct timeval tv;

    ei_logger_debug("Before");

/*#if defined(__unix__)
    if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0) {
#elif defined(_WIN32) || defined(_WIN64)
    if (clock_gettime_windows(&ts) == 0) {
#endif
        printf("%ld\n", ts.tv_nsec);
        return (unsigned long long) (ts.tv_sec * 1000000 + ts.tv_nsec / 1000);
    } else */if (ueum_time_of_day(&tv)) {
        return (unsigned long long) (tv.tv_sec * 1000000 + tv.tv_usec);
    }

    ei_logger_debug("After");

    ei_stacktrace_push_msg("Failed to get real current time or alternative");
    return 0;
}
