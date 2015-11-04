#ifndef BITS_H
#define BITS_H

unsigned setbits(unsigned x, int p, int n, unsigned y);
unsigned getbits(unsigned x, int p, int n);
unsigned invert(unsigned x, int p, int n);
unsigned rightrot(unsigned x, int n);
int bitcount(unsigned x);
int popcnt(unsigned x);

#endif // BITS_H
