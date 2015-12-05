#include "getline.h"

#include <stdio.h>

size_t my_getline(char *s, size_t lim)
{
  if (s == NULL || lim == 0)
  {
    return 0;
  }

  // Exercise 5-6. page 107
  // modified to use pointer arithmetic
  const char *begin = s;
  const char *end = s + lim;
  int c = '\0';
  while (s < end - 1 && c != '\n' && (c = getchar()) != EOF)
  {
    *s++ = (char)c;
  }
  *s = '\0';
  return (size_t)(s - begin);
}
