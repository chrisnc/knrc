#include "getline.h"

#include <stdio.h>

size_t my_getline(char *s, size_t lim)
{
  // Exercise 5-6. page 107
  // modified to use pointer arithmetic
  const char *begin = s;
  const char *end = s + lim;
  int c = '\0';
  while (s < end - 1 && c != '\n' && (c = getchar()) != EOF)
  {
    *s++ = (char)c;
  }
  if (lim > 0)
  {
    *s = '\0';
  }
  return (size_t)(s - begin);
}
