#include <stdio.h>

#include "strs.h"

// squeeze: delete all c from s
void squeeze(char s[], int c)
{
  int i, j;
  for (i = j = 0; s[i] != '\0'; ++i)
  {
    if (s[i] != c)
    {
      s[j++] = s[i];
    }
  }
  s[j] = '\0';
}

// strcat: concatenate t to end of s; s must be big enough
void my_strcat(char s[], char t[])
{
  int i, j;
  i = j = 0;
  while (s[i] != '\0') // find end of s
  {
    ++i;
  }
  while ((s[i++] = t[j++]) != '\0') // copy t
  {
  }
}

// Exercise 2-4. page 48
void squeeze_str(char s[], char e[])
{
  int i, j;
  for (i = j = 0; s[i] != '\0'; ++i)
  {
    int keep = 1;
    for (int k = 0; e[k] != '\0'; ++k)
    {
      if (s[i] == e[k])
      {
        keep = 0;
        break;
      }
    }
    if (keep)
    {
      s[j++] = s[i];
    }
  }
  s[j] = '\0';
}

// Exercise 2-5. page 48
int any(const char s[], const char t[])
{
  for (int i = 0; s[i] != '\0'; ++i)
  {
    for (int j = 0; t[j] != '\0'; ++j)
    {
      if (s[i] == t[j])
      {
        return i;
      }
    }
  }
  return -1;
}

// Exercise 4-1. page 71
// strrindex returns the position of the rightmost occurrence of t in s, or -1
// if there is none. This implementation is a trivial modification of strindex
// to just continue searching even after finding a match on the left, and keeps
// track of the rightmost one found. This could be improved by starting from
// the end of the string and returning the first match.
int strrindex(const char *s, const char *t)
{
  int i_max = -1;

  for (int i = 0; s[i] != '\0'; ++i)
  {
    int j, k;
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; ++j, ++k)
    {
    }
    if (k > 0 && t[k] == '\0')
    {
      i_max = i;
    }
  }
  return i_max;
}
