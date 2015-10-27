#include <stdio.h>
#include <stdlib.h>

// Exercise 1-20. page 34

#define TABSTOP 8

int main(void)
{
  size_t n = 0;
  char *line = NULL;
  ssize_t len;

  while ((len = getline(&line, &n, stdin)) != -1)
  {
    int col = 0;
    for (ssize_t i = 0; i < len; ++i)
    {
      if (line[i] == '\t')
      {
        for (ssize_t rem = TABSTOP - (col % TABSTOP); rem > 0; --rem)
        {
          ++col;
          putchar(' ');
        }
      }
      else
      {
        ++col;
        putchar(line[i]);
      }
    }
  }
  free(line);
}
