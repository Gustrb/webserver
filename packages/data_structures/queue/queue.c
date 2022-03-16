#include "queue.h"

queue_t queue_new() {
  queue_t queue;

  queue.size = 0;
  queue.list = array_list_new();

  return queue;
}

queue_t queue_new_with_size(size_t initial_size) {
  queue_t queue;

  queue.size = 0;
  queue.list = array_list_new_with_size(initial_size);

  return queue;
}

void *queue_peek(queue_t *queue) {
  err_n_die_if_true(!queue, "Cannot peek in a null ptr");
  err_n_die_if_true(queue->size == 0, "Cannot peek in an empty queue");

  return array_list_get_element_at(&queue->list, 0);
}

void queue_enqueue(queue_t *queue, void *data_to_insert) {
  err_n_die_if_true(!queue, "Cannot enqueue in a null ptr");

  queue->size++;

  array_list_push(&queue->list, data_to_insert);
}

void *queue_dequeue(queue_t *queue) {
  err_n_die_if_true(!queue, "Cannot dequeue from a null ptr");
  err_n_die_if_true(queue->size == 0, "Cannot dequeue from an empty queue");

  queue->size--;

  return array_list_remove_at(&queue->list, 0);
}

void queue_free(queue_t *queue) {
  err_n_die_if_true(!queue, "Cannot free a null ptr");

  array_list_free(&queue->list);
}
