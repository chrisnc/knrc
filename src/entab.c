#include <stdio.h>

#include "getline.h"

// Exercise 1-21. page 34

#define TABSTOP 8
#define MAXLINE 1000

int main(void)
{
  char line[MAXLINE];
  size_t len;

  while ((len = my_getline(line, MAXLINE)) > 0)
  {
    size_t next_t;
    for (size_t t = 0; t < len; t = next_t)
    {
      next_t = t + TABSTOP;
      size_t blanks_to_replace = 0;
      size_t i;
      for (i = t; i < t + TABSTOP && i < len; ++i)
      {
        if (line[i] == ' ')
        {
          ++blanks_to_replace;
        }
        else if (line[i] == '\t')
        {
          next_t = i + 1;
          blanks_to_replace = TABSTOP;
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
