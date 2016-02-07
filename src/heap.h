#ifndef HEAP_H
#define HEAP_H

#include <stddef.h>

#include "vector.h"

struct heap
{
  struct vector v;
  int (*cmp)(const void *, const void *);
};

void heap_init(struct heap *h, size_t elem_size,
               int (*cmp)(const void *, const void *));

void heap_deinit(struct heap *h);

const void *heap_min(const struct heap *h);

void heap_pop_min(struct heap *h);

void heap_insert(struct heap *h, const void *e);

size_t heap_size(const struct heap *h);

#endif // HEAP_H
