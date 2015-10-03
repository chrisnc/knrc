#include <stdio.h>
#include <limits.h>

// getbits: get n bits from position p through p + n - 1
// (modified from book, which starts at p and counts down...
unsigned getbits(unsigned x, int p, int n)
{
  return (x >> p) & ~(~0 << n);
}

// Exercise 2-6.
// set the n bits in x starting at position p with the first n bits of y
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
  unsigned mask = ((~0 >> p) << p) & ~(~0 << (n + p));
  return (x & ~mask) | ((y << p) & mask);
}

// Exercise 2-7.
// invert the n bits in x starting at position p
unsigned invert(unsigned x, int p, int n)
{
  return x ^ (((~0 >> p) << p) & ~(~0 << (n + p)));
}

// Exercise 2-8.
// returns x rotated right by n positions
unsigned rightrot(unsigned x, int n)
{
  static const int s = sizeof(unsigned) * CHAR_BIT;
  n %= s; // required to avoid overly large shifts
  if (n == 0) // a shift of (s - 0) is undefined
  {
    return x;
  }
  return (x >> n) | (x << (s - n));
}

int main(void)
{
  unsigned x = 0xff00ff00;
  int p = 8;
  int n = 4;
  unsigned y = 0xc;
  unsigned z = setbits(x, p, n, y);
  printf("setbits(0x%x, %d, %d, 0x%x) = 0x%x\n", x, p, n, y, z);
  z = setbits(z, 0, 4, 0xf);
  printf("getbits(0x%x, %d, %d) = 0x%x\n", z, p, n, getbits(z, p, n));
  printf("invert(0x%x, %d, %d) = 0x%x\n", z, p, n, invert(z, p, n));
  n = -36;
  printf("rightrot(0x%x, %d) = 0x%x\n", z, n, rightrot(z, n));
}
