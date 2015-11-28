#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "getline.h"

// line sorting example from page 107-110

#define MAXLINES 5000 // max # lines to be sorted

int readlines(char **lines, size_t maxlines);
void writelines(char **lines, size_t nlines);
void sortlines(char **lines, size_t nlines);

// sort input lines
int main(void)
{
  char *lines[MAXLINES];
  int n; // number of input lines read
  if ((n = readlines(lines, MAXLINES)) > 0)
  {
    sortlines(lines, (size_t)n);
    writelines(lines, (size_t)n);
    for (size_t i = 0; i < (size_t)n; ++i)
    {
      free(lines[i]);
    }
    return 0;
  }
  else
  {
    fprintf(stderr, "error: input too big to sort\n");
    return 1;
  }
}

#define MAXLEN 1000 // max lenghth of any input line

// readlines: read input lines
int readlines(char *lineptr[], size_t maxlines)
{
  char *p, line[MAXLEN];

  size_t nlines = 0;
  size_t len;
  while ((len = my_getline(line, MAXLEN)) > 0)
  {
    if (nlines >= maxlines || (p = malloc(len)) == NULL)
    {
      return -1;
    }
    else
    {
      line[len - 1] = '\0'; // delete newline
      strcpy(p, line);
      lineptr[nlines++] = p;
    }
  }
  return (int)nlines;
}

// writelines: write output lines
void writelines(char **lineptr, size_t nlines)
{
  while (nlines-- > 0)
  {
    printf("%s\n", *lineptr++);
  }
}

// swap: interchange v[i] and v[j]
static void swap(char **v, size_t i, size_t j)
{
  char *temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

void sortlines(char **v, size_t n)
{
  // do nothing if array contains fewer than two elements
  if (n < 2)
  {
    return;
  }

  swap(v, 0, n / 2); // move partition elem
  size_t last = 0;   // to v[0]
  for (size_t i = 0; i < n; ++i)
  {
    if (strcmp(v[i], v[0]) < 0)
    {
      swap(v, ++last, i);
    }
  }
  swap(v, 0, last); // restore partition elem

  sortlines(v, last);
  sortlines(v + last + 1, n - last - 1);
}
