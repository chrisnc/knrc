#include "heap.h"

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

// node   0 1 2 3 4 5 6 7 8 9 10
// parent X 0 0 1 1 2 2 3 3 4  4
static inline size_t parent(size_t i)
{
  return (i - 1) / 2;
}

// node   0 1 2 3 4
// left   1 3 5 7 9
// right  2 4 6 8 10
static inline size_t left_child(size_t i)
{
  return (i * 2) + 1;
}

static inline size_t right_child(size_t i)
{
  return (i * 2) + 2;
}

static inline const void *at(const struct heap *h, size_t i)
{
  return vector_at_const(&h->v, i);
}

static void bubble_up(struct heap *h, size_t i)
{
  if (i == 0)
  {
    return;
  }
  size_t p = parent(i);
  if (h->cmp(at(h, i), at(h, p)) < 0)
  {
    vector_swap(&h->v, i, p);
    bubble_up(h, p);
  }
}

static void bubble_down(struct heap *h, size_t i)
{
  size_t l = left_child(i);
  size_t r = right_child(i);
  size_t sz = heap_size(h);

  if (l >= sz) // i has no children
  {
    return;
  }

  const void *iptr = at(h, i);
  const void *lptr = at(h, l);

  int lcmpi = h->cmp(lptr, iptr);

  if (r >= sz) // i has only a left child
  {
    if (lcmpi < 0) // l < i
    {
      vector_swap(&h->v, i, l);
      bubble_down(h, l);
    }
    return;
  }

  const void *rptr = at(h, r);
  int lcmpr = h->cmp(lptr, rptr);
  int rcmpi = h->cmp(rptr, iptr);

  if (lcmpi < 0 && lcmpr < 0) // l < i && l < r
  {
    vector_swap(&h->v, i, l);
    bubble_down(h, l);
  }
  else if (rcmpi < 0) // (r < i <= l) || (r < i && r <= l)
  {
    vector_swap(&h->v, i, r);
    bubble_down(h, r);
  }
}

void heap_init(struct heap *h, size_t elem_size, int (*cmp)(const void *, const void *))
{
  vector_init(&h->v, elem_size);
  h->cmp = cmp;
}

void heap_deinit(struct heap *h)
{
  vector_deinit(&h->v);
}

const void *heap_min(const struct heap *h)
{
  return at(h, 0);
}

void heap_pop_min(struct heap *h)
{
  vector_swap(&h->v, 0, heap_size(h) - 1);
  vector_pop_back(&h->v);
  bubble_down(h, 0);
}

size_t heap_size(const struct heap *h)
{
  return vector_size(&h->v);
}

void heap_insert(struct heap *h, const void *e)
{
  vector_push_back(&h->v, e);
  bubble_up(h, heap_size(h) - 1);
}
