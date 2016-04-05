#include <stdbool.h>
#include <stdio.h>

// Exercise 3-2. part 2 page 60

int main(void)
{
  int c;
  bool escaped = false;
  while ((c = getchar()) != EOF)
  {
    if (escaped)
    {
      switch (c)
      {
      case 'n':
        putchar('\n');
        break;
      case 't':
        putchar('\t');
        break;
      default:
        putchar(c);
        break;
      }
      escaped = false;
    }
    else
    {
      if (c == '\\')
      {
        escaped = true;
      }
      else
      {
        putchar(c);
      }
    }
  }
}
