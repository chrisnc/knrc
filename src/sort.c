#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getline.h"

// sorting example with numerical or lexicographical sort, page 119

#define MAXLINES 5000
#define MAXLEN 5000

static int numcmp(const void *a, const void *b)
{
  const char *const *s = a;
  const char *const *t = b;
  return atoi(*s) - atoi(*t);
}

static int strcmp_void(const void *a, const void *b)
{
  const char *const *s = a;
  const char *const *t = b;
  return strcmp(*s, *t);
}

int main(int argc, char **argv)
{
  bool numeric = false;

  if (argc > 1 && strcmp(argv[1], "-n") == 0)
  {
    numeric = true;
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

  qsort((void **)lineptr, i, sizeof(lineptr[0]),
        (numeric ? numcmp : strcmp_void));

  for (size_t j = 0; j < i; ++j)
  {
    printf("%s", lineptr[j]);
    free(lineptr[j]);
  }
  free(lineptr);
  return EXIT_SUCCESS;
}
