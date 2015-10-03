#include <stdio.h>

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

// Exercise 2-4.
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

// Exercise 2-5.
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

int main(void)
{
  char s[] = "hello, world";
  char c = 'o';
  char e[] = "ld";

  printf("squeeze(\"%s\", \'%c\') = \"", s, c);
  squeeze(s, c);
  printf("%s\"\n", s);

  printf("squeeze_str(\"%s\", \"%s\") = \"", s, e);
  squeeze_str(s, e);
  printf("%s\"\n", s);

  char t[] = "re";
  printf("any(\"%s\", \"%s\") = %d\n", s, t, any(s, t));
}
