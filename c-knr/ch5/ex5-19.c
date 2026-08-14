#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>

#define BUFSIZE  1000
#define MAXTOKEN 1000

enum { NAME, PARENS, BRACKETS };
jmp_buf recover;


int  gettoken(void);
int  getch(void);
void ungetch(int);


char buf[BUFSIZE];	 /* buffer for unugetch */	
int  bufp = 0;		 /* next free position in buf */
int  tokentype;		 /* type of last token */
char token[500];	 /* last token string */
char name[MAXTOKEN];	 /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[500];


int main() /* convert words to declarations */
{
	int type;
	char temp[MAXTOKEN];
	char prevtoken[500];


	while (gettoken() != EOF) {
		strcpy(out, token);
		prevtoken[0] = '\0';
		while ((type = gettoken()) != '\n'){
			if (type == PARENS || type == BRACKETS){
				if(strstr(prevtoken,"*")){
					sprintf(temp,"(%s)",out);
					strcpy(out,temp);
					strcat(out,token);
				}else{
					strcat(out, token);
				}
			}else if (type == '*') {
				if(strstr(prevtoken,"()") == NULL || 
				   strstr(prevtoken,"*")  == NULL || 
				   strstr(prevtoken,"[]") == NULL ){
					sprintf(temp, "*%s", out);
				}else{
					sprintf(temp, "(*%s)", out);
				}
				strcpy(out, temp);
			} else if (type == NAME) {
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			} else {
				printf("invalid input at %s\n", token);	
			}
			strcpy(prevtoken,token);
		}	
		printf("%s\n",out);		
	}	
	return 0;
}

int getch(void)      /* get a (possibly pushed-back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters pushed back\n");
    else
        buf[bufp++] = c;
}
int gettoken(void) /* return next token */
{
	int c, getch(void);
	void ungetch(int);
	char *p = token;
		while ((c = getch()) == ' ' || c == '\t')
			;
		if (c == '(') {
			if ((c = getch()) == ')') {
				strcpy(token, "()");
				return tokentype = PARENS;
			} else {
				ungetch(c);
				return tokentype = '(';
			}	
		} else if (c == '[') {
			for (*p++ = c; (*p++ = getch()) != ']'; )
				;
			*p = '\0';
			return tokentype = BRACKETS;
		} else if (isalpha(c)) {
			for (*p++ = c; isalnum(c = getch()); )
				*p++ = c;
			*p = '\0';
			ungetch(c);
			return tokentype = NAME;
		} else{
			token[0] = c;
			token[1] = '\0';
			return tokentype = c;	
		}
}
