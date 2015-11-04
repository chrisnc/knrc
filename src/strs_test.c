#include <stdio.h>

#include "strs.h"

int main(void)
{
  char s[] = "hello, world";
  char c = 'o';
  char e[] = "ld";
  char t[] = "re";

  printf("squeeze(\"%s\", \'%c\') = \"", s, c);
  squeeze(s, c);
  printf("%s\"\n", s);

  printf("squeeze_str(\"%s\", \"%s\") = \"", s, e);
  squeeze_str(s, e);
  printf("%s\"\n", s);

  printf("any(\"%s\", \"%s\") = %d\n", s, t, any(s, t));
}
