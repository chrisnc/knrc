#include <stdio.h>

#include "getline.h"

// Exercise 1-20. page 34

#define TABSTOP 8
#define MAXLINE 1000

int main(void)
{
  char line[MAXLINE];
  size_t len;
  while ((len = my_getline(line, MAXLINE)) > 0)
  {
    int col = 0;
    for (size_t i = 0; i < len; ++i)
    {
      if (line[i] == '\t')
      {
        for (size_t rem = TABSTOP - (col % TABSTOP); rem > 0; --rem)
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
}
