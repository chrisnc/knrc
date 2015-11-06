#include <stdio.h>
#include <stdlib.h> // for atof
#include <ctype.h>

#define MAXOP 100  // max size of operand or operator
#define NUMBER '0' // signal that a number was found

int getop(char[]);
void push(double);
double pop(void);
int size(void);

// reverse Polish calculator
int main(void)
{
  int type;
  double x, y;
  char s[MAXOP];

  while ((type = getop(s)) != EOF)
  {
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
    // Exercise 4-3. (part 1) page 79
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
    // Exercise 4-4. page 79
    case 'p': // print the top element
      x = pop();
      printf("%f\n", x);
      push(x);
      break;
    case 'd': // duplicate the top element
      x = pop();
      push(x);
      push(x);
      break;
    case 's': // swap the top two elements
      y = pop();
      x = pop();
      push(y);
      push(x);
      break;
    case 'c': // clear the stack
      while (size() > 0)
      {
        pop();
      }
      break;
    case '\n':
      printf("\t%.8g\n", pop());
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  return 0;
}

#define MAXVAL 100 // maximum depth of val stack

static int sp = 0;         // next free stack position
static double val[MAXVAL]; // value stack

// push: push f onto value stack
void push(double f)
{
  if (sp < MAXVAL)
  {
    val[sp++] = f;
  }
  else
  {
    printf("error: stack full, can't push %g\n", f);
  }
}

// pop: pop and return top value from stack
double pop(void)
{
  if (sp > 0)
  {
    return val[--sp];
  }
  else
  {
    printf("error: stack empty\n");
    return 0.0;
  }
}

int size(void)
{
  return sp;
}

int getch(void);
void ungetch(int);

// getop: get next operator or numeric operand
int getop(char s[])
{
  int c;
  while ((s[0] = (char)(c = getch())) == ' ' || c == '\t')
  {
  }
  s[1] = '\0';
  int i = 0;
  // Exercise 4-3. (part 2) page 79
  if (c == '-')
  {
    // after reading a '-', peek at the next character
    // if it isn't a digit, return the '-' as an op
    // otherwise continue reading the number
    ungetch(c = getch());
    if (!isdigit(c))
    {
      return '-';
    }
  }
  else if (!isdigit(c) && c != '.')
  {
    return c; // not a number
  }
  if (isdigit(c)) // collect integer part
  {
    while (isdigit(s[++i] = (char)(c = getch())))
    {
    }
  }
  if (c == '.') // collect fraction part
  {
    while (isdigit(s[++i] = (char)(c = getch())))
    {
    }
  }
  s[i] = '\0';
  if (c != EOF)
  {
    ungetch(c);
  }
  return NUMBER;
}

#define BUFSIZE 100

static char buf[BUFSIZE];
static int bufp = 0;

// get a (possibly pushed back) character
int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

// push character back on input
void ungetch(int c)
{
  if (bufp >= BUFSIZE)
  {
    printf("ungetch: too many characters\n");
  }
  else
  {
    buf[bufp++] = (char)c;
  }
}
