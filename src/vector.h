#ifndef VECTOR_H
#define VECTOR_H

struct vector;

size_t vector_size(struct vector *s);

void *vector_back(struct vector *s);

void *vector_get(struct vector *s, size_t i);

void vector_pop_back(struct vector *s);

void vector_push_back(struct vector *s, void *e);

struct vector *vector_new(size_t elem_size);

struct vector *vector_new_alloc(size_t elem_size, size_t initial_alloc);

void vector_free(struct vector *s);

#endif // VECTOR_H
