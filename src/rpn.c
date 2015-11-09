#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h> // for atof
#include <string.h>

#include "getline.h"
#include "vector.h"

#ifdef _MSC_VER
#define strtok_r strtok_s
#endif

// Exercise 4-10. page 79
// Reverse Polish Notation calculator with getline

#define NUMBER '0'   // signal that a number was found
#define ALPHA_OP 'a' // signal that an alphabetic operator was found

void runop(const char *s, double *vars, double ans);
void push(double);
double pop(void);
size_t size(void);
void init_stack(void);
void destroy_stack(void);

#define MAXLINE 1024

int main(void)
{
  init_stack();
  char line[MAXLINE];

  double ans = NAN;
  double vars[26];
  for (size_t i = 0; i < 26; ++i)
  {
    vars[i] = NAN;
  }

  const char delims[] = " \n\t";

  while (my_getline(line, MAXLINE) > 0)
  {
    char *save = NULL;
    for (const char *s = strtok_r(line, delims, &save); s;
         s = strtok_r(NULL, delims, &save))
    {
      runop(s, vars, ans);
    }
    ans = pop();
    printf("\t%.8g\n", ans);
  }
  destroy_stack();
  return 0;
}

void runop(const char *s, double *vars, double ans)
{
  int type = s[0];
  if (isdigit(s[0]) || s[0] == '.' || (s[0] == '-' && isdigit(s[1])))
  {
    type = NUMBER;
  }
  if (isalpha(s[0]) || s[0] == '=')
  {
    type = ALPHA_OP;
  }

  double x, y;
  switch (type)
  {
  case NUMBER:
    push(atof(s));
    break;
  case '+':
    push(pop() + pop());
    break;
  case '*':
    push(pop() * pop());
    break;
  case '-':
    y = pop();
    push(pop() - y);
    break;
  case '/':
    y = pop();
    if (y != 0.0)
    {
      push(pop() / y);
    }
    else
    {
      printf("error: zero divisor\n");
    }
    break;
  case '%':
    y = pop();
    if (y != 0.0)
    {
      x = pop();
      push((int)x % (int)y);
    }
    else
    {
      printf("error: zero divisor for modulus\n");
    }
    break;
  case ALPHA_OP:
    // assignment to a variable, e.g., "=a"
    if (s[0] == '=' && isalpha(s[1]) && s[2] == '\0')
    {
      vars[tolower(s[1]) - 'a'] = pop();
      break;
    }
    // get the value of a variable
    if (isalpha(s[0]) && s[1] == '\0')
    {
      push(vars[tolower(s[0]) - 'a']);
      break;
    }
    // "ans" is a variable for the last value shown by pressing enter
    if (strcmp(s, "ans") == 0)
    {
      push(ans);
      break;
    }
    if (strcmp(s, "show") == 0) // print the top element
    {
      x = pop();
      printf("\t%.8g\n", x);
      push(x);
      break;
    }
    if (strcmp(s, "dup") == 0) // duplicate the top element
    {
      x = pop();
      push(x);
      push(x);
      break;
    }
    if (strcmp(s, "swap") == 0) // swap the top two elements
    {
      y = pop();
      x = pop();
      push(y);
      push(x);
      break;
    }
    if (strcmp(s, "clr") == 0) // clear the stack
    {
      while (size() > 0)
      {
        pop();
      }
      break;
    }
    if (strcmp(s, "sin") == 0)
    {
      push(sin(pop()));
      break;
    }
    if (strcmp(s, "exp") == 0)
    {
      push(exp(pop()));
      break;
    }
    if (strcmp(s, "pow") == 0)
    {
      y = pop();
      push(pow(pop(), y));
      break;
    }
  // fallthrough if none of the strcmp's find a match
  default:
    printf("error: unknown command %s\n", s);
    break;
  }
}

static struct vector *stack;

void init_stack(void)
{
  stack = vector_new(sizeof(double));
}

void destroy_stack(void)
{
  vector_free(stack);
}

// push: push f onto value stack
void push(double f)
{
  vector_push_back(stack, &f);
}

// pop: pop and return top value from stack
double pop(void)
{
  double *p = vector_back(stack);
  if (p == NULL)
  {
    printf("error: stack empty\n");
    return NAN;
  }
  double f = *p;
  vector_pop_back(stack);
  return f;
}

// size: get the number of elements on the stack
size_t size(void)
{
  return vector_size(stack);
}
