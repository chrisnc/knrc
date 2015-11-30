#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

struct vector
{
  size_t n_elems;
  size_t n_allocated;
  size_t elem_size;
  void *data;
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

// a convenience template for vectors containing a specific type
#define VECTOR_TEMPLATE(type, name)                                            \
                                                                               \
  inline type *vector_at_##name(struct vector *v, size_t i)                    \
  {                                                                            \
    return vector_at(v, i);                                                    \
  }                                                                            \
                                                                               \
  inline const type *vector_at_const_##name(struct vector *v, size_t i)        \
  {                                                                            \
    return vector_at_const(v, i);                                              \
  }                                                                            \
                                                                               \
  inline type *vector_back_##name(struct vector *v)                            \
  {                                                                            \
    return vector_back(v);                                                     \
  }                                                                            \
                                                                               \
  inline const type *vector_back_const_##name(struct vector *v)                \
  {                                                                            \
    return vector_back_const(v);                                               \
  }                                                                            \
                                                                               \
  inline void vector_push_back_##name(struct vector *v, type *e)               \
  {                                                                            \
    vector_push_back(v, e);                                                    \
  }                                                                            \
                                                                               \
  inline void vector_init_##name(struct vector *v)                             \
  {                                                                            \
    vector_init(v, sizeof(type));                                              \
  }

#endif // VECTOR_H
