#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "arc4random.h"
#include "heap.h"

HEAP_TEMPLATE(uint32_t, u32)

int main(void)
{
  struct heap h;
  heap_init_u32(&h);

  for (size_t i = 0; i < 1000; ++i)
  {
    uint32_t x = arc4random();
    heap_insert_u32(&h, x);
  }

  while (heap_size(&h) > 0)
  {
    uint32_t x = *heap_min_u32(&h);
    heap_pop_min(&h);
    printf("%u\n", x);
  }

  heap_deinit(&h);
}
