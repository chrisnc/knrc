#include <stdio.h>

#include "getline.h"
// simple pattern matching example, page 69

#define MAXLINE 1000 // maximum input line length

static char pattern[] = "ould"; // pattern to search for

// strindex: return index of t in s, -1 if none
static int strindex(char s[], char t[])
{
  int i, j, k;

  for (i = 0; s[i] != '\0'; ++i)
  {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k)
    {
    }
    if (k > 0 && t[k] == '\0')
    {
      return i;
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
