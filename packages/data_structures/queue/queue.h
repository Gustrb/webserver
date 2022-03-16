#pragma once

#include <stdlib.h>

#include "../array_list/array_list.h"
#include "../../utils/errors_helper.h"

// This whole data structure is a wrapper around the array_list_t, as a queue
// it only has the enqueue and dequeue functions, the rest is implemented in
// the array_list_t
typedef struct queue {
  size_t size;
  array_list_t list;
} queue_t;

// This function wraps the array_list_new function, it has the same default size
// as it, which is 10(maybe could be changed(?))
queue_t queue_new();

// This function wraps the array_list_new_with_size function, it has the same use
// case, it should be used when there is a max size for the queue so it wont resize
// itself as much
queue_t queue_new_with_size(size_t initial_size);

// Returns the first element of the queue, if the queue is empty it dies
void *queue_peek(queue_t *queue);

// Adds an element to the queue, if the queue is full it resizes itself, so it
// has an O(n) complexity
void queue_enqueue(queue_t *queue, void *data_to_insert);

// Removes the first element of the queue, if the queue is empty it dies
// but it also copies the whole queue after the removed element so it has an O(n) complexity as well
void *queue_dequeue(queue_t *queue);

// Deallocates the list field, but does not deallocate the queue itself, since it is, by default,
// allocated in the stack
void queue_free(queue_t *queue);
