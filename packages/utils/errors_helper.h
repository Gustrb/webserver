#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void err_n_die(const char *format, ...);
void err_n_die_if_true(bool condition, const char *format, ...);

