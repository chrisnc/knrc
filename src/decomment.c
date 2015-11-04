#include <stdio.h>

// Exercise 1-23. page 34

#define NO_COMMENT 0
#define OPENING_SLASH 1
#define C_COMMENT 2
#define CLOSING_STAR 3
#define LINE_COMMENT 4
#define IN_STRING 5
#define IN_CHAR_LIT 6
#define STRING_ESCAPE 7
#define CHAR_LIT_ESCAPE 8

static int no_comment(int c)
{
  if (c == '/')
  {
    return OPENING_SLASH;
  }
  putchar(c);
  if (c == '"')
  {
    return IN_STRING;
  }
  if (c == '\'')
  {
    return IN_CHAR_LIT;
  }
  return NO_COMMENT;
}

static int opening_slash(int c)
{
  if (c == '*')
  {
    return C_COMMENT;
  }
  if (c == '/')
  {
    return LINE_COMMENT;
  }
  putchar('/');
  putchar(c);
  return NO_COMMENT;
}

static int c_comment(int c)
{
  if (c == '*')
  {
    return CLOSING_STAR;
  }
  return C_COMMENT;
}

static int closing_star(int c)
{
  if (c == '/')
  {
    return NO_COMMENT;
  }
  if (c == '*')
  {
    return CLOSING_STAR;
  }
  return C_COMMENT;
}

static int line_comment(int c)
{
  if (c == '\n')
  {
    putchar('\n');
    return NO_COMMENT;
  }
  return LINE_COMMENT;
}

static int in_string(int c)
{
  putchar(c);
  if (c == '"')
  {
    return NO_COMMENT;
  }
  if (c == '\\')
  {
    return STRING_ESCAPE;
  }
  return IN_STRING;
}

static int in_char_lit(int c)
{
  putchar(c);
  if (c == '\'')
  {
    return NO_COMMENT;
  }
  if (c == '\\')
  {
    return CHAR_LIT_ESCAPE;
  }
  return IN_CHAR_LIT;
}

static int string_escape(int c)
{
  putchar(c);
  return IN_STRING;
}

static int char_lit_escape(int c)
{
  putchar(c);
  return IN_CHAR_LIT;
}

int main(void)
{
  int c;
  int state = NO_COMMENT;
  while ((c = getchar()) != EOF)
  {
    switch (state)
    {
    case NO_COMMENT:
      state = no_comment(c);
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
      state = string_escape(c);
      break;
    case CHAR_LIT_ESCAPE:
      state = char_lit_escape(c);
      break;
    default:
      printf("error, unknown state: %d\n", state);
      return 1;
    }
  }
}
