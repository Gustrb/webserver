#pragma once

#include <stdlib.h>

typedef struct array_list {
  void **data;
  size_t allocated_size;
  size_t last_element;
} array_list_t;

// Allocates a new array_list with size 10 by default
// the list itself must not be freed since its going to be allocated
// in the stack, but you should call array_list_free with a reference to it
// after its not going to be used anymore to cleanup the memory allocated with malloc
array_list_t array_list_new();

// It works the same way as the array_list_new function but you can set its initial
// size, its great to be used when its an operation in which its not going to be resized a lot
// since the list resizing has the complexity of O(n) with n being the list current size
array_list_t array_list_new_with_size(size_t size);

// Inserts a new element into the list at the given index, if the index is larger than the list
// it resizes itself to be able to hold the data
//
// This function has the complexity of O(n) since that every time it has to resize it has to copy
// all of its elements
void array_list_insert_at(array_list_t *list, size_t index, void *data_to_insert);

// A simple shortcut to array_list_insert_at that inserts after the last element of a list 
void array_list_push(array_list_t *list, void *data_to_insert);

// Performs a simple array lookup, returns NULL if the index was not filled but is in the array bounds
// But panics if it tries to access the list at a non-initialized index(or a negative?) 
void *array_list_get_element_at(array_list_t *list, size_t index);

// This function is used to free the memory allocated in the data field since its allocated in the heap
// it does not free the pointer itself so in order to free it it would require an aditional call to free()
//
// but since the default allocation for the array_list is through the stack it is usually not the case
void array_list_free(array_list_t *list);

