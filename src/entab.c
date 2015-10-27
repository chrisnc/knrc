#include <stdio.h>
#include <stdlib.h>

// Exercise 1-21. page 34

#define TABSTOP 8

int main(void)
{
  size_t n = 0;
  char *line = NULL;
  ssize_t len;

  while ((len = getline(&line, &n, stdin)) != -1)
  {
    for (int s = 0; s < len;)
    {
      // find the index of the last character before the next tab stop
      int e;
      for (e = s; e < s + TABSTOP - 1; ++e)
      {
        if (line[e] == '\t')
        {
          break;
        }
      }
      int next_s = e + 1;
      int blanks_to_replace = 0;
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
      for (int i = s; i <= e; ++i)
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
  free(line);
}
