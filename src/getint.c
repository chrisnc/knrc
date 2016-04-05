#include <ctype.h>
#include <stdio.h>

static int getch(void)
{
  return getc(stdin);
}

static void ungetch(int c)
{
  ungetc(c, stdin);
}

// getint: get next integer from input into *pn
static int getint(int *pn)
{
  int c;
  while (isspace(c = getch())) // skip white space
  {
  }
  if (!isdigit(c) && c != EOF && c != '+' && c != '-')
  {
    ungetch(c);
    return 0;
  }
  int sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-')
  {
    // Exercise 5-1. page 97
    int next = getch();
    if (!isdigit(next))
    {
      ungetch(next);
      ungetch(c);
      return 0;
    }
    c = next;
  }
  for (*pn = 0; isdigit(c); c = getch())
  {
    *pn = 10 * *pn + (c - '0');
  }
  *pn *= sign;
  if (c != EOF)
  {
    ungetch(c);
  }
  return c;
}

// Exercise 5-2. page 97
// the return type is int with the same semantics as getint
// EOF for end of file, 0 if the next input is not a number, and positive for a
// successful parse
static int getfloat(float *pn)
{
  int c;
  while (isspace(c = getch())) // skip white space
  {
  }
  if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
  {
    ungetch(c);
    return 0;
  }
  int sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-' || c == '.')
  {
    int next = getch();
    if (!isdigit(next))
    {
      ungetch(next);
      ungetch(c);
      return 0;
    }
    if (c == '.')
    {
      ungetch(next);
    }
    else
    {
      c = next;
    }
  }

  for (*pn = 0.0; isdigit(c); c = getch())
  {
    *pn = 10.0f * *pn + (c - '0');
  }
  if (c == '.')
  {
    c = getch();
  }
  float power;
  for (power = 1.0f; isdigit(c); c = getch())
  {
    *pn = 10.0f * *pn + (c - '0');
    power *= 10.0f;
  }
  if (c == 'e' || c == 'E')
  {
    c = getch();
    int expsign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
    {
      c = getch();
    }
    int exponent = 0;
    for (; isdigit(c); c = getch())
    {
      exponent = 10 * exponent + (c - '0');
    }
    for (int e = 0; e < exponent; ++e)
    {
      if (expsign > 0)
      {
        power /= 10.0f;
      }
      else
      {
        power *= 10.0f;
      }
    }
  }

  *pn = sign * *pn / power;

  return c;
}

int main(void)
{
  int x;
  int r;
  for (int i = 0; i < 2; ++i)
  {
    if ((r = getint(&x)) <= 0)
    {
      printf("getint returned %d\n", r);
      return 1;
    }
    printf("read %d\n", x);
  }

  float f;
  for (int i = 0; i < 2; ++i)
  {
    if ((r = getfloat(&f)) <= 0)
    {
      printf("getfloat returned %d\n", r);
      return 1;
    }
    printf("read %f\n", (double)f);
  }
}
