#ifndef util_h
#define util_h

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

int rand_int(int min, int max);

char** string_split(const char* str, const char* delim, int* len);
char* toLowerCase(const char* str);

#endif