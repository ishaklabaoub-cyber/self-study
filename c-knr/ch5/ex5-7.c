#include <stdio.h>
#include <string.h>
#define MAXLINES 5000      /* max #lines to be sorted */
#define MAXLEN 1000        /* max length of any input line */
#define BUFSIZE 1000       /* max length of the buffer */

char *lineptr[MAXLINES];   /* pointers to text lines */
char buf[BUFSIZE];
int  bufp = 0;

void writelines(char *lineptr[], int nlines);
int readlines(char *lineptr[], int nlines);

int main()
{
	int nlines;/* number of input lines read */
	
	if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
		//qsort(lineptr, 0, nlines-1);
		writelines(lineptr, nlines);
		return 0;
	}else {
		printf("error: input too big to sort\n");
		return 1;
	}
}



/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
	int len, nlines;
	char line[MAXLEN];
	nlines = 0;
	while((len = getline(line,MAXLEN)) > 0){
		if(nlines >= maxlines || (len + bufp) >= BUFSIZE){
			return -1;
		}else{
			line[len - 1] = '\0'; /* delete new line */
			strcpy(buf + bufp,line);
			lineptr[nlines++] = buf + bufp;
			bufp += len;
		}
		
	}
	return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
	int i;
	for (i = 0; i < nlines; i++)
		printf("%s\n", lineptr[i]);
}
