#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#define MAX_LENGTH 100

int minscanf(char*,...);

int main()
{
    int n = 100;
    
    //printf("Enter n:");
    minscanf("enter:%d",&n);
    printf("n--> %d\n",n);
	return 0;
}

int minscanf(char *fmt,...){
    int c;
    va_list ap; /* points to each argument in turn */
	int *ival;  
    char *p;
    char temp_str[MAX_LENGTH] = "";
    int i;
	
    va_start(ap, fmt);
	while(isspace(*fmt)){   // Skipping white spaces
            fmt++;
    }
	for(p = fmt; *p; p++){	//scan the format given
        if(*p != '%'){
            i = 0;
            while(((c = getchar()) != EOF) && c != '\n' && !isdigit(c)){
                       printf("\t\tDEBUG: wow0\n");
                       printf("\t\tDEBUG:%c\n",c); 
                       temp_str[i++] = c;
                     printf("\t\tDEBUG: temp_str[%s]\n", fmt);
            }
            printf("\t\tDEBUG: wow1\n");
            temp_str[++i] = '\0';
            printf("\t\tDEBUG: fmt[%s]\n", fmt);
            printf("\t\tDEBUG: temp_str[%s]\n", fmt);
            if(strncmp(temp_str, fmt, i) != 0){
                printf("\t\tDEBUG: wow2\n");
                ival = va_arg(ap, int*);
                *ival = 0;
                return 1;
                break;
            }
                    continue;
        }
        ++p;
        switch(*p){
            case 'd':
                ival = va_arg(ap, int*);
                while(isdigit(c = getchar()) && c != '\n'){
                    *ival = *ival*10 + (c - '0');
                }
                break;
            default:
                putchar(*p);
                break;
        }
	}
    va_end(ap);
    return 0;
}
