#include <stdio.h>
#include <ctype.h>
#define BUFSIZE 100

char buf[BUFSIZE];
int bufp = 0;

int getch(void);
void ungetch(int);
float getfloat(float*);

int main()
{

    float n;
    int result;

    while ((result = getfloat(&n)) != EOF){
        if(result == 0.0)
            printf("not a number\n");
        else
            printf("read: %.2f\n", n);
    }
	return 0;	
}

int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c){
	if(bufp >= BUFSIZE){
		printf("ungetch: too many characters\n");
	}else{
		buf[bufp++] = c;
	}
}	

float getfloat(float *pn){
	int c,sign;
	while(isspace(c = getch())) /* Skip white spaces */
		;
	if(!isdigit(c) && c != EOF && c != '+' && c != '-'){
		ungetch(c); /* Not a number */
		return 0.0;
	}
	sign = (c == '-') ? -1 : 1;
	if(c == '+' || c == '-'){
		int sign_char = c;
		c = getch();
		if(!isdigit(c)){
			/* Not a number */
			ungetch(c);
			ungetch(sign_char);
			return 0.0;
		}
	}
	for(*pn = 0; isdigit(c); c = getch())
		*pn = 10 * *pn + (c - '0');
	
	double power = 1.0;
	if(c == '.'){
		c = getch();
		for(;isdigit(c);c = getch()){
			*pn = 10.0 * *pn + (c - '0');
         		power *= 10.0;
		}
	}
	*pn /= power;
	*pn *= sign;
	if(c != EOF)
		ungetch(c);
	return c;
}
