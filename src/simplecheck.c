#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"

// Exercise 1-24. page 34

struct char_info
{
  int line;
  int col;
  int c;
};

#define NORMAL 0
#define OPENING_SLASH 1
#define C_COMMENT 2
#define LINE_COMMENT 3
#define CLOSING_STAR 4
#define IN_STRING 5
#define STRING_ESCAPE 6
#define IN_CHAR_LIT 7
#define CHAR_LIT_ESCAPE 8

static bool bracket_match(int x, int y)
{
  return (x == '{' && y == '}') || (x == '(' && y == ')') ||
         (x == '[' && y == ']');
}

static int normal(int c, struct vector *v, int line, int col)
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
    ci.c = c;
    ci.line = line;
    ci.col = col;
    vector_push_back(v, &ci);
    break;
  }
  case '}':
  case ']':
  case ')':
    if (vector_size(v) > 0)
    {
      struct char_info *ci = vector_back(v);
      vector_pop_back(v);
      if (!bracket_match(ci->c, c))
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

static int opening_slash(int c)
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

static int c_comment(int c)
{
  return c == '*' ? CLOSING_STAR : C_COMMENT;
}

static int closing_star(int c)
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

static int line_comment(int c)
{
  return c == '\n' ? NORMAL : LINE_COMMENT;
}

static int in_string(int c)
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

static int in_char_lit(int c)
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
  struct vector v;
  vector_init(&v, sizeof(struct char_info));
  while ((c = getchar()) != EOF)
  {
    ++col;
    switch (state)
    {
    case NORMAL:
      state = normal(c, &v, line, col);
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
  vector_deinit(&v);
}
