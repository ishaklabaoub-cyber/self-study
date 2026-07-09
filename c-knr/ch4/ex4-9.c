#include <stdio.h>
#include <stdlib.h>          /* for atof() */
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAXOP   100          /* max size of operand or operator */
#define NUMBER  '0'   /* signal that a number was found */
#define WORD    'w'
#define VAR     'v'
#define MAXVAL  100          /* maximum depth of val stack */
#define BUFSIZE 100

/* functions */
int    getop(char []);
void   push(double);
double pop(void);
int    getch(void);
void   ungetch(int);

/* globals */
int    sp;		     /* next free stack position */	
int    pb;	             /* pusback character */	 
int    has_pb = 0;           /* Flag to know if a character has pushed back*/
char   last_var;             /* variable name */
double val[MAXVAL];	     /* value stack */
double var[26];	     	     /* variables array */

int main(){
	int type;
	double op2 , op1, mrpv = 0.0;
	char s[MAXOP];

	while ((type = getop(s)) != EOF){
		switch (type) {
			case NUMBER:
				push(atof(s));
			break;
			case WORD:
				op2 = pop();
				if(!strcmp("sin",s)){
					push(sin(op2));
				}else if(!strcmp("exp",s)){
					push(exp(op2));
				}else if(!strcmp("pow",s)){
					op1 = pop();
					push(pow(op1,op2));
				}else {
    					printf("error: unknown function %s\n", s);
	    				push(op2);  // put the popped value back
				}
			break;
			case '+':
				push(pop() + pop());
			break;
			case '*':
				push(pop() * pop());
			break;
			case '-':
				op2 = pop();
				push(pop() - op2);
			break;
			case '/':
				op2 = pop();
				if (op2 != 0.0){
					push(pop() / op2);
				}else{
					printf("error: zero divisor\n");
				}
			break;
			case '%':
				op2 = pop();
				op1 = pop();
				if(op2 != 0.0){
					push((int)op1 % (int)op2);		
				}else{
					printf("error: zero divisor\n");
				}
			break;
			case '?':
				if(sp > 0){
					printf("\tLast element:%.8g\n",val[sp - 1]);
				}else{
					printf("\nStack is Empty.\n");
				}
			break;
			case '=':
				pop();
				op1 = pop();
				var[last_var - 'a'] = op1;
				push(op1);		
			break;
			case '#':
				if(sp > 0){
					push(val[sp-1]);
				}else{
					printf("\nStack is Empty.\n");
				}
			break;
			case '$':
				if(sp >= 2){
					op2 = pop();
					op1 = pop();
					push(op2);
					push(op1);
				}else{
					printf("\nYou need atleast two elements.\n");
				}
			break;
			case '^':
				sp = 0;	
			break;
			case '_':
				push(mrpv);
			break;
			case '\n':
				mrpv = pop();
				printf("\t%.8g\n", mrpv);
			break;
			default:
				if(islower(type)){
        				last_var = type;
        				push(var[type - 'a']);
    				} else {
        				printf("error: unknown command %s\n", s);
    				}
			break;
			}
	}
	return 0;
}

/* push: push f onto value stack */
void push(double f)
{
	if (sp < MAXVAL)
		val[sp++] = f;
	else
		printf("error: stack full, can't push %g\n", f);
}
/* pop: pop and return top value from stack */
double pop(void)
{
	if (sp > 0)
		return val[--sp];
	else {
		printf("error: stack empty\n");
		return 0.0;
	}
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
	int i, c;

	while ((s[0] = c = getch()) == ' ' || c == '\t')
		;
	s[1] = '\0';

	i = 0;
	if(c == '-')                      /* check sign */
		if (!isdigit(s[++i] = c = getch())){
			ungetch(c);
			c = s[0];                  /* not a sign */
	}
	if(isalpha(c)){
			while(isalpha(s[++i] = c = getch()))
				;
		s[i] = '\0';
		ungetch(c);
		if(i == 1){
			last_var = s[0];
			return last_var;
		}
		return WORD;
	}
	if (!isdigit(c) && c != '.')
		return c;                      /* not a number */

	if(isdigit(c))
		while (isdigit(s[++i] = c = getch()))
			;
	if(c == '.')                      /* collect fraction part */
		while (isdigit(s[++i] = c = getch()))
			;	
	s[i] = '\0';
	if (c != EOF)
		ungetch(c);
	return NUMBER;
}

/* getch: get a (possibly pushed back) character */
int getch(void)
{
	if(has_pb){
		has_pb = 0;
		return pb;
	}
	return getchar();
}

/* ungetch: push character back on input */
void ungetch(int c)
{
		pb = c;
		has_pb = 1;
}
