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

#ifndef UNKNOWNECHOUTILSMODULE_TIME_CURRENT_H
#define UNKNOWNECHOUTILSMODULE_TIME_CURRENT_H

#include <ueum/compiler/bool.h>

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

bool ueum_time_of_day(struct timeval *p);

#endif
