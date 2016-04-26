#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "getline.h"

// Exercise 1-20. page 34

// Exercise 5-11. page 118
// modified to accept a list of tabstops in argv

#define TABSTOP_DEFAULT 8
#define MAXLINE 1000

int main(int argc, char **argv)
{
  size_t m = 0;
  size_t n = TABSTOP_DEFAULT;
  while (--argc > 0)
  {
    ++argv;
    if (**argv == '-' && sscanf(*argv + 1, "%zu", &m) != 1)
    {
      fprintf(stderr, "detab: illegal option -%s\n", *argv);
      return EXIT_FAILURE;
    }
    if (**argv == '+' && sscanf(*argv + 1, "%zu", &n) != 1)
    {
      fprintf(stderr, "detab: illegal option %s\n", *argv);
      return EXIT_FAILURE;
    }
  }

  char line[MAXLINE];
  size_t len;

  while ((len = my_getline(line, MAXLINE)) > 0)
  {
    bool first_tabstop = true;
    size_t col = 0;
    for (size_t i = 0; i < len; ++i)
    {
      if (line[i] == '\t')
      {
        size_t tabstop;
        if (*argv || sscanf(*argv++, "%zu", &tabstop) != 1)
        {
          tabstop = n;
        }
        if (first_tabstop)
        {
          tabstop += m;
          first_tabstop = false;
        }
        for (size_t rem = tabstop - ((col - m) % tabstop); rem > 0; --rem)
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
