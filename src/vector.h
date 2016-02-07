#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

struct vector
{
  size_t n_elems;
  size_t n_allocated;
  size_t elem_size;
  unsigned char *data;
};

size_t vector_size(const struct vector *v);

void *vector_at(struct vector *v, size_t i);

const void *vector_at_const(const struct vector *v, size_t i);

void *vector_back(struct vector *v);

const void *vector_back_const(const struct vector *v);

void vector_pop_back(struct vector *v);

void vector_push_back(struct vector *v, const void *e);

void vector_swap(struct vector *v, size_t i, size_t j);

void vector_init(struct vector *v, size_t elem_size);

void vector_init_with_capacity(struct vector *v, size_t elem_size,
                               size_t capacity);

void vector_deinit(struct vector *v);

#endif // VECTOR_H
