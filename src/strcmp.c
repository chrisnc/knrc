#include <stdio.h>

int strcmp_arr(const char *s, const char *t);
int strcmp_ptr(const char *s, const char *t);

int main(void)
{
  char s[] = "what's up";
  char t[] = "what's this then";

  int (*f[2])(const char *, const char *) = {strcmp_arr, strcmp_ptr};

  for (size_t i = 0; i < 2; ++i)
  {
    printf("strcmp(\"%s\", \"%s\") -> %d\n", s, t, f[i](s, t));
  }
}

// strcmp: return < 0 if s < t, 0 if s == t, > 0 if s > t
int strcmp_arr(const char *s, const char *t)
{
  int i;
  for (i = 0; s[i] == t[i]; ++i)
  {
    if (s[i] == '\0')
    {
      return 0;
    }
  }
  return s[i] - t[i];
}

// strcmp: return < 0 if s < t, 0 if s == t, > 0 if s > t
int strcmp_ptr(const char *s, const char *t)
{
  for (; *s == *t; s++, t++)
  {
    if (*s == '\0')
    {
      return 0;
    }
  }
  return *s - *t;
}
