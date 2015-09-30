#include <stdio.h>
#include <limits.h>

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

// Exercise 1-14.
void char_histogram(void)
{
  const int N_CHARS = 1 << (sizeof(char) * CHAR_BIT);
  int c;
  int hist[N_CHARS];
  for (int i = 0; i < N_CHARS; ++i)
  {
    hist[i] = 0;
  }

  printf("N_CHARS = %d\n", N_CHARS);

  while ((c = getchar()) != EOF)
  {
    printf("found a %c\n", c);
    ++hist[(unsigned char)c];
  }
  printf("char   frequency\n");
  for (int i = 0; i < N_CHARS; ++i)
  {
    if (i < 32) // below SPC
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

int main(void)
{
  //word_length_histogram();
  char_histogram();
}
