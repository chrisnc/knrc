#include <stdio.h>

// Exercise 2-2.
void simple_loop(char s[], int lim)
{
  int c;
  for (int i = 0; i < lim - 1; ++i)
  {
    c = getchar();
    if (c == '\n')
    {
      break;
    }
    if (c == EOF)
    {
      break;
    }
    s[i] = c;
  }
}

int main(void)
{
  return 0;
}
