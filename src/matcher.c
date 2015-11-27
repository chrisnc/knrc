#include <stdio.h>

#include "getline.h"
// simple pattern matching example, page 69

#define MAXLINE 1000 // maximum input line length

static char pattern[] = "ould"; // pattern to search for

// Exercise 5-6. page 107
// modified strindex to use pointer arithmetic

// strindex: return index of t in s, -1 if none
static int strindex(const char *s, const char *t)
{
  const char *sstart = s;
  for (; *s; ++s)
  {
    const char *j, *k;
    for (j = s, k = t; *k && *j == *k; ++j, ++k)
    {
    }
    if (k > t && *k == '\0')
    {
      return (int)(s - sstart);
    }
  }
  return -1;
}

// find all lines matching pattern
int main(void)
{
  char line[MAXLINE];
  int found = 0;
  while (my_getline(line, MAXLINE) > 0)
  {
    if (strindex(line, pattern) >= 0)
    {
      printf("%s", line);
      ++found;
    }
  }
  return found;
}
