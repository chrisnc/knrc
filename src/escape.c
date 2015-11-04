#include <stdio.h>

#include "getline.h"

// Exercise 3-2. page 60
static int escape(char *s, const char *t)
{
  int n = 0;
  while (*t)
  {
    switch (*t)
    {
    case '\t':
      *s++ = '\\';
      *s++ = 't';
      n += 2;
      break;
    case '\n':
      *s++ = '\\';
      *s++ = 'n';
      n += 2;
      break;
    case '\\':
      *s++ = '\\';
      *s++ = '\\';
      n += 2;
      break;
    default:
      *s++ = *t;
      break;
    }
    ++t;
  }
  *s = '\0';
  return n;
}

static int unescape(char *s, const char *t)
{
  int n = 0;
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
    ++n;
  }
  *s = '\0';
  return n;
}

#define MAXLINE 1000

int main(void)
{
  char line[MAXLINE];
  char escaped[MAXLINE * 2];
  char unescaped[MAXLINE];
  size_t len;
  while ((len = my_getline(line, MAXLINE)) > 0)
  {
    escape(escaped, line);
    unescape(unescaped, escaped);
    printf("line = %s", line);
    printf("escaped = %s\n", escaped);
    printf("unescaped = %s", unescaped);
  }
}
