#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 1000      /* Max length of any input line */
#define MAXLINES 5000    /* Max number of lines */


char* lineptr[MAXLEN];
int   nlines;

int   atoi1(char*);
char* alloc(int);
int   getline1(char*,int);
int   readlines(char*[],int);
void  writelines(char*[],int);

int main(int argc,char* argv[])
{
	int n,i,j;
	char number[100];

	if(argc == 1){
		n = 10;
	}else{
		if(argv[1][0] == '-'){
			
			i = 1;
			j = 0;
			while(isdigit(argv[1][i])){
				number[j++] = argv[1][i++];    		/* Extracting number in a string */	
			}
			number[j] = '\0';

			n = atoi1(number);
		}else{
			n = 10;
		}
	}

	nlines = readlines(lineptr,MAXLEN);

	if(n > nlines){
		n = nlines;
	}
	writelines(lineptr,n);
	printf("\n%d\n",n);

	return 0;
}
int atoi1(char* c){
	int i;
	int integer = 0;
	i = 0;
	while(c[i] != '\0'){
		integer *= 10;		
		integer += c[i++] - '0';
	}
	return integer; 
}
char* alloc(int len){
	char *memalloc = malloc(len);
	if(!memalloc){   	/* in case the malloc() failed */
		return NULL;
	}
	return memalloc;
}
int getline1(char* line,int n){
	int c,i;
	i = 0;
	while((c = getchar()) != EOF && i < n - 1){
		line[i++] = c;
		if(c == '\n')
			break;
	}
	line[i] = '\0';
	return i;	
}
int readlines(char *lineptr[],int maxlines){
	int len,nlines;
	char *p,line[MAXLEN];

	nlines = 0;
	while((len = getline1(line,MAXLEN)) > 0){
		if(nlines >= maxlines || (p = alloc(len)) == NULL){
			return -1;
		}else{
			line[len - 1] = '\0'; /* Delete new line */
			strcpy(p,line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;
}

void writelines(char *lineptr[],int n){
	int i = nlines - n;
	
	while(n--)
	{
		printf("%s\n",lineptr[i++]);
	}

}
