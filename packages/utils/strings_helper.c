#include "strings_helper.h"
#include <string.h>

string_t string_from_char(char *str) {
  string_t string;

  size_t len = strlen(str);

  string.str = malloc(len + 1);
  strncpy(string.str, str, len);
  string.len = len;

  string.str[len] = '\0';

  return string;
}

string_t string_copy(string_t string) {
  string_t copy = string_from_char(string.str);
  return copy;
}

array_list_t string_split(string_t str, char delim) {
  array_list_t list = array_list_new();
  string_t copy = string_copy(str);
  char *token = strtok(copy.str, &delim);

  while (token != NULL) {
    string_t *element = malloc(sizeof(string_t));

    *element = string_from_char(token);
    array_list_push(&list, element);
    token = strtok(NULL, &delim);
  }

  return list;
}

bool string_equals(string_t str1, string_t str2) {
  return strncmp(str1.str, str2.str, str1.len) == 0;
}

void string_free(string_t *string) {
  err_n_die_if_true(!string, "Cannot de-allocate NULL string");

  free(string->str);
  string->len = 0;
}
