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
    minscanf("enter%d %d", &n, &m);         /* Example */
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
        while(isspace(*p)){     // skipping white-spaces
            p++;
        }

        if(*p != '%'){
            while((c = getchar()) != EOF && c != '\n' && *p != '%' && *p != '\0'){  // checking the input to the format
                    if(c != *p){
                        conversion_type = 'v';      // 'v' is a sentinel value
                        break;
                    }
                    p++;
            }
        }
            while(isspace(*p)){     // skipping white-spaces to get to the '%' hopefully
                p++;
            }
        if(*p == '%' && conversion_type != 'v'){
            j = 0;
            while(isspace(*p)){
                p++;
            }
            conversion_type = *++p;
                  

            while((c = getchar()) != EOF && c != '\n' && !isspace(c) && j < MAX_LENGTH){    // store the value in a string
                value[j] = c;
                j++;
            }
            value[j] = '\0';
        }
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
