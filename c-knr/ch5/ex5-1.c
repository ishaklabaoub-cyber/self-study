#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
int getint(int *pn);
int main()
{
	
    int n, result;
    
    while ((result = getint(&n)) != EOF){
        if(result == 0)
            printf("not a number\n");
        else
            printf("read: %d\n", n);
    }
	return 0;
}

int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
	int c, sign;
	while (isspace(c = getch()))/* skip white space */
		;
	if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
		ungetch(c); /* it is not a number */
		return 0;
	}
	sign = (c == '-') ? -1 : 1;
	if (c == '+' || c == '-'){
		int sign_char = c;
		c = getch();
		if(!isdigit(c)){
			ungetch(c);
			ungetch(sign_char);
			return 0;
		}
	}
	for (*pn = 0; isdigit(c), c = getch())
		*pn = 10 * *pn + (c - '0');
	*pn *= sign;
	if (c != EOF)
		ungetch(c);
	return c;
}
