#include <stdio.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 80


int main()
{
	int c;
	int column_c = 0;

	while((c = getchar()) != EOF)
	{
		if(c != '\n' && column_c >= MAX_LINE_LENGTH){
			putchar('\n');
			column_c = 0;
		}
		if(isprint(c)){
			putchar(c);
			column_c++;
		} else if(/*c == '\t' || 
			  c == '\a' || 
			  c == '\n'*/c >= 0 && c <= 32 )
		{
			printf("/%#o",c);
			column_c += 4;	// for example: '/t' --> /011 (Four characters).
		
			if(c == '\n'){	// if encounters with a new line print it as it is
				putchar('\n');
				column_c = 0;
			}
		} else if(c == '\0'){
			printf("/%#o",'\0');
			column_c += 2;
		}
	}
	return 0;
}
