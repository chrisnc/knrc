#include <stdio.h>

#define IN 1  // inside a word
#define OUT 0 // outside a word

int main(void)
{
  int state = OUT;
  int nl = 0, nw = 0, nc = 0;
  int c;
  while ((c = getchar()) != EOF)
  {
    ++nc;
    if (c == '\n')
    {
      ++nl;
    }
    if (c == ' ' || c == '\n' || c == '\t')
    {
      state = OUT;
    }
    else if (state == OUT)
    {
      state = IN;
      ++nw;
    }
  }
  printf("%d %d %d\n", nl, nw, nc);
}

/*
 * Exercise 1-11. page 21
 * Feeding the wc program random inputs, or generating random inputs with
 * a sufficient mix of ' ', '\n', and '\t' characters.
 */
