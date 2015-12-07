#include <stdio.h>
#include <string.h>

#include "getline.h"
#include "heap.h"

// line sorting example from page 107-110

void writelines(char **lineptr, size_t nlines);
void sortlines(char **v, size_t n);

#define MAXLINES 5000 // max # lines to be sorted
#define MAXLEN 1000   // max length of any input line

static int strcmp_void(const void *a, const void *b)
{
  return strcmp(*(const char *const *)a, *(const char *const *)b);
}

HEAP_TEMPLATE_CMP(const char *, line, strcmp_void)

int main(void)
{
  // Exercise 5-7. page 110
  // When using a fixed buffer for the lines instead of malloc,
  // the program takes roughly the same time to run.

  // Need to use one extra line to read into to determine if there is input
  // beyond MAXLINES.
  char lines[MAXLINES + 1][MAXLEN];
  size_t nlines = 0;
  struct heap lineptrs;
  heap_init_line(&lineptrs);
  size_t len;
  while ((len = my_getline(lines[nlines], MAXLEN)) > 0)
  {
    if (nlines >= MAXLINES || lines[nlines][len - 1] != '\n')
    {
      fprintf(stderr, "error: input too big to sort\n");
      return 1;
    }
    heap_insert_line(&lineptrs, lines[nlines++]);
  }

  while (heap_size(&lineptrs) > 0)
  {
    printf("%s", *heap_min_line(&lineptrs));
    heap_pop_min(&lineptrs);
  }

  heap_deinit(&lineptrs);

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
  for (; nlines > 0; --nlines)
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
