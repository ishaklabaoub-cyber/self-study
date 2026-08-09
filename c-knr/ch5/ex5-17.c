#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000
#define MAXLEN 	 1000
#define OUT      0	/* OUT the word */
#define IN	 1 	/* INside the word */

char *lineptr[MAXLINES];

int   atoi1(char*);
char* alloc(int); 
int   getline1(char*,int);
int   readlines(char*[],int);
void  writelines(char*[],int);
int   numcmp(char*,char*);
int   foldcmp(char*,char*);
int   dircmp(char*,char*);
int   compare(char**,char**);
char* find_field(char*,int);

int field_n = 0;
int numeric = 0; 
int reverse = 0;
int fold    = 0;
int dir     = 0;

int main(int argc, char *argv[])
{
    int nlines;
    int i,j;

    j = 1;
    if(argc > 1){    
	while(j < argc){
    		i = 0;	
    		if(argv[j][i] == '-'){
			i++;
			while(isalpha(argv[j][i])){
				if(tolower(argv[j][i]) == 'r'){
					reverse = 1;
				}else if(tolower(argv[j][i]) == 'n'){
					numeric = 1;
				}else if(tolower(argv[j][i]) == 'f'){
					fold    = 1;
				}else if(tolower(argv[j][i]) == 'd'){
					dir     = 1;
				}
				i++;
			}
		}if(isdigit(argv[j][i])){
			field_n = atoi1(argv[j]);
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

char* find_field(char* line,int field_n)
{
	int i;
	int state, prev_state;
	if(field_n == 1){
		return line;
	}else if(field_n == 0){
		return line;	
	}else if(field_n < 0){
		return NULL;
	}	
	i = 0;
	state = OUT;
	prev_state = state;
	while(1){
		if(line[i] == ' ' || line[i] == '\t' || line[i] == '\0'){
			state = OUT;
		}else{
			state = IN;	
		}
		if(state == IN && prev_state == OUT){
			--field_n;
		}
		if(field_n == 0){
			return line + i;
		}
		if(field_n != 0 && line[i] == '\0'){
			return NULL;
		}
		prev_state = state;
		i++;
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
int foldcmp(char* s1,char* s2){
	int i;
	for(i = 0;(s1[i] != '\0') || (s2[i] != '\0');i++){
		if(tolower(s1[i]) != tolower(s2[i])){
			break;
		}
	}
	return tolower(s1[i]) - tolower(s2[i]);
}
int dircmp(char *s1,char *s2){
	int i,j;
	char temp1,temp2;
	for(i = 0,j = 0;(s1[j] != '\0') || (s2[i] != '\0');i++,j++){
		temp1 = s1[j];
		temp2 = s2[i];
		if(fold == 1){
			temp1 = tolower(s1[j]);
			temp2 = tolower(s2[i]);

		}
		while( !(isalnum(temp1) || isspace(temp1)) && temp1 != '\0'){    /* skipping  ponctuation */
			if(fold == 1){
				temp1 = tolower(s1[++j]);
			}else{
				temp1 = s1[++j];
			}
		}
		while( !(isalnum(temp2) || isspace(temp2)) && temp2 != '\0' ){   /* skipping  ponctuation */
			if(fold == 1){
				temp2 = tolower(s2[++i]);
			}else{
				temp2 = s2[++i];
			}
		}
			if(temp1 == '\0' && temp2 == '\0'){
				return 0;
			}else if(temp1 == '\0'){
				return -1;			/* in case one of the strings reaches NULL terminator */
			}else if(temp2 == '\0'){
				return 1;
			}
			if(temp1 != temp2){
				break;
			}	
	}
	return temp1 - temp2;
}

int compare(char **s1, char **s2)
{
    	char* field_s1 = find_field(*s1,field_n);
	char* field_s2 = find_field(*s2,field_n);
    	if(field_s1 == NULL || field_s2 == NULL){
		return -1;
	}
	int cond;
    	if(dir == 1){
  
		    cond = dircmp(field_s1,field_s2);
  	
   	 }else{
    		cond = numeric ? numcmp(field_s1, field_s2) : (fold ? foldcmp(field_s1,field_s2) : strcmp(field_s1,field_s2));
    	}
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

void writelines(char* lineptr[],int nlines)
{
	int i;
	for(i = 0;i < nlines;i++){
		printf("%s\n",lineptr[i]);
	}
}
