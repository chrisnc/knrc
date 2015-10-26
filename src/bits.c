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

// bitcount: count 1 bits in x
int bitcount(unsigned x)
{
  int b;
  for (b = 0; x != 0; x >>= 1)
  {
    if (x & 0x1)
    {
      ++b;
    }
  }
  return b;
}

// Exercise 2-9.
// popcnt, faster version of bitcount
// With x unsigned, x &= x - 1 deletes the rightmost 1-bit in x.
// This is because the rightmost 1-bit will either be in the zero'th position
// in which case subtracting 1 simply sets it to zero and leaves other bits
// unchanged (and &'ing with x leaves this bit unset and the other bits
// unchanged), or it is in some higher position with all lower-order bits zero,
// in which case subtracting 1 sets this bit to zero and all previous bits to
// 1. &'ing this with the original x sets all of these bits to zero, since the
// rightmost 1 was set to zero in (x - 1), and the lower order bits were all
// zero in x itself.
int popcnt(unsigned x)
{
  int b = 0;
  while (x)
  {
    ++b;
    x &= x - 1;
  }
  return b;
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

  printf("bitcount(0x%x) = %d\n", z, bitcount(z));
  printf("popcnt(0x%x) = %d\n", z, popcnt(z));
}
