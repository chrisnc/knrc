#include <stdio.h>

// Exercise 4-14. page 91
#define swap(t, x, y)                                                          \
  do                                                                           \
  {                                                                            \
    t swap_tmp = x;                                                            \
    x = y;                                                                     \
    y = swap_tmp;                                                              \
  } while (0)

// MSVC does not like this idiom because the "conditional expression is
// constant", so we write a special version that disables this warning.
#ifdef _MSC_VER
#undef swap
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
