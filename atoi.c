#include <stdio.h>
#include <ctype.h>

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

// Exercise 2-10.
// lower: convert c to lower case; ASCII only, using ?:
int my_lower(int c)
{
  return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

// Exercise 2-3.
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

int main(void)
{
  const char *s = "100";
  const char *sx = "0x1a";
  char c = 'F';
  printf("my_atoi(\"%s\") = %d\n", s, my_atoi(s));
  printf("my_lower(\'%c\') = \'%c\'\n", c, my_lower(c));
  printf("my_htoi(\"%s\") = %d\n", sx, my_htoi(sx));
}
