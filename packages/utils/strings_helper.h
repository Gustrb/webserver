#pragma once

#include "../data_structures/array_list/array_list.h"
#include "errors_helper.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
  char *str;
  size_t len;
} string_t;

// Creates a new string with the given content.
// The content is dynamically allocated and must be freed by the caller.
//
// this operation involves a copy of the given content, so it has the time
// complexity O(n) and it requires a memory allocation of O(n)
string_t string_from_char(char *str);

// Copies the given string into a new one, returning the new string.
// since it uses string_from_char it has the time complexity O(n) and it
// requires a memory allocation of O(n) and the new string also has to be freed
// by the caller
string_t string_copy(string_t string);

// Creates a list of strings from the given array of strings.
// separated by the given separator.
//
// this operation involves a copy of the given content, so it has the time
// complexity O(n) All the strings in the array must be freed by the caller And
// the list itself must be freed by the caller
array_list_t string_split(string_t str, char delim);

// Compares two strings.
bool string_equals(string_t str1, string_t str2);

// This function frees the value of the given string but it does not free the
// string itself since its allocation by the string_from_char is made in the
// stack
void string_free(string_t *string);
