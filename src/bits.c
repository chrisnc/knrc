#include <stdio.h>
#include <limits.h>

#include "bits.h"

// getbits: get n bits from position p through p + n - 1
// (modified from book, which starts at p and counts down...
unsigned getbits(unsigned x, int p, int n)
{
  return (x >> p) & ~(~0U << n);
}

// Exercise 2-6. page 49
// set the n bits in x starting at position p with the first n bits of y
unsigned setbits(unsigned x, int p, int n, unsigned y)
{
  const unsigned mask = ((~0U >> p) << p) & ~(~0U << (n + p));
  return (x & ~mask) | ((y << p) & mask);
}

// Exercise 2-7. page 49
// invert the n bits in x starting at position p
unsigned invert(unsigned x, int p, int n)
{
  return x ^ (((~0U >> p) << p) & ~(~0U << (n + p)));
}

// Exercise 2-8. page 49
// returns x rotated right by n positions
unsigned rightrot(unsigned x, int n)
{
  static const unsigned nbits = sizeof(unsigned) * CHAR_BIT;
  const unsigned s = (unsigned)n % nbits; // required to avoid overly large shifts

  // 0 <= s < nbits
  // a left shift of (nbits - 0) is undefined
  // so just return the input if asked to rotate by 0
  if (s == 0)
  {
    return x;
  }

  return (x >> s) | (x << (nbits - s));
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

/*
 * Exercise 2-9. page 51
 * popcnt, faster version of bitcount
 * With x unsigned, x &= x - 1 deletes the rightmost 1-bit in x.
 * If the rightmost bit is 1, subtracting 1 sets the rightmost bit to 0 and
 * leaves the other bits unchanged. Bitwise and of this number and the original
 * is equal to x with the rightmost bit set to 0.
 *
 *  x           = 11100101111
 *       x - 1  = 11100101110
 *  x & (x - 1) = 11100101110
 *
 * If the rightmost 1 bit is in some higher position with all lower-order bits
 * 0, subtracting 1 sets all the lower-order bits to 1 due to borrowing
 * subtraction, and the higher position 1 bit is set to 0.
 * A bitwise & of this number with the original x sets all of these bits to
 * 0, since the rightmost 1 was set to zero in (x - 1), and the lower order
 * bits were all zero in x itself.
 *
 *  x           = 11100110000
 *       x - 1  = 11100101111
 *  x & (x - 1) = 11100100000
 */
int popcnt(unsigned x)
{
  int b;
  for (b = 0; x; ++b)
  {
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

  n = 0;
  printf("rightrot(0x%x, %d) = 0x%x\n", z, n, rightrot(z, n));

  n = INT_MIN;
  printf("rightrot(0x%x, %d) = 0x%x\n", z, n, rightrot(z, n));

  printf("bitcount(0x%x) = %d\n", z, bitcount(z));
  printf("popcnt(0x%x) = %d\n", z, popcnt(z));
}
