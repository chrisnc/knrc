#include <ctype.h>
#include <stdio.h>

#include "atoi.h"

// Exercise 5-6, page 107
// modified these functions to use pointer arithmetic

// atoi: convert s to integer
int my_atoi(const char *s)
{
  int n = 0;
  while (*s >= '0' && *s <= '9')
  {
    n *= 10;
    n += *s++ - '0';
  }
  return n;
}

// Exercise 2-3. page 46
int my_htoi(const char *s)
{
  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
  {
    s += 2;
  }
  int n = 0;
  while (isxdigit(*s))
  {
    int c = tolower(*s++);
    n *= 0x10;
    n += isalpha(c) ? c - 'a' + 10 : c - '0';
  }
  return n;
}

// Exercise 2-10. page 52
// lower: convert c to lower case; ASCII only, using ?:
int my_lower(int c)
{
  return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

// new atoi from page 54
int newatoi(const char *s)
{
  while (isspace(*s)) // skip whitespace
  {
    ++s;
  }
  int sign = (*s == '-') ? -1 : 1;
  if (*s == '+' || *s == '-') // skip sign
  {
    ++s;
  }
  int n = 0;
  while (isdigit(*s))
  {
    n *= 10;
    n += (*s++ - '0');
  }
  return sign * n;
}

int main(void)
{
  const char *s = "100";
  const char *sn = "-123";
  const char *sx = "0x1a";
  char c = 'F';
  printf("my_atoi(\"%s\") = %d\n", s, my_atoi(s));
  printf("newatoi(\"%s\") = %d\n", sn, newatoi(sn));
  printf("my_lower(\'%c\') = \'%c\'\n", c, my_lower(c));
  printf("my_htoi(\"%s\") = %d\n", sx, my_htoi(sx));
}
