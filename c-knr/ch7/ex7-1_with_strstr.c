#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TOK_DELIM  " ./"
#define BUFSIZE 100

int main(int argc,char **argv)
{
	int c;

	if(argc == 1){
		if(strstr(argv[0], "toupper") != NULL){
			while((c = getchar()) != EOF)
			{
				putchar(toupper(c));
			}
		} else if(strstr(argv[0], "tolower")){
			while((c = getchar()) != EOF)
			{
				putchar(tolower(c));
			}
		} else{
			printf("Pattern not found\n");
			return 1;
		}	
	} else{
		printf("too much arguments.\n");
	}
	return 0;
}
