#pragma once

#include <stdlib.h>

typedef struct buffer {
  char *str;
  size_t size;
} buffer_t;

// Creates a buffer from the contents of a file descriptor
// it must be an opened file, a socket, etc
// It returns a buffer which must be freed since it was allocated with malloc
//
// It is unix based, it uses the read syscall from the unistd lib so it doesn't
// work in a non-unix env
buffer_t buffered_reader_from_fd(int fd);

// Creates a buffer from the contents of the file pointed by the filepath string
// it panics if the given path is not valid or if the operating system cannot
// open it
//
// It is unix based, because it uses the buffered_reader_from_fd function and
// the open (and close) unixi syscall
// the buffer content should be freed since it was allocated using malloc
buffer_t buffered_reader_from_filepath(const char *filepath);

// Frees the memory allocated by buffered_reader_from_fd
// but does not free the buffer_t struct itself, since it might have been
// stack allocated
void buffered_reader_free(buffer_t *buffer);
