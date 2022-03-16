#include "errors_helper.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void err_n_die(const char *format, ...) {
  va_list ap;

  va_start(ap, format);
  fprintf(stdout, "Error: ");
  vfprintf(stdout, format, ap);
  fprintf(stdout, "\n");
  va_end(ap);

  exit(EXIT_FAILURE);
}

void err_n_die_if_true(bool condition, const char *format, ...) {
  if (condition) {
    va_list ap;
    va_start(ap, format);

    err_n_die(format, ap);
    va_end(ap);
  }
}

