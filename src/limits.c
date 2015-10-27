#include <float.h>
#include <limits.h>
#include <stdio.h>

// Exercise 2-1. page 36

int main(void)
{
  printf("CHAR_MIN = %d, CHAR_MAX = %d\n", CHAR_MIN, CHAR_MAX);
  printf("SHRT_MIN = %d, SHRT_MAX = %d\n", SHRT_MIN, SHRT_MAX);
  printf("INT_MIN = %d, INT_MAX = %d\n", INT_MIN, INT_MAX);
  printf("LONG_MIN = %ld, LONG_MAX = %ld\n", LONG_MIN, LONG_MAX);

  printf("UCHAR_MAX = %d\n", UCHAR_MAX);
  printf("USHRT_MAX = %u\n", USHRT_MAX);
  printf("UINT_MAX = %u\n", UINT_MAX);
  printf("ULONG_MAX = %lu\n", ULONG_MAX);

  printf("minimum float = %f, maximum float = %f\n", -FLT_MAX, FLT_MAX);
  printf("minimum double = %f, maximum double = %f\n", -DBL_MAX, DBL_MAX);
}
