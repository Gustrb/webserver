#include "array_list.h"

#include <stdio.h>

// This function wraps the array_list_new_with_size by calling it with the
// DEFAULT_ARRAY_LIST_SIZE value as the size, by default the size is 10
//
// TODO: Evaluate wheter 10 is a good initial boundary
array_list_t array_list_new() {
  const size_t DEFAULT_ARRAY_LIST_SIZE = 10;
  return array_list_new_with_size(DEFAULT_ARRAY_LIST_SIZE);
}

array_list_t array_list_new_with_size(size_t size) {
  array_list_t list;
     
  list.allocated_size = size;
  list.data = calloc(sizeof(void *), size);
  list.last_element = 0;

  return list;
}

// Each call to resize has the complexity of O(n) so call it with caution
static inline void resize(array_list_t *list, size_t new_size) {
  list->data = realloc(list->data, new_size);
  list->allocated_size = new_size;
}

void array_list_insert_at(array_list_t *list, size_t index, void *data_to_insert) {
  if (index >= list->allocated_size) {
    resize(list, index);
  }
  
  // If the last element is not the last anymore it must be updated
  if (index > list->last_element) {
    list->last_element = index;
  }
  
  list->data[index] = data_to_insert;
}

void array_list_push(array_list_t *list, void *data_to_insert) {
  array_list_insert_at(list, list->last_element + 1, data_to_insert);
}

void *array_list_get_element_at(array_list_t *list, size_t index) {
  // If out of the list's bounds it should panic and exit with EXIT_FAILURE code
  //
  // TODO: maybe free list(?) since it is not going to be freed and might be a rather large
  // file structure
  if (index < 0 || index > list->allocated_size) {
    fprintf(stderr, "Error: Index out of bounds");
    exit(EXIT_FAILURE);
  }

  return list->data[index];
}

void array_list_free(array_list_t *list) {
  free(list->data);
  list->allocated_size = 0;
}

