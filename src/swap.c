#include <stdio.h>

// Exercise 4-14. page 91
#define swap(t, x, y)                                                          \
  do                                                                           \
  {                                                                            \
    t swap_tmp = x;                                                            \
    x = y;                                                                     \
    y = swap_tmp;                                                              \
  } while (0)


#ifdef _MSC_VER
#undef swap

// MSVC warning C4127 is for "conditional expression is constant",
// which prevents the do {} while (0) multiline macro idiom,
// so we disable it for just this case.
#define swap(t, x, y)                                                          \
  do                                                                           \
  {                                                                            \
    t swap_tmp = x;                                                            \
    x = y;                                                                     \
    y = swap_tmp;                                                              \
    __pragma(warning(push)) __pragma(warning(disable : 4127))                  \
  } while (0) __pragma(warning(pop))

#endif // _MSC_VER

int main(void)
{
  int x = 100;
  int y = 200;
  printf("x = %d, y = %d\n", x, y);
  swap(int, x, y);
  printf("x = %d, y = %d\n", x, y);
  return 0;
}
