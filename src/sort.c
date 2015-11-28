#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "getline.h"

// line sorting example from page 107-110

void writelines(char **lineptr, size_t nlines);
void sortlines(char **v, size_t n);

#define MAXLINES 5000 // max # lines to be sorted
#define MAXLEN 1000   // max lenghth of any input line

int main(void)
{
  char line[MAXLEN];
  char *lines[MAXLINES];
  size_t nlines = 0;
  size_t len;
  while ((len = my_getline(line, MAXLEN)) > 0)
  {
    if (nlines >= MAXLINES || (lines[nlines] = malloc(len + 1)) == NULL)
    {
      fprintf(stderr, "error: input too big to sort\n");
      return 1;
    }
    strcpy(lines[nlines++], line);
  }
  sortlines(lines, nlines);
  writelines(lines, nlines);
  for (size_t i = 0; i < nlines; ++i)
  {
    free(lines[i]);
  }
  return 0;
}

// writelines: write output lines
// NOTE: It would be nice to write this function as:
// static void writelines(const char *const *lineptr, size_t nlines);
// as it does not modify the characters or the pointers to the characters,
// but this doesn't work very well in C, because the original data
// is an array of char *, so passing it in to something that accepts
// const char * const * yields a warning:
// -Wincompatible-pointer-types-discards-qualifiers
//
// This link explains the issue well: http://c-faq.com/ansi/constmismatch.html
// Surprisingly, this would work in C++. From the link:
// "(C++ has more complicated rules for assigning const-qualified pointers
// which let you make more kinds of assignments without incurring warnings, but
// still protect against inadvertent attempts to modify const values. C++ would
// still not allow assigning a char ** to a const char **, but it would let you
// get away with assigning a char ** to a const char * const *.)
//
// In C, if you must assign or pass pointers which have qualifier mismatches at
// other than the first level of indirection, you must use explicit casts
// (e.g. (const char **) in this case), although as always, the need for such a
// cast may indicate a deeper problem which the cast doesn't really fix."
void writelines(char **lineptr, size_t nlines)
{
  while (nlines-- > 0)
  {
    printf("%s", *lineptr++);
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

