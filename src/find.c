#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "getline.h"

#define MAXLINE 1000

// simple grep example, using argv[1] as search string, page 116
int main(int argc, char **argv)
{
  char line[MAXLINE];
  int found = 0;

  if (argc != 2)
  {
    printf("Usage: find pattern\n");
    return EXIT_FAILURE;
  }

  while (my_getline(line, MAXLINE) > 0)
  {
    if (strstr(line, argv[1]) != NULL)
    {
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
