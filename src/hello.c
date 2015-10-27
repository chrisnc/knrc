#include <stdio.h>

// Exercise 1-1. page 8
int main(void)
{
  printf("hello, world\n");
}

/*
 * Exercise 1-2. page 8
 * When the format string contains \c where c is not among {n, t, b, ", \} the
 * compiler emits a -Wunknown-escape-sequence warning.
 * The backslash is ignored, and the character following it is printed normally.
 */

/*
// commented out since we compile with -Werror
void unknown_escape_sequence(void)
{
  printf("unknown escape sequence: \c!\n");
}
*/
