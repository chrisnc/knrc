#ifndef CONTROL_H
#define CONTROL_H

int binsearch(int x, int v[], int n);
int binsearch_2(int x, int v[], int n);
void reverse(char s[]);
void my_itoa(int n, char s[]);
void fixed_itoa(int n, char *s);
void itob(int n, char *s, int b);
void itoa_padded(int n, char *s, int min_width);

#endif // CONTROL_H
