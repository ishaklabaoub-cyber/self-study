#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFSIZE 100
#define MAXWORD 100
#define MAXLINE 50
		
char  buf[BUFSIZE];			/* buffer to store input */
int   bufp = 0;				/* buffer postion */
int   line_n = 1;			/* counter tracking input line number */

struct tnode{
	char   *word;			/* word from input */
	int    line_num[MAXLINE];	/* array for line number storing */
	int    nlines;		        /* how many line numbers are stored */
	struct tnode *left;		/* left child */
	struct tnode *right;		/* right child */
};

struct 	tnode *talloc();
struct  tnode *addtree(struct tnode*,char*);
void 	treewords(struct tnode*);
int 	getch(void);
void  	ungetch(int);
int 	getword(char*,int);


char *noise_words[10] = {
	"an","the", "and", "a", "of", "is", NULL		/* noise words to avoid like : the, and, a, of, is ...etc*/
};


int main()
{
	int i,flag;
	struct tnode *root;
	char word[MAXWORD];
	

	root = NULL;
	while(getword(word,MAXWORD) != EOF){
		flag = 0;
		i = 0;
		if ( isalpha(word[0])){
			while(noise_words[i] != NULL){
				if(strcmp(noise_words[i],word) == 0){
					flag = 1;
					break;
				}
				i++;
			}
			if(!flag){
				root = addtree(root,word);
			}
		}
	}
	treewords(root);
	return 0;
}
int getch(void){
	int c = (bufp > 0) ? buf[--bufp] : getchar();
	if(c == '\n')line_n++;
	return c;	
}
void ungetch(int c){
	if(bufp >= BUFSIZE){
		printf("ungetch : too many characters pushed back\n");
	}else{
		if(c == '\n')line_n--;
		buf[bufp++] = c;
	}
}

/* getword: get next word or character from input */
int getword(char* word,int limit)
{
	int c;
	char *w = word;

	while(isspace(c = getch()))
		;
	

	if (c == '#'){
		while((c = getch()) != '\n' && c != EOF)
			;
		
		if (c == EOF){
			return EOF;
		}
	}
	if(c == '/'){

		c = getch();
		
		
		if (c == '/'){
			while((c = getch()) != '\n' && c != EOF)
				;
			
			if(c == EOF)
				return EOF;
		} else if (c == '*'){

			char prev = 0;
			while((prev != '*' || c != '/' ) && c != EOF){
					
					prev = c;
					c = getch();
			}
			if(c == EOF)
				return EOF;
			c = getch();

		} else{
			ungetch(c);
			c = '/';
		}
	}
	    /* string constant: consume and discard the whole literal, then
       recurse to get the next real token */
    	if (c == '"') {
        	int prevc = 0;
       		 while ((c = getch()) != EOF) {
			 if (c == '"' && prevc != '\\')
        	      			  break;
            		prevc = c;
        	}
        	if (c == EOF)
            		return EOF;
        	return getword(word, limit);
    	}
	if (c != EOF){	
		*w++=c;
	}	
	if ( !isalpha(c) && c != '_'){
		*w = '\0';
		return c;
	}
	for(;limit-- > 0;w++)
		if( !isalnum(*w = getch()) && *w != '_'){
			ungetch(*w);
			break;
		}

	*w = '\0';
	return word[0];
}

struct tnode *talloc(){
	return (struct tnode *)malloc(sizeof(struct tnode));
}
struct tnode *addtree(struct tnode *p,char *w){
	int cond;
	if(p == NULL){
		p = talloc();
		p->word = strdup(w);
		p->nlines = 0;
		p->line_num[p->nlines++] = line_n;
		p->left = p->right = NULL;
	} else if( (cond = strcmp(w,p->word)) == 0){
			//repeated word
			if(p->nlines >= MAXLINE){
				return NULL;
			}
			p->line_num[p->nlines++] = line_n;
	} else if(cond < 0){
		p->left = addtree(p->left,w);
	} else{
		p->right = addtree(p->right,w);
	}
	return p;
}

void treewords(struct tnode *p){
	int prevn;
	if(p != NULL){
		prevn = 0;
		treewords(p->left);
		printf("\t%s: ",p->word);
		for(int j = 0;p->line_num[j] != 0;j++){
			if(p->line_num[j] != prevn){
				printf("%d ",p->line_num[j]);
			}
			prevn = p->line_num[j];
		}
		putchar('\n');
		treewords(p->right);
	}
}
