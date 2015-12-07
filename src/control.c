#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>

#include "control.h"

// binsearch: find x in v[0] <= v[1] <= ... <= v[n-1]
int binsearch(int x, int v[], int n)
{
  int low = 0;
  int high = n - 1;
  int mid;
  while (low <= high)
  {
    mid = (low + high) / 2;
    if (x < v[mid])
    {
      high = mid - 1;
    }
    else if (x > v[mid])
    {
      low = mid + 1;
    }
    else
    {
      return mid;
    }
  }
  return -1;
}

// Exercise 3-1. page 58
int binsearch_2(int x, int v[], int n)
{
  int low = 0;
  int high = n;
  int mid = (low + high) / 2;
  while (mid != low)
  {
    if (x < v[mid])
    {
      high = mid;
    }
    else
    {
      low = mid;
    }
    mid = (low + high) / 2;
  }
  return (x == v[mid]) ? mid : -1;
}

// Exercise 5-6, page 107
// modified these functions to use pointer arithmetic

// reverse: reverse string s in place
void reverse(char *s)
{
  size_t n = strlen(s);
  char *t = s + n;
  while (s < t)
  {
    char c = *s;
    *s++ = *--t;
    *t = c;
  }
}

// itoa from page 64
void my_itoa(int n, char *s)
{
  char *start = s;
  int sign;
  if ((sign = n) < 0) // record sign
  {
    n = -n;
  }
  do
  {
    *s++ = n % 10 + '0';
  } while ((n /= 10) > 0);
  if (sign < 0)
  {
    *s++ = '-';
  }
  *s = '\0';
  reverse(start);
}

/*
 * Exercise 3-4. page 64
 *
 * On a two's complement system, computing -n of the largest negative number,
 * -(2^{wordsize - 1}), will overflow, rather than produce 2^{wordsize - 1},
 * which is not representable.
 */
void fixed_itoa(int n, char *s)
{
  char *start = s;
  bool is_negative = n < 0;
  do
  {
    *s++ = (char)('0' + abs(n % 10));
  } while ((n /= 10));

  if (is_negative)
  {
    *s++ = '-';
  }
  *s = '\0';
  reverse(start);
}

// Exercise 3-5. page 64
void itob(int n, char *s, int b)
{
  char *start = s;
  bool is_negative = n < 0;
  do
  {
    int digit = abs(n % b);
    *s++ = (char)((digit < 10) ? digit + '0' : (digit - 10) + 'a');
  } while ((n /= b));
  if (is_negative)
  {
    *s++ = '-';
  }
  *s = '\0';
  reverse(start);
}

// Exercise 3-6. page 64
void itoa_padded(int n, char *s, int min_width)
{
  char *start = s;
  const char *end = s + min_width;
  bool is_negative = n < 0;
  do
  {
    *s++ = (char)('0' + abs(n % 10));
  } while ((n /= 10));

  if (is_negative)
  {
    *s++ = '-';
  }
  while (s < end)
  {
    *s++ = ' ';
  }
  *s = '\0';
  reverse(start);
}

int main(void)
{
  static const int n = 10;
  int *v = malloc(n * sizeof(*v));
  for (int i = 0; i < n; ++i)
  {
    v[i] = i;
  }

  for (int x = -3; x <= n + 3; ++x)
  {
    printf("binsearch(%d, v, %d) = %d\n", x, n, binsearch(x, v, n));
  }
  free(v);

  char odd[] = "This is an odd length string.";
  printf("strlen(\"%s\") = %zu\n", odd, strlen(odd));
  printf("%s\n", odd);
  reverse(odd);
  printf("%s\n", odd);

  char even[] = "This is an even length string.";
  printf("strlen(\"%s\") = %zu\n", even, strlen(even));
  printf("%s\n", even);
  reverse(even);
  printf("%s\n", even);

  char empty[] = "";
  printf("strlen(\"%s\") = %zu\n", empty, strlen(empty));
  printf("%s\n", empty);
  reverse(empty);
  printf("%s\n", empty);

  char str[100];
  my_itoa(-9000, str);
  printf("my_itoa(%d) = \"%s\"\n", -9000, str);
  // This line triggers undefined behavior, as the original my_itoa is broken
  // for INT_MIN. fixed_itoa does the right thing, however.
  //my_itoa(INT_MIN, str);
  //printf("my_itoa(%d) = \"%s\"\n", INT_MIN, str);
  fixed_itoa(INT_MIN, str);
  printf("fixed_itoa(%d) = \"%s\"\n", INT_MIN, str);

  int x = INT_MIN;
  itob(x, str, 16);
  printf("itob(%d) = \"%s\"\n", x, str);

  int z = -10;
  char itoaresult[100] = {0};
  itoa_padded(z, itoaresult, 10);
  printf("itoa_padded(%d, s, 10); s = %s\n", z, itoaresult);
  printf("len(s) = %zu\n", strlen(itoaresult));

  return 0;
}
