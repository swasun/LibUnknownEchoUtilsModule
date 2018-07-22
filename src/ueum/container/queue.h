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
  * Inspired from : http://www.sanfoundry.com/c-program-queue-using-linked-list for structure
  *
  * Inspired from : https://github.com/tobithiel/Queue for thread-safety logic
  * Associated copyright :
  *
  * Copyright (C) 2011 by Tobias Thiel
  * Permission is hereby granted, free of charge, to any person obtaining a copy
  * of this software and associated documentation files (the "Software"), to deal
  * in the Software without restriction, including without limitation the rights
  * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  * copies of the Software, and to permit persons to whom the Software is
  * furnished to do so, subject to the following conditions:
  *
  * The above copyright notice and this permission notice shall be included in
  * all copies or substantial portions of the Software.
  *
  * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  * THE SOFTWARE.
  */

#ifndef UNKNOWNECHOUTILSMODULE_QUEUE_H
#define UNKNOWNECHOUTILSMODULE_QUEUE_H

#include <ueum/compiler/bool.h>
#include <ueum/thread/thread_mutex.h>
#include <ueum/thread/thread_cond.h>

#include <stdio.h>

struct ueum_queue_node {
    void *data;
    struct ueum_queue_node *ptr;
};

typedef struct {
    struct ueum_queue_node *front, *rear, *temp, *front1;
    int count;
    void (*user_print_func)(void *data, FILE *fd);
    void *(*user_alloc_func)(void *data);
    void (*user_free_func)(void *data);
    ueum_thread_mutex *mutex;
    ueum_thread_cond *write_cond, *read_cond;
} ueum_queue;

ueum_queue *ueum_queue_create();

ueum_queue *ueum_queue_create_mem(void *(*alloc_func)(void *data), void (*free_func)(void *data));

void ueum_queue_destroy(ueum_queue *queue);

void ueum_queue_clean_up(ueum_queue *queue);

bool ueum_queue_push(ueum_queue *queue, void *data);

/**
 * Set capacity for regulate the size
 */
bool ueum_queue_push_wait(ueum_queue *queue, void *data);

bool ueum_queue_pop(ueum_queue *queue);

int ueum_queue_size(ueum_queue *queue);

void *ueum_queue_front(ueum_queue *queue);

void *ueum_queue_front_wait(ueum_queue *queue);

bool ueum_queue_empty(ueum_queue *queue);

bool ueum_queue_print(ueum_queue *queue, FILE *fd);

bool ueum_queue_set_print_func(ueum_queue *queue, void (*print_func)(void *data, FILE *fd));

#endif
