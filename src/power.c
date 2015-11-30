#include <stdio.h>

// power function examples, page 24-26

int power_first(int base, int n);
int power(int base, int n);

// test power function
int main(void)
{
  for (int i = 0; i < 10; ++i)
  {
    printf("%d %d %d\n", i, power(2, i), power(-3, i));
  }
  return 0;
}

// power: raise base to n-th power; n >= 0
int power_first(int base, int n)
{
  int p = 1;
  for (int i = 1; i <= n; ++i)
  {
    p = p * base;
  }
  return p;
}

// power: raise base to n-th power; n >= 0; version 2
int power(int base, int n)
{
  int p;
  for (p = 1; n > 0; --n)
  {
    p = p * base;
  }
  return p;
}
