#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h> // for strcasecmp

#include "getline.h"

// sorting example with numerical or lexicographical sort, page 119

// Exercise 5-14, page 121
// modified to support reverse sorting

// Exercise 5-15, page 121
// modified to support case-insensitive sorting

// Exercise 5-16, page 121
// modified to support directory sort order

#define MAXLINES 5000
#define MAXLEN 5000

static bool reverse = false;
static bool numeric = false;
static bool directory = false;
static bool case_insensitive = false;

static const char *dirskip(const char *s)
{
  while (*s && !isdigit(*s) && !isalpha(*s) && !isspace(*s))
  {
    ++s;
  }
  return s;
}

static int cmp(const void *a, const void *b)
{
  const char *const *sp = a;
  const char *const *tp = b;
  const char *s = *sp;
  const char *t = *tp;

  int x;
  if (numeric)
  {
    x = atoi(s) - atoi(t);
  }
  else
  {
    if (directory)
    {
      s = dirskip(s);
      t = dirskip(t);
    }
    while ((case_insensitive ? tolower(*s) == tolower(*t) : *s == *t) && *s)
    {
      if (directory)
      {
        s = dirskip(s);
        t = dirskip(t);
      }
      ++s;
      ++t;
    }
    x = case_insensitive ? tolower(*s) - tolower(*t) : *s - *t;
  }

  if (reverse)
  {
    x = -x;
  }
  return x;
}

int main(int argc, char **argv)
{
  while (--argc > 0 && (*++argv)[0] == '-')
  {
    char c;
    while ((c = *++argv[0]))
    {
      switch (c)
      {
      case 'n':
        numeric = true;
        break;
      case 'r':
        reverse = true;
        break;
      case 'd':
        directory = true;
        break;
      case 'f':
        case_insensitive = true;
        break;
      default:
        fprintf(stderr, "sort: illegal option %c\n", c);
        return EXIT_FAILURE;
      }
    }
  }

  char **lineptr = calloc(MAXLINES, sizeof(*lineptr));

  char line[MAXLEN];
  size_t len;
  size_t i = 0;
  while ((len = my_getline(line, MAXLEN)) > 0)
  {
    if (line[len - 1] != '\n')
    {
      fprintf(stderr, "error: line too large\n");
      line[len - 1] = '\n';
    }
    if (i < MAXLINES)
    {
      lineptr[i] = realloc(lineptr[i], len + 1);
      memcpy(lineptr[i], line, len + 1);
      ++i;
    }
    else
    {
      fprintf(stderr, "error: too many lines\n");
      break;
    }
  }

  qsort((void **)lineptr, i, sizeof(lineptr[0]), cmp);

  for (size_t j = 0; j < i; ++j)
  {
    printf("%s", lineptr[j]);
    free(lineptr[j]);
  }
  free(lineptr);
  return EXIT_SUCCESS;
}
