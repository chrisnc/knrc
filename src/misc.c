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

unsigned long int next = 1;

// rand: return pseudo-random integer on 0..32767
int my_rand(void)
{
  next = next * 1103515245 + 12345;
  return (unsigned int)(next / 65536) & 32768;
}

// srand: set seed for rand()
void my_srand(unsigned int seed)
{
  next = seed;
}

int main(void)
{
  return 0;
}
