#include <limits.h>
#include <stdbool.h>
#include <stdio.h>

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

int main(void)
{
  char s[100] = {0};
  int x[10] = {123, -1000, INT_MIN, INT_MAX, 0, -10000, 3, -10, -1, 1};

  for (size_t i = 0; i < 10; ++i)
  {
    itoa_recur(x[i], s);
    printf("itoa_recur(%d, s) -> s = \"%s\"\n", x[i], s);
  }

  return 0;
}
