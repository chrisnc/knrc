#include <stdio.h>

// strcpy examples, page 105

void strcpy_arr(char *s, const char *t);
void strcpy_ptr1(char *s, const char *t);
void strcpy_ptr2(char *s, const char *t);
void strcpy_ptr3(char *s, const char *t);

int main(void)
{
  char s[100];

  struct
  {
    void (*f)(char *, const char *);
    const char *s;
  } x[4] = {
      {strcpy_arr, "first, strcpy_arr"},
      {strcpy_ptr1, "then, strcpy_ptr1"},
      {strcpy_ptr2, "next, strcpy_ptr2"},
      {strcpy_ptr3, "finally, strcpy_ptr3"},
  };

  for (size_t i = 0; i < 4; ++i)
  {
    x[i].f(s, x[i].s);
    printf("%s\n", s);
  }
}

// strcpy: copy t to s; array subscript version
void strcpy_arr(char *s, const char *t)
{
  int i = 0;
  while ((s[i] = t[i]) != '\0')
  {
    ++i;
  }
}

// strcpy: copy t to s; pointer version 1
void strcpy_ptr1(char *s, const char *t)
{
  while ((*s = *t) != '\0')
  {
    ++s;
    ++t;
  }
}

// strcpy: copy t to s; pointer version 2
void strcpy_ptr2(char *s, const char *t)
{
  while ((*s++ = *t++) != '\0')
  {
  }
}

/*
 * MSVC doesn't like this idiom, even with the extra parens.
 * clang and gcc will emit -Wparentheses unless you use extra
 * parentheses around the assignment
 */
#ifdef _MSC_VER
#pragma warning(disable : 4706)
#endif // _MSC_VER

// strcpy: copy t to s; pointer version 3
void strcpy_ptr3(char *s, const char *t)
{
  while ((*s++ = *t++))
  {
  }
}
