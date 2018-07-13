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

#include <ueum/ueum.h>
#include <ei/ei.h>

int main() {
    ueum_queue *queue;
    const char *data;
    void *element;
    
    queue = NULL;
    data = "Hello world !";

    ei_init();
    ei_logger_use_symbol_levels();

    ei_logger_info("Creating an empty queue");
    if ((queue = ueum_queue_create()) == NULL) {
        ei_stacktrace_push_msg("Failed to create new empty queue");
        goto clean_up;
    }

    ei_logger_info("Pushing a new element to the queue");
    if (!ueum_queue_push(queue, (void *)data)) {
        ei_stacktrace_push_msg("Failed to push data to the queue");
        goto clean_up;
    }

    ei_logger_info("Checking if the queue is empty");
    if (ueum_queue_empty(queue)) {
        ei_stacktrace_push_msg("The queue is empty but it shouldn't");
        goto clean_up;
    }

    ei_logger_info("The queue isn't empty and contains %d element", ueum_queue_size(queue));

    ei_logger_info("Get the front element of the queue");
    if ((element = ueum_queue_front(queue)) == NULL) {
        ei_stacktrace_push_msg("Failed to get the front element from the queue");
        goto clean_up;
    }

    ei_logger_info("The element of the queue contains: %s", (char *)element);

    if (!ueum_queue_pop(queue)) {
        ei_stacktrace_push_msg("Failed to pop the queue");
        goto clean_up;
    }

clean_up:
    ueum_queue_destroy(queue);
    if (ei_stacktrace_is_filled()) {
        ei_logger_stacktrace("An error occurred with the following stacktrace :");
    }
    ei_uninit();
    return 0;
}
