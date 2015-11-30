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

// some convenience macros for creating heaps of a particular type
#define HEAP_TEMPLATE(type, name)                                              \
  int heap_##name##_cmp(const void *, const void *);                           \
  inline int heap_##name##_cmp(const void *a, const void *b)                   \
  {                                                                            \
    type x = *(const type *)a;                                                 \
    type y = *(const type *)b;                                                 \
    if (x < y)                                                                 \
    {                                                                          \
      return -1;                                                               \
    }                                                                          \
    if (x > y)                                                                 \
    {                                                                          \
      return 1;                                                                \
    }                                                                          \
    return 0;                                                                  \
  }                                                                            \
  HEAP_TEMPLATE_CMP(type, name, heap_##name##_cmp)

#define HEAP_TEMPLATE_CMP(type, name, cmp)                                     \
                                                                               \
  inline void heap_init_##name(struct heap *h)                                 \
  {                                                                            \
    heap_init(h, sizeof(type), cmp);                                           \
  }                                                                            \
                                                                               \
  inline const type *heap_min_##name(struct heap *h)                           \
  {                                                                            \
    return heap_min(h);                                                        \
  }                                                                            \
                                                                               \
  inline void heap_insert_##name(struct heap *h, type *e)                      \
  {                                                                            \
    heap_insert(h, e);                                                         \
  }

#endif // HEAP_H
