#include "buffered_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

#include "../utils/errors_helper.h"

buffer_t buffered_reader_from_fd(int fd) {
  err_n_die_if_true(fd < 0, "Error: Invalid file descriptor: %d", fd);

  buffer_t buffer;

  size_t size = 0;

  // Fetches the size of the content to be read and inserts it into the
  // size variable
  ioctl(fd, FIONREAD, &size);

  err_n_die_if_true(size <= 0, "Invalid file size");

  // Allocating size + 1 to be able to store the null character
  //
  // TODO: Investigate creating an allocator for relativelly small pointers
  // to be deallocated atexit()
  // so this wont need to be freed manually through free()
  buffer.str = malloc(size + 1);

  read(fd, buffer.str, size);
  buffer.size = size;

  // Adding the null character to the end of the string
  buffer.str[size] = '\0';

  return buffer;
}

void buffered_reader_free(buffer_t *buffer) {
  err_n_die_if_true(!buffer, "Buffer cannot be null");

  free(buffer->str);
}

