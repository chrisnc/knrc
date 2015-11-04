#include <stdio.h>
#include <ctype.h>

#include "atoi.h"

// atoi: convert s to integer
int my_atoi(const char s[])
{
  int n = 0;
  for (int i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
  {
    n = 10 * n + (s[i] - '0');
  }
  return n;
}

// Exercise 2-3. page 46
int my_htoi(const char s[])
{
  int n = 0;
  int i;
  if (s[0] == '0' && (s[1] == 'x' || s[1] == 'X'))
  {
    i = 2;
  }
  else
  {
    i = 0;
  }
  for (; isxdigit(s[i]); ++i)
  {
    int c = tolower(s[i]);
    int next_digit = isalpha(c) ? c - 'a' + 10 : c - '0';
    n = 0x10 * n + next_digit;
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
int newatoi(char s[])
{
  int i;
  for (i = 0; isspace(s[i]); ++i) // skip whitespace
  {
  }
  int sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-') // skip sign
  {
    ++i;
  }
  int n;
  for (n = 0; isdigit(s[i]); ++i)
  {
    n = 10 * n + (s[i] - '0');
  }
  return sign * n;
}

int main(void)
{
  const char *s = "100";
  const char *sx = "0x1a";
  char c = 'F';
  printf("my_atoi(\"%s\") = %d\n", s, my_atoi(s));
  printf("my_lower(\'%c\') = \'%c\'\n", c, my_lower(c));
  printf("my_htoi(\"%s\") = %d\n", sx, my_htoi(sx));
}
