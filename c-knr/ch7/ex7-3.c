#include <stdio.h>
#include <stdarg.h>

void minprintf(char *fmt, ...);

int main()
{
	int n = 234;			
	minprintf("%125d\n",n);		/* example */
	return 0;
}

void minprintf(char *fmt, ...){
	va_list ap; /* points to each argument in turn*/
	char *p, *sval; 
	int ival;
	double dval;
	int flag;

	va_start(ap, fmt);	/* make ap point to 1st unnamed arg */
	for(p = fmt; *p; p++){
		flag = 0;
		if(*p != '%'){
			putchar(*p);
			continue;
		}
		if(*++p > '0' && *p <= '9'){
			int f_width = 0;
			int temp , num_length = 0;
			flag = 1;
			while(*p > '0' && *p <= '9'){		// parsing multi-digit field width
				f_width = (f_width * 10) + (*p - '0');
				++p;	
			}
		
			ival = va_arg(ap, int);
			temp = ival;
			
			while(temp){
				num_length++;
				temp /= 10;
			}
			if(num_length >= f_width){
				// the number get printed without the width added to the right
			} else{
				f_width -= num_length;  // calculating the approprite field width
				while(f_width){
					putchar(' ');	// adding the field width
					f_width--;
				}
			}
		}
		
		if(!flag)ival = va_arg(ap, int);

		switch(*p){
			case '%':
				putchar(*p);
				break;
			case 'c':
				putchar(ival);
				break;	
			case 'o':
				printf("%o", ival);
				break;	
			case 'x':
				printf("%x", ival);
				break;	
			case 'd':
				printf("%d", ival);
				break;
			case 'f':
				dval = va_arg(ap, double);
				printf("%f",dval);
				break;		
			case 's':
				for(sval = va_arg(ap, char*); *sval; sval++){
					putchar(*sval);
				}
				break;	
			default:
				putchar(*p);
				break;	
		}
	}
	va_end(ap); 	/* clean up when done */
}
