#include "dotenv.h"

#include <stdlib.h>

#include "../buffered_reader/buffered_reader.h"
#include "../utils/errors_helper.h"

#define PRIVATE static

PRIVATE void read_into_dotenv_if_no_content(dotenv_instance_t *dotenv) {
  err_n_die_if_true(!dotenv, "Invalid dotenv instance");
  buffer_t file_content = buffered_reader_from_filepath(dotenv->path);

  if (!dotenv->content) {
    dotenv->content = file_content.str;
  }
}

char *dotenv_fetch_prop(dotenv_instance_t *dotenv, char *prop_name) {
  err_n_die_if_true(!prop_name, "Invalid property name, it cannot be null");
  read_into_dotenv_if_no_content(dotenv);

  string_t content = string_from_char(dotenv->content);
  string_t prop_str = string_from_char(prop_name);
  array_list_t list = string_split(content, '\n');

  for (size_t line_index = 0; line_index < list.allocated_size; line_index++) {
    string_t *line = array_list_get_element_at(&list, line_index);
    array_list_t line_split = string_split(*line, '=');

    string_t *key = array_list_get_element_at(&line_split, 0);
    string_t *value = array_list_get_element_at(&line_split, 1);

    if (string_equals(prop_str, *key)) {
      return value->str;
    }
  }

  return NULL;
}
