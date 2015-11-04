#include <stdio.h>

#define IN 1  // inside a word
#define OUT 0 // outside a word

// Exercise 1-12. page 21
int main(void)
{
  int state = OUT;
  int c;
  while ((c = getchar()) != EOF)
  {
    if (c == ' ' || c == '\n' || c == '\t')
    {
      if (state == IN)
      {
        putchar('\n');
      }
      state = OUT;
    }
    else
    {
      state = IN;
      putchar(c);
    }
  }
}
