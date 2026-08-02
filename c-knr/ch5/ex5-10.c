#include <stdio.h>
#include <stdlib.h>   /* for atof */
#include <ctype.h>    /* for isdigit */

#define MAXOP 100
#define MAXVAL 100

int sp = 0;
double val[MAXVAL];

void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else {
        printf("error: stack empty\n");
        return 0.0;
    }
}

int main(int argc, char *argv[])
{
    int i;
    double op2;

    for (i = 1; i < argc; i++) {
        /* TODO: figure out — is argv[i] a number, or an operator? */
        if (isdigit(argv[i][0]) || (argv[i][0] == '-' && argv[i][1] != '\0')) {
            push(atof(argv[i]));
        } else {
            switch (argv[i][0]) {
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
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero divisor\n");
                break;
            default:
                printf("error: unknown operator %s\n", argv[i]);
                break;
            }
        }
    }

    printf("%g\n", pop());
    return 0;
}
