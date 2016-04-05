#include <limits.h>
#include <stdio.h>

#define N_CHARS (1 << (sizeof(char) * CHAR_BIT))

// Exercise 1-14. page 24

int main(void)
{
  int c;
  int hist[N_CHARS];
  for (int i = 0; i < N_CHARS; ++i)
  {
    hist[i] = 0;
  }

  printf("N_CHARS = %d\n", N_CHARS);

  while ((c = getchar()) != EOF)
  {
    ++hist[(unsigned char)c];
  }
  printf("char   frequency\n");
  for (int i = 0; i < N_CHARS; ++i)
  {
    if (i < ' ') // below SPC are control characters
    {
      printf("\\x%-4x", i);
    }
    else if (i >= 127) // DEL and above
    {
      continue;
    }
    else
    {
      printf("%-6c", (char)i);
    }
    for (int n = 0; n < hist[i]; ++n)
    {
      putchar('#');
    }
    putchar('\n');
  }
}
