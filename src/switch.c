#include <stdio.h>

#include "getline.h"

int count_digits(void) // count digits, white space, others
{
  int ndigit[10] = {0};
  int nwhite = 0;
  int nother = 0;

  int c;
  while ((c = getchar()) != EOF)
  {
    switch (c)
    {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      ++ndigit[c - '0'];
      break;
    case ' ':
    case '\n':
    case '\t':
      ++nwhite;
      break;
    default:
      ++nother;
      break;
    }
  }
  printf("digits =");
  for (int i = 0; i < 10; ++i)
  {
    printf(" %d", ndigit[i]);
  }
  printf(", white space = %d, other = %d\n", nwhite, nother);
  return 0;
}

// Exercise 3-2. page 60
int escape(char *s, const char *t)
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

int unescape(char *s, const char *t)
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
