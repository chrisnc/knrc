#include <stdio.h>

void count_digits_and_whitespace(void)
{
  int nwhite, nother;
  int ndigit[10];

  nwhite = nother = 0;
  for (int i = 0; i < 10; ++i)
  {
    ndigit[i] = 0;
  }

  int c;
  while ((c = getchar()) != EOF)
  {
    if (c >= '0' && c <= '9')
    {
      ++ndigit[c - '0'];
    }
    else if (c == ' ' || c == '\n' || c == '\t')
    {
      ++nwhite;
    }
    else
    {
      ++nother;
    }
  }
  printf("digits =");
  for (int i = 0; i < 10; ++i)
  {
    printf(" %d", ndigit[i]);
  }
  printf(", white space = %d, other = %d\n", nwhite, nother);
}

// Exercise 1-13.

#define MAX_WORD_LEN 20
#define IN 1
#define OUT 0

void word_length_histogram(void)
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
  printf("length\n");
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

int main(void)
{
  word_length_histogram();
}
