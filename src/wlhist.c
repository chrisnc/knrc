#include <stdio.h>

// Exercise 1-13. page 24

#define MAX_WORD_LEN 20
#define IN 1
#define OUT 0

int main(void)
{
  int state = OUT;
  int hist[MAX_WORD_LEN + 1];
  for (int i = 0; i <= MAX_WORD_LEN; ++i)
  {
    hist[i] = 0;
  }
  int nlong_words = 0;
  int nc = 0;
  int c;
  while ((c = getchar()) != EOF)
  {
    if (c == ' ' || c == '\n' || c == '\t')
    {
      if (state == IN)
      {
        if (nc <= MAX_WORD_LEN)
        {
          ++hist[nc];
        }
        else
        {
          ++nlong_words;
        }
      }
      state = OUT;
      nc = 0;
    }
    else
    {
      state = IN;
      ++nc;
    }
  }
  printf("length frequency\n");
  for (int i = 0; i <= MAX_WORD_LEN; ++i)
  {
    printf("%6d ", i);
    for (int n = 0; n < hist[i]; ++n)
    {
      putchar('#');
    }
    putchar('\n');
  }
  printf("longer ");
  for (int n = 0; n < nlong_words; ++n)
  {
    putchar('#');
  }
  putchar('\n');
}
