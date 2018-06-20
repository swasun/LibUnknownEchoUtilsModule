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
 *  @file      timer_measure.h
 *  @brief     Module to manipulate timer_measure in order to measure time elapsed.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef UNKNOWNECHOUTILSMODULE_TIMER_MEASURE_H
#define UNKNOWNECHOUTILSMODULE_TIMER_MEASURE_H

#include <ueum/time/timer_measure_struct.h>
#include <ueum/bool.h>

ueum_timer_measure *ueum_timer_measure_create(unsigned int id);

void ueum_timer_measure_destroy(ueum_timer_measure *measure);

char *ueum_timer_measure_get_unity(ueum_timer_measure *measure);

bool ueum_timer_measure_set_unity(ueum_timer_measure *measure, char *unity);

bool ueum_timer_measure_append_begin(ueum_timer_measure *measure, int time);

bool ueum_timer_measure_append_end(ueum_timer_measure *measure, int time);

bool ueum_timer_measure_average(ueum_timer_measure *measure, double *result);

#endif
