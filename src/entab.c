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
    for (size_t s = 0; s < len;)
    {
      // find the index of the last character before the next tab stop
      size_t e;
      for (e = s; e < s + TABSTOP - 1; ++e)
      {
        if (line[e] == '\t')
        {
          break;
        }
      }
      size_t next_s = e + 1;
      size_t blanks_to_replace = 0;
      if (e >= len) // the line doesn't reach the next tab stop
      {
        e = len - 1;
      }
      else
      {
        // walk back from the last character until there are no more
        // consecutive spaces and tabs
        for (; e >= s; --e)
        {
          if (line[e] == ' ')
          {
            ++blanks_to_replace;
          }
          else if (line[e] == '\t')
          {
            blanks_to_replace += TABSTOP;
          }
          else
          {
            break;
          }
        }
      }
      for (size_t i = s; i <= e; ++i)
      {
        putchar(line[i]);
      }
      if (blanks_to_replace == 1)
      {
        putchar(' ');
      }
      else if (blanks_to_replace > 1)
      {
        putchar('\t');
      }
      s = next_s;
    }
  }
}
