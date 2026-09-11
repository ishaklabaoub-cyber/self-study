#include <endian.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdarg.h>

#define MAX_LENGTH 100

int minscanf(char*,...);

int main()
{
    int n = 100;
    //char c = 'a';
    //printf("Enter n m:");
    minscanf("enterd%d", &n);
    printf("n --> %d\n", n);
	return 0;
}

int minscanf(char *fmt,...){
    int c;
    va_list ap; /* points to each argument in turn */
	int *ival;
    char *cval;
    char *p;

    char temp_str[MAX_LENGTH] = "";
    int  temp_num;
    int  flag = 0;
    int  i,j;
	
    va_start(ap, fmt);
	for(p = fmt; *p; p++){	//scan the format given
          while(isspace(*p)){
                p++;
          }


        if(flag){       // if there's a formatting text in fmt , advance p so it points to the '%'
            --j;
            p += j;
        }
        if(*p != '%'){
            i = 0;
            j = 0;  
            while(*(p+j) != '%' && *p != '\0'){   // store the index that '%' is in
                j++;
            }
            temp_num = 0;
            while(((c = getchar()) != EOF) && c != '\n' && i < MAX_LENGTH){
                if(isdigit(c)){
                    temp_num *= 10;
                    temp_num += c - '0';
                } else{
                    temp_str[i++] = c;      // storing the text given by the user
                }
            }
            temp_str[i] = '\0';
            
            int ret;
            if((ret = strncmp(temp_str, fmt, j)) != 0){     // comparing the text of the user with the formatting in fmt
                // if they aren't similair assign 0 to the argument passed
                ival = va_arg(ap, int*);
                *ival = 0;
                return 1;  
            } else if(ret == 0){    
                // if they are similair we assign later 'temp_num' to the argument passed
                flag = 1;
            
            }
                    continue;
        }
        ++p;
        switch(*p){
            case 'd':
                ival = va_arg(ap, int*);
                *ival = 0;
                if(flag){
                    flag = 0;
                    *ival = temp_num;
                    break;
                }
                while(isdigit(c = getchar()) && c != '\n'){
                    *ival = *ival*10 + (c - '0');
                }
                break;
            case 'c':
                cval = va_arg(ap, char*);
                    printf("\t\tDEBUG0\n");
                if( (c = getchar()) == EOF){
                    printf("\t\tDEBUG1\n");
                    *cval = 0;
                } else{
                    printf("\t\tDEBUG2\n");
                    *cval = c;
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
