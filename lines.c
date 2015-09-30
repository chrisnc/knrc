#include <stdio.h>

#define MAXLINE 1000 // maximum input line length

int my_getline(char line[], int maxline);

void copy(char to[], char from[]);

// print the longest input line
void get_max_line(void)
{
  int len;               // current line length
  int max;               // maximum length seen so far
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
    printf("the longest line was %d characters\n", max);
    printf("%s", longest);
  }
}

// getline: read a line into s, return length
// Exercise 1-16. modified to return the actual length of the line, even if it
// was longer than lim-1
int my_getline(char s[], int lim)
{
  int c = 0, i;

  for (i = 0; c != '\n' && (c = getchar()) != EOF; ++i)
  {
    if (i < lim - 1)
    {
      s[i] = c;
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

// Exercise 1-17.
void print_over_80_chars(void)
{

  int len;
  char line[MAXLINE];

  while ((len = my_getline(line, MAXLINE)) > 0)
  {
    if (len > 80)
    {
      printf("%s", line);
    }
  }
}

// Exercise 1-18.
void delete_blanks(void)
{
  int len;
  char line[MAXLINE];

  while ((len = my_getline(line, MAXLINE)) > 0)
  {
    int i;
    for (i = len - 2; i >= 0 && (line[i] == ' ' || line[i] == '\t'); --i)
    {
      line[i] = '\0';
    }
    if (i == -1) // all characters except the newline were removed, so delete
                 // this line
    {
      continue;
    }
    /*
     * re-set the newline after deleting characters
     * if no characters were deleted, i + 1 == len - 1, and line[len - 1] is
     * already the newline
     */
    line[i + 1] = '\n';
    printf("%s", line);
  }
}

// Exercise 1-19.
void reverse(char s[], int len)
{
  int half_len = len / 2;
  for (int i = 0; i < half_len; ++i)
  {
    int j = len - i - 1;
    char tmp = s[i];
    s[i] = s[j];
    s[j] = tmp;
  }
}

void reverse_lines(void)
{
  int len;
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
