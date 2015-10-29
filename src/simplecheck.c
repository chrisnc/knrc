#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Exercise 1-24. page 34

struct char_info
{
  char c;
  int line;
  int col;
};

struct vector
{
  size_t n_elems;
  size_t n_allocated;
  size_t elem_size;
  uint8_t *elems;
};

void *back(struct vector *s)
{
  if (s->n_elems == 0)
  {
    fprintf(stderr, "back on an empty vector\n");
    exit(1);
  }
  return s->elems + ((s->n_elems - 1) * s->elem_size);
}

void *get(struct vector *s, size_t i)
{
  if (i >= s->n_elems)
  {
    fprintf(stderr, "get for index %zu out of range, size: %zu\n", i,
            s->n_elems);
    exit(1);
  }
  return s->elems + (i * s->elem_size);
}

void pop_back(struct vector *s)
{
  if (s->n_elems == 0)
  {
    fprintf(stderr, "pop_back on an empty vector\n");
    exit(1);
  }
  --s->n_elems;
}

void push_back(struct vector *s, void *e)
{
  if (s->n_elems == s->n_allocated)
  {
    s->n_allocated <<= 1;
    s->elems = realloc(s->elems, s->elem_size * s->n_allocated);
  }
  memcpy(s->elems + ((s->n_elems++) * s->elem_size), e, s->elem_size);
}

struct vector *new_vector(size_t initial_alloc, size_t elem_size)
{
  struct vector *s = malloc(sizeof(*s));
  s->n_elems = 0;
  s->n_allocated = initial_alloc;
  s->elem_size = elem_size;
  s->elems = malloc(s->n_allocated * s->elem_size);
  return s;
}

void destroy_vector(struct vector *s)
{
  free(s->elems);
  free(s);
}

#define NORMAL 0
#define OPENING_SLASH 1
#define C_COMMENT 2
#define LINE_COMMENT 3
#define CLOSING_STAR 4
#define IN_STRING 5
#define STRING_ESCAPE 6
#define IN_CHAR_LIT 7
#define CHAR_LIT_ESCAPE 8

bool bracket_match(char x, char y)
{
  return (x == '{' && y == '}') || (x == '(' && y == ')') ||
         (x == '[' && y == ']');
}

int normal(int c, struct vector *s, int line, int col)
{
  switch (c)
  {
  case '/':
    return OPENING_SLASH;
  case '"':
    return IN_STRING;
  case '\'':
    return IN_CHAR_LIT;
  case '{':
  case '[':
  case '(':
  {
    struct char_info ci;
    ci.c = (char) c;
    ci.line = line;
    ci.col = col;
    push_back(s, &ci);
    break;
  }
  case '}':
  case ']':
  case ')':
    if (s->n_elems > 0)
    {
      struct char_info *ci = back(s);
      pop_back(s);
      if (!bracket_match(ci->c, (char) c))
      {
        printf("line %d, col %d: '%c' is not closed, unexpected '%c' on "
               "line %d, col %d\n",
               ci->line, ci->col, ci->c, c, line, col);
      }
    }
    else
    {
      printf("line %d, col %d, unexpected '%c'\n", line, col, c);
    }
    break;
  default:; // all other characters, no special behavior
  }
  return NORMAL;
}

int opening_slash(int c)
{
  switch (c)
  {
  case '*':
    return C_COMMENT;
  case '/':
    return LINE_COMMENT;
  default:
    return NORMAL;
  }
}

int c_comment(int c)
{
  return c == '*' ? CLOSING_STAR : C_COMMENT;
}

int closing_star(int c)
{
  switch (c)
  {
  case '/':
    return NORMAL;
  case '*':
    return CLOSING_STAR;
  default:
    return C_COMMENT;
  }
}

int line_comment(int c)
{
  return c == '\n' ? NORMAL : LINE_COMMENT;
}

int in_string(int c)
{
  switch (c)
  {
  case '"':
    return NORMAL;
  case '\\':
    return STRING_ESCAPE;
  default:
    return IN_STRING;
  }
}

int in_char_lit(int c)
{
  switch (c)
  {
  case '\'':
    return NORMAL;
  case '\\':
    return CHAR_LIT_ESCAPE;
  default:
    return IN_CHAR_LIT;
  }
}

int main(void)
{
  int c;
  int state = NORMAL;
  int line = 1;
  int col = 0;
  struct vector *s = new_vector(128, sizeof(struct char_info));
  while ((c = getchar()) != EOF)
  {
    ++col;
    switch (state)
    {
    case NORMAL:
      state = normal(c, s, line, col);
      break;
    case OPENING_SLASH:
      state = opening_slash(c);
      break;
    case C_COMMENT:
      state = c_comment(c);
      break;
    case CLOSING_STAR:
      state = closing_star(c);
      break;
    case LINE_COMMENT:
      state = line_comment(c);
      break;
    case IN_STRING:
      state = in_string(c);
      break;
    case IN_CHAR_LIT:
      state = in_char_lit(c);
      break;
    case STRING_ESCAPE:
      state = IN_STRING;
      break;
    case CHAR_LIT_ESCAPE:
      state = IN_CHAR_LIT;
      break;
    default:
      printf("error, unknown state: %d\n", state);
      return 1;
    }
    if (c == '\n')
    {
      ++line;
      col = 0;
    }
  }
  destroy_vector(s);
}
