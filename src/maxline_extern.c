#include <stdio.h>

#define MAXLINE 1000 // maximum input line size

int max; // maximum length seen so far
char line[MAXLINE]; // current input line
char longest[MAXLINE]; // longest line saved here

int getline_extern(void);
void copy_extern(void);

// print longest input line; specialized version
int main(void)
{
  int len;
  extern int max;
  extern char longest[];

  max = 0;
  while ((len = getline_extern()) > 0)
  {
    if (len > max) {
      max = len;
      copy_extern();
    }
  }
  if (max > 0) // there was a line
  {
    printf("%s", longest);
  }
  return 0;
}

// getline: specialized version
int getline_extern(void)
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
void copy_extern(void)
{
  extern char line[], longest[];

  int i = 0;
  while ((longest[i] = line[i]) != '\0')
  {
    ++i;
  }
}
