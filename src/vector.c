#include "vector.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

size_t vector_size(const struct vector *v)
{
  return v->n_elems;
}

static void *at(const struct vector *v, size_t i)
{
  if (i >= v->n_elems)
  {
    return NULL;
  }
  return v->data + (i * v->elem_size);
}

void *vector_at(struct vector *v, size_t i)
{
  return at(v, i);
}

const void *vector_at_const(const struct vector *v, size_t i)
{
  return at(v, i);
}

void *vector_back(struct vector *v)
{
  return at(v, vector_size(v) - 1);
}

const void *vector_back_const(const struct vector *v)
{
  return at(v, vector_size(v) - 1);
}

void vector_pop_back(struct vector *v)
{
  if (v->n_elems > 0)
  {
    --v->n_elems;
  }
}

void vector_push_back(struct vector *v, const void *e)
{
  if (v->n_elems == v->n_allocated)
  {
    v->n_allocated <<= 1;
    v->data = realloc(v->data, v->elem_size * v->n_allocated);
  }
  memcpy(vector_at(v, v->n_elems++), e, v->elem_size);
}

void vector_swap(struct vector *v, size_t i, size_t j)
{
  void *tmpbuf = malloc(v->elem_size);
  memcpy(tmpbuf, vector_at(v, i), v->elem_size);
  memcpy(vector_at(v, i), vector_at(v, j), v->elem_size);
  memcpy(vector_at(v, j), tmpbuf, v->elem_size);
  free(tmpbuf);
}

void vector_init(struct vector *v, size_t elem_size)
{
  vector_init_with_capacity(v, elem_size, 1);
}

void vector_init_with_capacity(struct vector *v, size_t elem_size,
                               size_t capacity)
{
  v->n_elems = 0;
  v->n_allocated = capacity;
  v->elem_size = elem_size;
  v->data = malloc(v->n_allocated * v->elem_size);
}

void vector_deinit(struct vector *v)
{
  free(v->data);
}
