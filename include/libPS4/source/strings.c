#include <libPS4/strings.h>

char *replace_str(char *str, char *orig, char *rep) {
  char *ret;
  int i, count = 0;
  size_t newlen = f_strlen(rep);
  size_t oldlen = f_strlen(orig);
  for (i = 0; str[i] != '\0'; i++) {
    if (f_strstr(&str[i], orig) == &str[i]) {
      count++;
      i += oldlen - 1;
    }
  }
  ret = f_malloc(i + count * (newlen - oldlen));
  if (ret == NULL) {
    return str;
  }
  i = 0;
  while (*str) {
    if (f_strstr(str, orig) == str) {
      f_strcpy(&ret[i], rep);
      i += newlen;
      str += oldlen;
    } else {
      ret[i++] = *str++;
    }
  }
  ret[i] = '\0';
  return ret;
}
int split_string(char *str, char c, char ***arr) {
  int count = 1;
  int token_len = 1;
  int i = 0;
  char *p;
  char *t;
  p = str;
  while (*p != '\0') {
    if (*p == c) {
      count++;
    }
    p++;
  }
  *arr = (char **)f_malloc(sizeof(char *) * count);
  if (*arr == NULL) {
    return 0;
  }
  p = str;
  while (*p != '\0') {
    if (*p == c) {
      (*arr)[i] = (char *)f_malloc(sizeof(char) * token_len);
      if ((*arr)[i] == NULL) {
        return 0;
      }
      token_len = 0;
      i++;
    }
    p++;
    token_len++;
  }
  (*arr)[i] = (char *)f_malloc(sizeof(char) * token_len);
  if ((*arr)[i] == NULL) {
    return 0;
  }
  i = 0;
  p = str;
  t = ((*arr)[i]);
  while (*p != '\0') {
    if (*p != c && *p != '\0') {
      *t = *p;
      t++;
    } else {
      *t = '\0';
      i++;
      t = ((*arr)[i]);
    }
    p++;
  }
  return count;
}
char *read_string(int f) {
  char *string = f_malloc(sizeof(char) * 65536);
  int c;
  int length = 0;
  if (!string) {
    return string;
  }
  while ((c = fgetc_pointer(f)) != -1) {
    string[length++] = c;
  }
  string[length++] = '\0';

  return f_realloc(string, sizeof(char) * length);
}
int substring(char *haystack, char *needle) {
  if (f_strlen(haystack) >= f_strlen(needle)) {
    for (int i = f_strlen(haystack) - f_strlen(needle); i >= 0; i--) {
      int found = 1;
      for (size_t d = 0; d < f_strlen(needle); d++) {
        if (haystack[i + d] != needle[d]) {
          found = 0;
          break;
        }
      }
      if (found == 1) {
        return i;
      }
    }
  }
  return -1;
}
