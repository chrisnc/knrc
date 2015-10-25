#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// Exercise 3-3.

// longest range is a-z which expands 3 characters into 26
#define EXPAND_FACTOR 9

void expand(char *d, const char *s)
{
  char begin;
  while ((begin = *d++ = *s++))
  {
    // '-' can't begin a range, and if the next character isn't '-' we aren't
    // in a range
    if (begin == '-' || *s != '-')
    {
      continue;
    }
    char end = *(s + 1); // look at the character following '-'
    // check that begin and end form a valid range
    if (begin <= end &&
        ((islower(begin) && islower(end)) || (isupper(begin) && isupper(end)) ||
         (isdigit(begin) && isdigit(end))))
    {
      // write the character range to the output
      // (not including begin because it was already emitted)
      for (char c = begin + 1; c <= end; ++c)
      {
        *d++ = c;
      }
      // advance s past the '-' and end if they completed a range
      s += 2;
    }
  }
}

int main(void)
{
  size_t n = 0;
  char *line = NULL;
  ssize_t len;
  char *expanded = NULL;

  while ((len = getline(&line, &n, stdin)) != -1)
  {
    line[len - 1] = '\0'; // delete newline
    expanded = realloc(expanded, len * EXPAND_FACTOR + 1);
    expand(expanded, line);
    printf("%s\n", expanded);
  }
  free(line);
  free(expanded);
}
