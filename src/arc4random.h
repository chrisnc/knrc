#ifndef ARC4RANDOM_H
#define ARC4RANDOM_H

#if defined(linux)

#include <bsd/stdlib.h>

#else

#include <stdlib.h>

#if defined(_MSC_VER)

#include <stdint.h>
// implement arc4random in terms of MSVC's rand_s
static uint32_t arc4random(void)
{
  uint32_t res;
  rand_s(&res);
  return res;
}

#endif // _MSC_VER

#endif // linux

#endif // ARC4RANDOM_H
