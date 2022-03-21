#pragma once

#include "../utils/strings_helper.h"

typedef struct dotenv {
  char *content;
  const char *path;
} dotenv_instance_t;

char *dotenv_fetch_prop(dotenv_instance_t *dotenv, char *prop_name);
