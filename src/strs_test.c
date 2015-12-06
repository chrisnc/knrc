#ifdef _MSC_VER
// allow strncpy and friends for testing
#define _CRT_SECURE_NO_WARNINGS
#endif // _MSC_VER

#include "arc4random.h"
#include "strs.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

// make a random string with a random length inside
// the length n buffer s
// the random length will be in the range [0,n)
static void make_random_string(char *s, size_t n)
{
  size_t len = arc4random() % n;
  for (size_t i = 0; i < n; ++i)
  {
    if (i < len)
    {
      s[i] = (char)((arc4random() % 96) + ' ');
    }
    else
    {
      s[i] = '\0';
    }
  }
}

static void show_string_buf(const char *s, size_t n)
{
  printf("string: \"%s\" ", s);
  printf("extra: ");
  for (size_t i = strlen(s); i < n; ++i)
  {
    putchar(s[i] ? s[i] : '0');
  }
  putchar('\n');
}

int main(void)
{
  char s[] = "hello, world";
  char c = 'o';
  char e[] = "ld";
  char t[] = "re";
  char w[] = "hewr wat wr";
  char q[] = "wr";

  printf("squeeze(\"%s\", \'%c\') -> \"", s, c);
  squeeze(s, c);
  printf("%s\"\n", s);

  printf("squeeze_str(\"%s\", \"%s\") -> \"", s, e);
  squeeze_str(s, e);
  printf("%s\"\n", s);

  printf("any(\"%s\", \"%s\") -> %d\n", s, t, any(s, t));

  printf("strrindex(\"%s\", \"%s\") -> %d\n", w, q, strrindex(w, q));

  char b[100] = {0};
  strcat_ptr(b, s);
  strcat_ptr(b, e);
  strcat_ptr(b, t);
  strcat_ptr(b, w);
  printf("strcat result: %s\n", b);

  printf("strend(\"%s\", \"%s\") -> %d\n", b, w, strend(b, w));
  printf("strend(\"%s\", \"%s\") -> %d\n", b, e, strend(b, e));

  char source[60];
  char target1[60];
  char target2[60];
  for (size_t i = 0; i < 100000; ++i)
  {
    make_random_string(source, sizeof(source));
    make_random_string(target1, sizeof(target1));
    memcpy(target2, target1, sizeof(target1));
    size_t n = arc4random() % (sizeof(source) + 1);

    const char *p1 = strncpy(target1, source, n);
    const char *p2 = my_strncpy(target2, source, n);

    if (p1 != target1)
    {
      printf("strncpy did not return its input pointer\n");
    }
    if (p2 != target2)
    {
      printf("my_strncpy did not return its input pointer\n");
    }
    if (memcmp(target1, target2, sizeof(target1)) != 0)
    {
      printf("strncpy test failed\n");
      printf("source:\n");
      show_string_buf(source, sizeof(source));
      printf("n = %zu\n", n);
      printf("strncpy output:\n");
      show_string_buf(target1, sizeof(target1));
      printf("my_strncpy output:\n");
      show_string_buf(target2, sizeof(target2));
    }
  }

  for (size_t i = 0; i < 100000; ++i)
  {
    make_random_string(source, sizeof(source));
    make_random_string(target1, sizeof(target1));
    memcpy(target2, target1, sizeof(target1));

    size_t n = arc4random() % (sizeof(source) - strlen(target1));

    const char *p1 = strncat(target1, source, n);
    const char *p2 = my_strncat(target2, source, n);

    if (p1 != target1)
    {
      printf("strncat did not return its input pointer\n");
    }
    if (p2 != target2)
    {
      printf("my_strncat did not return its input pointer\n");
    }
    if (memcmp(target1, target2, sizeof(target1)) != 0)
    {
      printf("strncat test failed\n");
      printf("source:\n");
      show_string_buf(source, sizeof(source));
      printf("n = %zu\n", n);
      printf("strncat output:\n");
      show_string_buf(target1, sizeof(target1));
      printf("my_strncat output:\n");
      show_string_buf(target2, sizeof(target2));
    }
  }

  char cmps1[60];
  char cmps2[60];
  for (size_t i = 0; i < 100000; ++i)
  {
    make_random_string(cmps1, sizeof(cmps1));
    make_random_string(cmps2, sizeof(cmps2));

    size_t n = arc4random() % sizeof(cmps1);

    int cmp1 = strncmp(cmps1, cmps2, n);
    int cmp2 = my_strncmp(cmps1, cmps2, n);

#ifdef _MSC_VER
    // on Windows, strncmp only returns -1, 0, or 1.
    if (cmp2 < 0)
    {
      cmp2 = -1;
    }
    else if (cmp2 > 0)
    {
      cmp2 = 1;
    }
#endif

    if (cmp1 != cmp2)
    {
      printf("strncmp test failed\n");
      printf("s:\n");
      show_string_buf(cmps1, sizeof(cmps1));
      printf("t:\n");
      show_string_buf(cmps2, sizeof(cmps2));
      printf("n = %zu\n", n);
      printf("strncmp output: %d\n", cmp1);
      printf("my_strncmp output: %d\n", cmp2);
    }
  }
}
