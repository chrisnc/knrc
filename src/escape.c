#include <stdio.h>

// Exercise 3-2. page 60

int main(void)
{
  int c;
  while ((c = getchar()) != EOF)
  {
    switch (c)
    {
    case '\t':
      putchar('\\');
      putchar('t');
      break;
    case '\n':
      putchar('\\');
      putchar('n');
      break;
    case '\\':
      putchar('\\');
      putchar('\\');
      break;
    default:
      putchar(c);
      break;
    }
  }
}
