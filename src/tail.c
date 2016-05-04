#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getline.h"

#define MAXLEN 5000

// Exercise 5-13, page 118

int main(int argc, char **argv)
{
  size_t n = 10;

  if (argc >= 2 && argv[1][0] == '-')
  {
    if (sscanf(argv[1] + 1, "%zu", &n) != 1)
    {
      fprintf(stderr, "tail: illegal option %s\n", argv[1]);
      return EXIT_FAILURE;
    }
  }

  char **lineptr = calloc(n, sizeof(*lineptr));

  char line[MAXLEN];
  size_t len;
  size_t i = 0;
  while ((len = my_getline(line, MAXLEN)) > 0)
  {
    if (line[len - 1] != '\n')
    {
      fprintf(stderr, "error: line too large\n");
    }
    if (i < n)
    {
      lineptr[i] = realloc(lineptr[i], len + 1);
      memcpy(lineptr[i], line, len + 1);
      i = (i + 1) % n;
    }
  }
  for (size_t j = 0; j < n; ++j)
  {
    if (lineptr[i])
    {
      printf("%s", lineptr[i]);
      free(lineptr[i]);
    }
    i = (i + 1) % n;
  }
  free(lineptr);
}
