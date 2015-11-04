#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

struct vector
{
  size_t n_elems;
  size_t n_allocated;
  size_t elem_size;
  uint8_t *elems;
};

size_t vector_size(struct vector *s)
{
  return s->n_elems;
}

void *vector_back(struct vector *s)
{
  if (s->n_elems == 0)
  {
    return NULL;
  }
  return s->elems + ((s->n_elems - 1) * s->elem_size);
}

void *vector_get(struct vector *s, size_t i)
{
  if (i >= s->n_elems)
  {
    return NULL;
  }
  return s->elems + (i * s->elem_size);
}

void vector_pop_back(struct vector *s)
{
  if (s->n_elems > 0)
  {
    --s->n_elems;
  }
}

void vector_push_back(struct vector *s, void *e)
{
  if (s->n_elems == s->n_allocated)
  {
    s->n_allocated <<= 1;
    s->elems = realloc(s->elems, s->elem_size * s->n_allocated);
  }
  memcpy(s->elems + ((s->n_elems++) * s->elem_size), e, s->elem_size);
}

struct vector *vector_new(size_t elem_size)
{
  return vector_new_with_initial(elem_size, 0);
}

struct vector *vector_new_with_initial(size_t elem_size, size_t initial_allocated_elems)
{
  struct vector *s = malloc(sizeof(*s));
  s->n_elems = 0;
  s->n_allocated = initial_allocated_elems;
  s->elem_size = elem_size;
  s->elems = malloc(s->n_allocated * s->elem_size);
  return s;
}

void vector_free(struct vector *s)
{
  free(s->elems);
  free(s);
}
