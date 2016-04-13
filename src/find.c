#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getline.h"

#define MAXLINE 1000

// find: print lines that match pattern from 1st arg, page 116
// with -x and -n flags, page 117
int main(int argc, char **argv)
{
  char line[MAXLINE];
  size_t lineno = 0;
  bool except = false;
  bool number = false;
  int found = 0;
  int c;

  while (--argc > 0 && (*++argv)[0] == '-')
  {
    while ((c = *++argv[0]))
    {
      switch (c)
      {
      case 'x':
        except = true;
        break;
      case 'n':
        number = true;
        break;
      default:
        printf("find: illegal option %c\n", c);
        argc = 0;
        found = -1;
        break;
      }
    }
  }

  if (argc != 1)
  {
    printf("Usage: find -x -n pattern\n");
    return EXIT_FAILURE;
  }

  while (my_getline(line, MAXLINE) > 0)
  {
    ++lineno;
    if ((strstr(line, *argv) != NULL) != except)
    {
      if (number)
      {
        printf("%zu:", lineno);
      }
      printf("%s", line);
      ++found;
    }
  }

  if (found == 0)
  {
    return EXIT_FAILURE;
  }

  printf("found %d occurrences\n", found);

  return EXIT_SUCCESS;
}
