#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Section 5.12: Complicated Declarations
// dcl program example, page 123

#define MAXTOKEN 100

enum
{
  NAME,
  PARENS,
  BRACKETS
};

static int gettoken(void);

static int getch(void)
{
  return getc(stdin);
}

static void ungetch(int c)
{
  ungetc(c, stdin);
}

static int tokentype;
static char token[MAXTOKEN];
static char name[MAXTOKEN];
static char datatype[MAXTOKEN];
static char out[1000];

static void dirdcl(void);

static void dcl(void)
{
  int ns;
  for (ns = 0; gettoken() == '*'; ++ns)
  {
  }
  dirdcl();
  while (ns-- > 0)
  {
    strcat(out, " pointer to");
  }
}

static void dirdcl(void)
{
  int type;
  if (tokentype == '(')
  {
    dcl();
    if (tokentype != ')')
    {
      printf("error: missing )\n");
    }
  }
  else if (tokentype == NAME)
  {
    strcpy(name, token);
  }
  else
  {
    printf("error: expected name or (dcl)\n");
  }
  while ((type = gettoken()) == PARENS || type == BRACKETS)
  {
    if (type == PARENS)
    {
      strcat(out, " function returning");
    }
    else
    {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
  }
}

int main(void)
{
  while (gettoken() != EOF)
  {
    strcpy(datatype, token);
    out[0] = '\0';
    dcl();
    if (tokentype != '\n')
    {
      printf("syntax error\n");
    }
    printf("%s: %s %s\n", name, out, datatype);
  }
}

static int gettoken(void)
{
  int c;
  char *p = token;
  while ((c = getch()) == ' ' || c == '\t')
  {
  }
  if (c == '(')
  {
    if ((c = getch()) == ')')
    {
      strcpy(token, "()");
      return tokentype = PARENS;
    }
    else
    {
      ungetch(c);
      return tokentype = '(';
    }
  }
  else if (c == '[')
  {
    for (*p++ = (char)c; (*p++ = (char)getch()) != ']';)
    {
    }
    *p = '\0';
    return tokentype = BRACKETS;
  }
  else if (isalpha(c))
  {
    for (*p++ = (char)c; isalnum(c = getch());)
    {
      *p++ = (char)c;
    }
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  }
  else
  {
    return tokentype = c;
  }
}
