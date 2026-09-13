#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <stdarg.h>

#define MAX_LENGTH 100

int minscanf(char*,...);

int main()
{
    int n = 100;
    int m = 200;
    //char temp[MAX_LENGTH] = "hello";
    minscanf("enter%d %d", &n, &m);
    printf("n m --> %d %d\n", n, m);
	return 0;
}

int minscanf(char *fmt,...){
    int c, j;
    va_list ap;
    int *ival;
    char *cval;
    char *p;
    char conversion_type;
    char value[MAX_LENGTH] = "";

    va_start(ap, fmt);
    for(p = fmt; *p; p++){
        conversion_type = 0;
        while(isspace(*p)){     // skipping white spaces
            p++;
        }

        if(*p != '%'){
            while((c = getchar()) != EOF && c != '\n' && *p != '%' && *p != '\0'){
                    if(c != *p){
                        conversion_type = 'v';
                        break;
                    }
                    p++;
            }
        }
            while(isspace(*p)){
                p++;
            }
        if(*p == '%' && conversion_type != 'v'){
            j = 0;
            while(isspace(*p)){
                p++;
            }
            conversion_type = *++p;
                  

          /*while(isspace(c = getchar()))
                ;
            c = 0;*/
            while((c = getchar()) != EOF && c != '\n' && !isspace(c) && j < MAX_LENGTH){
                value[j] = c;
                j++;
            }
            value[j] = '\0';
            printf("\t\tDEBUG: value[%s]\n", value);
        }
        while(isspace(c = getchar()))
                ;
        printf("\t\tDEBUG0\n");
        j = 0;
        switch(conversion_type){
            case 'v': 
            case '0':
                // mismatch values not assigned
                return 1;
                break;
            case '%':
                putchar(conversion_type);
                break;
            case 'd':
                ival  = va_arg(ap, int*);
                *ival = 0;
                while(isdigit(value[j]) && value[j] != '\0'){
                    *ival = *ival * 10 + (value[j] - '0');
                    j++;
                }
                break;
            case 'c':
                cval  = va_arg(ap, char*);
                *cval = value[0];
                break;
            case 's':
                cval  = va_arg(ap, char*);
                strcpy(cval, value);
                break;
            default:
                putchar(conversion_type);
                break;
        }


    
    }
    return 0;
}
