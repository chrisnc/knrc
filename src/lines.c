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

// Exercise 1-16. page 30
// getline: read a line into s, return length
// modified to return the actual length of the line, even if it was longer than
// lim-1
int my_getline_ex_1_16(char s[], int lim)
{
  int c = 0, i;
  for (i = 0; c != '\n' && (c = getchar()) != EOF; ++i)
  {
    if (i < lim - 1)
    {
      s[i] = (char) c;
    }
  }
  if (i < lim)
  {
    s[i] = '\0';
  }
  else if (lim > 0)
  {
    s[lim - 1] = '\0';
  }
  return i;
}

// copy: copy 'from' into 'to'; assume to is big enough
void copy(char to[], char from[])
{
  int i = 0;
  while ((to[i] = from[i]) != '\0')
  {
    ++i;
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
    size_t i;
    /*
     * Start from the end of the line and delete whitespace. We also delete the
     * newline here to avoid the bookkeeping of starting at len - 2. This would
     * incur a special case for the line "\n" where len - 2 overflows.
     */
    for (i = len - 1; line[i] == ' ' || line[i] == '\t' || line[i] == '\n'; --i)
    {
      line[i] = '\0';
      if (i == 0)
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
void reverse(char s[], size_t len)
{
  size_t half_len = len / 2;
  for (size_t i = 0; i < half_len; ++i)
  {
    size_t j = len - i - 1;
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
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
