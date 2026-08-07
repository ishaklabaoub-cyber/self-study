#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 1000

char *lineptr[MAXLINES];

int   atoi1(char*);
char* alloc(int); 
int   getline1(char*,int);
int   readlines(char *lineptr[], int nlines);
void  writelines(char *lineptr[], int nlines);
void  qsort1(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int   numcmp(char *, char *);
int   compare(char*, char*);

int numeric = 0; 
int reverse = 0;

int main(int argc, char *argv[])
{
    int nlines;
    int i,j;

    j = 1;
    if(argc > 1){    
    	while(j < argc){	    
    		if(argv[j][0] == '-'){
			i = 1;
			while(isalpha(argv[j][i])){
				if(tolower(argv[j][i]) == 'r'){
					reverse = 1;
				}else if(tolower(argv[j][i]) == 'n'){
					numeric = 1;
				}
				i++;
			}
		}
		j++;
    	}
    }
    nlines = readlines(lineptr, MAXLINES);
    if (nlines >= 0) {
        qsort((void **) lineptr, nlines, sizeof(lineptr[0]),(int (*)(const void *, const void *)) compare);
		 
	writelines(lineptr, nlines);
        return 0;
    } else {
        printf("input too big to sort\n");
        return 1;
    }
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
	double v1, v2;
	v1 = atof(s1);
	v2 = atof(s2);
	if (v1 < v2){
		return -1;
	} else if (v1 > v2){
		return 1;
	} else {
		return 0;
	}
}
int compare(char *s1, char *s2)
{
    int cond;

    cond = numeric ? numcmp(s1, s2) : strcmp(s1, s2);

    if (reverse) cond = -cond; 

    return cond;
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

int readlines(char* lineptr[],int maxlen){
	int len,nlines;
	char *p,line[MAXLEN];

	nlines = 0;
	while((len = getline1(line,maxlen)) > 0){
		if(nlines >= maxlen || (p = alloc(len)) == NULL){
			return -1;
		}else{
			line[len - 1] = '\0';  /* Deletes new line */
			strcpy(p,line);
			lineptr[nlines++] = p;
		}
	}
	return nlines;

}

void writelines(char* lineptr[],int nlines){
	int i;
	for(i = 0;i < nlines;i++){
		printf("%s\n",lineptr[i]);
	}
}
