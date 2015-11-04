#include "getline.h"

#include <stdio.h>

size_t my_getline(char *s, size_t lim)
{
  int c = 0;
  size_t i = 0;
  while (i < lim - 1 && c != '\n' && (c = getchar()) != EOF)
  {
    s[i++] = (char)c;
  }
  if (lim > 0)
  {
    s[i] = '\0';
  }
  return i;
}
