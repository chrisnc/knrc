#include <stdio.h>

#include "getline.h"

// Exercise 3-2. part 2 page 60
static void unescape(char *s, const char *t)
{
  while (*t)
  {
    if (*t == '\\')
    {
      ++t;
      switch (*t)
      {
      case 'n':
        *s++ = '\n';
        break;
      case 't':
        *s++ = '\t';
        break;
      default:
        *s++ = *t;
        break;
      }
      ++t;
    }
    else
    {
      *s++ = *t++;
    }
  }
  *s = '\0';
}

#define MAXLINE 1000

int main(void)
{
  char line[MAXLINE];
  char unescaped[MAXLINE];
  size_t len;
  while ((len = my_getline(line, MAXLINE)) > 0)
  {
    unescape(unescaped, line);
    printf("%s", unescaped);
  }
}
