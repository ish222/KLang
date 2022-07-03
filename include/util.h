#ifndef KLANG_UTIL_H
#define KLANG_UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

void* xmalloc(size_t size);  // malloc wrapper which checks if the pointer returned is null
char* read_ascii_from_file(const char* path);  // Reads ascii data from a file TODO
char* read_input();  // Reads input from console until newline

#endif //KLANG_UTIL_H
