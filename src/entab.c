#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "getline.h"

// Exercise 1-21. page 34

// Exercise 5-11. page 118
// modified to accept a list of tabstops in argv

// Exercise 5-12. page 118
// modified to accept -m +n for tab stops every N columns
// starting at column m.

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
      fprintf(stderr, "entab: illegal option -%s\n", *argv);
      return EXIT_FAILURE;
    }
    if (**argv == '+' && sscanf(*argv + 1, "%zu", &n) != 1)
    {
      fprintf(stderr, "entab: illegal option %s\n", *argv);
      return EXIT_FAILURE;
    }
  }

  char line[MAXLINE];
  size_t len;

  while ((len = my_getline(line, MAXLINE)) > 0)
  {
    size_t next_t;
    size_t tabstop;
    bool first_tabstop = true;
    for (size_t t = 0; t < len; t = next_t)
    {
      if (*argv || sscanf(*argv++, "%zu", &tabstop) != 1)
      {
        tabstop = n;
      }
      if (first_tabstop)
      {
        tabstop += m;
        first_tabstop = false;
      }
      next_t = t + tabstop;
      size_t blanks_to_replace = 0;
      size_t i;
      for (i = t; i < t + tabstop && i < len; ++i)
      {
        if (line[i] == ' ')
        {
          ++blanks_to_replace;
        }
        else if (line[i] == '\t')
        {
          next_t = i + 1;
          blanks_to_replace = tabstop;
          break;
        }
        else
        {
          while (blanks_to_replace > 0)
          {
            putchar(' ');
            --blanks_to_replace;
          }
          putchar(line[i]);
        }
      }
      // line ended before the next tabstop
      if (i + 1 < next_t)
      {
        while (blanks_to_replace > 0)
        {
          putchar(' ');
          --blanks_to_replace;
        }
        break;
      }
      if (blanks_to_replace >= 1)
      {
        putchar('\t');
      }
    }
  }
}
