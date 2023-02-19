#ifndef STRINGS_H
#define STRINGS_H

#include <utils.h>
#include <libPS4/file.h>


char *replace_str(char *str, char *orig, char *rep);
char *read_string(int f);
int split_string(char *str, char c, char ***arr);
int substring(char *haystack, char *needle);
#endif
