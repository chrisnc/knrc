#include <stdio.h>

// Exercise 1-22. page 34

#define LINE_LENGTH 80
#define TAB_STOP 8

int main(void)
{
  int current_line_length = 0;
  int trailing_blanks = 0;

  int c;
  while ((c = getchar()) != EOF)
  {
    switch (c)
    {
    case ' ':
      ++trailing_blanks;
      break;
    case '\t':
      trailing_blanks += TAB_STOP - (current_line_length % TAB_STOP);
      break;
    case '\n':
      trailing_blanks = 0;
      current_line_length = 0;
      putchar('\n');
      break;
    default:
      if (current_line_length + trailing_blanks + 1 >= LINE_LENGTH)
      {
        putchar('\n');
        putchar(c);
        current_line_length = 1;
        trailing_blanks = 0;
      }
      else
      {
        for (; trailing_blanks > 0; --trailing_blanks)
        {
          putchar(' ');
          ++current_line_length;
        }
        putchar(c);
        ++current_line_length;
      }
    }
  }
}
