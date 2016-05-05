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

#define MAXLINES 5000
#define MAXLEN 5000

static int numcmp(const void *a, const void *b)
{
  const char *const *const s = a;
  const char *const *const t = b;
  return atoi(*s) - atoi(*t);
}

static int strcmp_void(const void *a, const void *b)
{
  const char *const *const s = a;
  const char *const *const t = b;
  return strcmp(*s, *t);
}

static int strcasecmp_void(const void *a, const void *b)
{
  const char *const *const s = a;
  const char *const *const t = b;
  return strcasecmp(*s, *t);
}

static void reverse_lines(char **lineptr, size_t nlines)
{
  for (size_t i = 0; i < nlines / 2; ++i)
  {
    size_t j = nlines - i - 1;
    char *tmp = lineptr[i];
    lineptr[i] = lineptr[j];
    lineptr[j] = tmp;
  }
}

int main(int argc, char **argv)
{
  bool reverse = false;

  int (*cmp)(const void *, const void *) = strcmp_void;

  while (--argc > 0 && (*++argv)[0] == '-')
  {
    char c;
    while ((c = *++argv[0]))
    {
      switch (c)
      {
      case 'n':
        cmp = numcmp;
        break;
      case 'r':
        reverse = true;
        break;
      case 'f':
        cmp = strcasecmp_void;
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

  if (reverse)
  {
    reverse_lines(lineptr, i);
  }

  for (size_t j = 0; j < i; ++j)
  {
    printf("%s", lineptr[j]);
    free(lineptr[j]);
  }
  free(lineptr);
  return EXIT_SUCCESS;
}
