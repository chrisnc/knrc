#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#include "arc4random.h"
#include "heap.h"

static int u32_cmp(const void *a, const void *b)
{
  const uint32_t *x = a, *y = b;
  if (*x < *y)
  {
    return -1;
  }
  if (*x > *y)
  {
    return 1;
  }
  return 0;
}

int main(void)
{
  struct heap h;
  heap_init(&h, sizeof(uint32_t), u32_cmp);

  for (size_t i = 0; i < 1000; ++i)
  {
    uint32_t x = arc4random();
    heap_insert(&h, &x);
  }

  while (heap_size(&h) > 0)
  {
    uint32_t x = *(const uint32_t *)heap_min(&h);
    heap_pop_min(&h);
    printf("%u\n", x);
  }

  heap_deinit(&h);
}
