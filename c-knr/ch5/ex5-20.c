#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <setjmp.h>

#define BUFSIZE  100
#define MAXTOKEN 100

enum { NAME, QUALIFIER , PARENS, BRACKETS };
jmp_buf recover;

void dcl(void);
void dirdcl(void);
int  gettoken(void);
int  getch(void);
void ungetch(int);


char buf[BUFSIZE];	  /* buffer for unugetch */	
int  bufp = 0;		  /* next free position in buf */
int  tokentype;		  /* type of last token */
char token[MAXTOKEN];	  /* last token string */
char name[MAXTOKEN];	  /* identifier name */
char datatype[MAXTOKEN];  /* data type = char, int, etc. */
char qualifier[MAXTOKEN]; /* qualifier = const ,etc. */
char out[1000];


int main() /* convert declaration to words */
{
	int c;
	while (gettoken() != EOF) {		 /* 1st token on line */
		if(setjmp(recover) == 0){
			qualifier[0] = '\0'; 
			
			if( !strcmp("const",token) || !strcmp("volatile",token)){
				strcpy(qualifier,token); /* is the qualifier */
				gettoken();	
			}
			strcpy(datatype, token); /* is the datatype */
		
			out[0] = '\0';

			dcl();			 /* parse rest of line */
		
			printf("%s: %s %s %s\n", name, out, qualifier, datatype);

		}else{
			printf("error: bad declaration\n");
			while((c = getch()) != '\n' && c != EOF)
				; /* discard rest of the bad line */
		}	
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
			for (*p++ = c; (*p++ = getch()) != ']'; )	/* getting Data types or Qualifier*/
				;
			*p = '\0';
			return tokentype = BRACKETS;
		} else if (isalpha(c)) {
			for (*p++ = c; isalnum(c = getch()); )
				*p++ = c;
			*p = '\0';
			ungetch(c);	
			return tokentype = NAME;
			} else
				return tokentype = c;
}

/* dcl: parse a declarator */ 
void dcl(void) { 
	int ns;  
	for (ns = 0; gettoken() == '*'; ) /* count *'s */ 
		ns++; 
	dirdcl(); 
	while (ns-- > 0) 
		strcat(out, " pointer to");
}
/* dirdcl: parse a direct declarator */
void dirdcl(void)
{
    int type;

    if (tokentype == '(') {         /* ( dcl ) */
        dcl();
        if (tokentype != ')')
		longjmp(recover,1);
    } else if (tokentype == NAME){   /* variable name */
        strcpy(name, token);
    } else{
	    longjmp(recover,1);
    }
    while ((type=gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}
