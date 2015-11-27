#include <stdio.h>

#include "getline.h"

// Exercise 3-2. page 60
static void escape(char *s, const char *t)
{
  while (*t)
  {
    switch (*t)
    {
    case '\t':
      *s++ = '\\';
      *s++ = 't';
      break;
    case '\n':
      *s++ = '\\';
      *s++ = 'n';
      break;
    case '\\':
      *s++ = '\\';
      *s++ = '\\';
      break;
    default:
      *s++ = *t;
      break;
    }
    ++t;
  }
  *s = '\0';
}

#define MAXLINE 1000

int main(void)
{
  char line[MAXLINE];
  char escaped[MAXLINE * 2];
  size_t len;
  while ((len = my_getline(line, MAXLINE)) > 0)
  {
    escape(escaped, line);
    printf("%s", escaped);
  }
}
