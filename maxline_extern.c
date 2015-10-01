#include <stdio.h>

#define MAXLINE 1000 // maximum input line size

int max; // maximum length seen so far
char line[MAXLINE]; // current input line
char longest[MAXLINE]; // longest line saved here

int my_getline(void);
void copy(void);

// print longest input line; specialized version
int main(void)
{
  int len;
  extern int max;
  extern char longest[];

  max = 0;
  while ((len = my_getline()) > 0)
  {
    if (len > max) {
      max = len;
      copy();
    }
  }
  if (max > 0) // there was a line
  {
    printf("%s", longest);
  }
  return 0;
}

// my_getline: specialized version
int my_getline(void)
{
  int c = 0, i;
  extern char line[];
  for (i = 0; i < MAXLINE - 1 && c != '\n' && (c = getchar()) != EOF; ++i)
  {
    line[i] = c;
  }
  line[i] = '\0';
  return i;
}

// copy: specialized version
void copy(void)
{
  extern char line[], longest[];

  int i = 0;
  while ((longest[i] = line[i]) != '\0')
  {
    ++i;
  }
}
