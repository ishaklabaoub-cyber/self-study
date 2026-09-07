#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TOK_DELIM  " ./"
#define BUFSIZE 100

int main(int argc,char **argv)
{
	int c;
	int bufsize = BUFSIZE, pos = 0;
	char **tokens = malloc(bufsize * sizeof(char*));
	char *token;

	if(tokens == NULL){
		fprintf(stderr,"malloc: failed allocation...\n");
		exit(EXIT_FAILURE);
	}

	if(argc == 1){
		token = strtok(argv[0], TOK_DELIM);
		while(token != NULL)
		{
			tokens[pos] = token;
			pos++;
			
			if(pos >= bufsize){
				bufsize += BUFSIZE;
				tokens = realloc(tokens, bufsize * sizeof(char*));
	
				if(tokens == NULL){
					fprintf(stderr,"malloc: failed allocation...\n");
					exit(EXIT_FAILURE);
				}
			}
			token = strtok(NULL, TOK_DELIM);
		}
		tokens[++pos] = NULL;

		for(int i = 0; tokens[i] != NULL; i++)
		{
			if(strcmp(tokens[i], "toupper") == 0){
				while((c = getchar()) != EOF){
					putchar(toupper(c));
					
				}
				break;
			} else if(strcmp(tokens[i], "tolower") == 0){
				while((c = getchar()) != EOF){
					putchar(tolower(c));
				}
				break;
			}
		}
	} else{
		printf("too much arguments.\n");
	}
	return 0;
}
