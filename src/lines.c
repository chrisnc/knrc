#include <stdio.h>

#include "getline.h"

#include "lines.h"

#define MAXLINE 1000 // maximum input line length

void copy(char to[], char from[]);

// print the longest input line
void get_max_line(void)
{
  size_t len;            // current line length
  size_t max;            // maximum length seen so far
  char line[MAXLINE];    // current input line
  char longest[MAXLINE]; // longest line saved here

  max = 0;
  while ((len = my_getline(line, MAXLINE)) > 0)
  {
    if (len > max)
    {
      max = len;
      copy(longest, line);
    }
  }
  if (max > 0) // there was a line
  {
    printf("the longest line was %zu characters\n", max);
    printf("%s", longest);
  }
}

// Exercise 5-6. page 107
// modified these functions to use pointer arithmetic

// Exercise 1-16. page 30
// getline: read a line into s, return length
// modified to return the actual length of the line, even if it was longer than
// lim-1
size_t my_getline_ex_1_16(char *s, size_t lim)
{
  int c = 0;
  size_t n = 0;
  for (; c != '\n' && (c = getchar()) != EOF; ++n)
  {
    if (n < lim - 1)
    {
      *s++ = (char)c;
    }
  }
  if (lim > 0)
  {
    *s = '\0';
  }
  return n;
}

// copy: copy 'from' into 'to'; assume to is big enough
void copy(char *to, char *from)
{
  while ((*to++ = *from++) != '\0')
  {
  }
}

// Exercise 1-17. page 31
void print_over_80_chars(void)
{
  size_t len;
  char line[MAXLINE];

  while ((len = my_getline(line, MAXLINE)) > 0)
  {
    if (len > 80)
    {
      printf("%s", line);
    }
  }
}

// Exercise 1-18. page 31
void delete_blanks(void)
{
  size_t len;
  char line[MAXLINE];

  while ((len = my_getline(line, MAXLINE)) > 0)
  {
    int line_is_blank = 0;
    /*
     * Start from the end of the line and delete whitespace. We also delete the
     * newline here to avoid the bookkeeping of starting at len - 2. This would
     * incur a special case for the line "\n" where len - 2 overflows.
     */
    for (char *e = line + len - 1; *e == ' ' || *e == '\t' || *e == '\n'; --e)
    {
      *e = '\0';
      if (e == line)
      {
        line_is_blank = 1;
        break;
      }
    }
    if (!line_is_blank)
    {
      // we deleted the newline before, so re-add it in printf
      printf("%s\n", line);
    }
  }
}

// Exercise 1-19. page 31
void reverse(char *s, size_t len)
{
  char *t = s + len;
  while (s < t)
  {
    char tmp = *s;
    *s++ = *--t;
    *t = tmp;
  }
}

void reverse_lines(void)
{
  size_t len;
  char line[MAXLINE];

  while ((len = my_getline(line, MAXLINE)) > 0)
  {
    reverse(line, len - 1); // leave the '\n' in the last position
    printf("%s", line);
  }
}

int main(void)
{
  // get_max_line();
  // print_over_80_chars();
  // delete_blanks();
  reverse_lines();
}
