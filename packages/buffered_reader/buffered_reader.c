#include "buffered_reader.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <unistd.h>

buffer_t buffered_reader_from_fd(int fd) {
  // TODO: Create a function that tests wheter a condition is true and fails
  // with a provided error message and returns EXIT_FAILURE
  if (fd < 0) {
    fprintf(stderr, "Error: Invalid file descriptor: %d", fd);
    exit(EXIT_FAILURE);
  }

  buffer_t buffer;

  size_t size = 0;

  // Fetches the size of the content to be read and inserts it into the
  // size variable
  ioctl(fd, FIONREAD, &size);

  // TODO: Throw an error if size is less than 0, making the if (size > 0) test
  // not necessary

  // Allocating size + 1 to be able to store the null character
  //
  // TODO: Investigate creating an allocator for relativelly small pointers
  // to be deallocated atexit()
  // so this wont need to be freed manually through free()
  buffer.str = malloc(size + 1);

  // If size is less than 0 an error should be thrown
  if (size > 0) {
    read(fd, buffer.str, size);
    buffer.size = size;
  }

  // Adding the null character to the end of the string
  buffer.str[size] = '\0';

  return buffer;
}

void buffered_reader_free(buffer_t *buffer) {
  free(buffer->str);
}

