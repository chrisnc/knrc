#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

// Exercise 4-12. page 88
// NOTE: The return value is not the original value
// of s like itoa from the standard library. Instead it is a pointer to the
// null terminator this is used so the function can be implemented recursively
// without a helper function.
static char *itoa_recur(int n, char *s)
{
  if (n < 0)
  {
    *s++ = '-';
    if (-(n / 10))
    {
      s = itoa_recur(-(n / 10), s);
    }
    *s++ = (char)('0' - (n % 10));
  }
  else if (n > 0)
  {
    if (n / 10)
    {
      s = itoa_recur(n / 10, s);
    }
    *s++ = (char)('0' + (n % 10));
  }
  else
  {
    *s++ = '0';
  }
  *s = '\0';
  return s;
}

// Exercise 4-13. page 88
static void reverse_recur(char *s)
{
  size_t n = strlen(s);
  if (n < 2)
  {
    return;
  }
  char tmp = s[n - 1];
  s[n - 1] = '\0';
  reverse_recur(s + 1);
  s[n - 1] = s[0];
  s[0] = tmp;
}

int main(void)
{
  char s[100] = {0};
  const int x[10] = {123, -1000, INT_MIN, INT_MAX, 0, -10000, 3, -10, -1, 1};

  for (size_t i = 0; i < 10; ++i)
  {
    itoa_recur(x[i], s);
    printf("itoa_recur(%d, s) -> s = \"%s\"\n", x[i], s);
  }

  char a[] = "hello, there";
  char b[] = "this is a string";
  char c[] = "";
  char d[] = "0012";
  char *const ss[] = {a, b, c, d};

  for (size_t i = 0; i < 4; ++i)
  {
    printf("reverse_recur(\"%s\") ->", ss[i]);
    reverse_recur(ss[i]);
    printf(" \"%s\"\n", ss[i]);
  }

  return 0;
}
