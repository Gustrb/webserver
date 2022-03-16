#include "array_list.h"
#include "../../utils/errors_helper.h"

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

  err_n_die_if_true(!list.data, "Could not allocate array_list");

  return list;
}

// Each call to resize has the complexity of O(n) so call it with caution
static inline void resize(array_list_t *list, size_t new_size) {
  list->data = realloc(list->data, new_size);

  err_n_die_if_true(!list->data, "Could not resize list");

  list->allocated_size = new_size;
}

void array_list_insert_at(array_list_t *list, size_t index, void *data_to_insert) {
  err_n_die_if_true(!list, "List cannot be null");

  if (index >= list->allocated_size) {
    resize(list, index);
  }

  list->data[index] = data_to_insert;
}

void array_list_push(array_list_t *list, void *data_to_insert) {
  err_n_die_if_true(!list, "List cannot be null");

  for (size_t i = 0; i < list->allocated_size; i++) {
    if (list->data[i] == NULL) {
      array_list_insert_at(list, i, data_to_insert);
      return;
    }
  }
}

void *array_list_get_element_at(array_list_t *list, size_t index) {
  err_n_die_if_true(!list, "List cannot be null");

  // TODO: maybe free list(?) since it is not going to be freed and might be a rather large
  // data structure
  err_n_die_if_true(index > list->allocated_size, "Index out of bounds");

  return list->data[index];
}

void *array_list_remove_at(array_list_t *list, size_t index) {
  err_n_die_if_true(!list, "List cannot be null");

  void *data = array_list_get_element_at(list, index);

  for (size_t i = index; i < list->allocated_size; i++) {
    list->data[i] = list->data[i + 1];
  }

  return data;
}

void array_list_free(array_list_t *list) {
  err_n_die_if_true(!list, "List cannot be null");

  free(list->data);
  list->allocated_size = 0;
}
