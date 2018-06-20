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
 *  @file      timer_measure_struct.h
 *  @brief     Structure that represent a time measure.
 *  @author    Charly Lamothe
 *  @copyright GNU Public License.
 */

#ifndef UNKNOWNECHOUTILSMODULE_TIMER_MEASURE_STRUCT_H
#define UNKNOWNECHOUTILSMODULE_TIMER_MEASURE_STRUCT_H

typedef struct {
	unsigned int id;
	int *times_begin;
	int *times_end;
	int times_begin_number;
	int times_end_number;
	char *unity;
} ueum_timer_measure;

#endif
