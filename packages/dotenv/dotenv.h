#pragma once

#include "../utils/strings_helper.h"

typedef struct dotenv {
  char *content;
  const char *path;
} dotenv_instance_t;

// Initializes a dotenv if it is not already initialized.
// Returns NULL if there is no such prop_name;
// This is a WIP and it should be changed to use a hashmap as soon as it is
// implemented.
char *dotenv_fetch_prop(dotenv_instance_t *dotenv, char *prop_name);
