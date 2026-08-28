#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFSIZE 100
#define MAXWORD 100

char *words[MAXWORD];
char *group[MAXWORD];
char buf[BUFSIZE];
int  bufp = 0;
int  n;
int  terminate;
struct tnode{			/* tree node */
	char* word;		/* points to the text */
	int count;		/* count of occurrences */
	struct tnode *left;	/* left child */
	struct tnode *right;	/* right child */
};

int 	atoi1(char*);
int 	getch(void);
void  	ungetch(int);
void    search(char*[]);
int 	getword(char*,int);
struct  tnode *talloc(void);
struct  tnode *addtree(struct tnode *,char *);
void    treewords(struct tnode *);

int main(int argc,char **argv)
{
	if(argc == 1){
		n = 6;
	} else{
		if(( n = atoi1(argv[1])) < 0 ){
			printf("INVALID NUMBER\nCONSIDERING N = 6\n");
			n = 6;		
		}	
	}
	struct tnode *root;
	char word[MAXWORD];
	
	root = NULL;
	while(getword(word,MAXWORD) != EOF){
		if ( isalpha(word[0])){
			root = addtree(root,word);	
		}
	}
	
	treewords(root);
	words[terminate] = NULL;
	search(words);
	if(group[0] == NULL){
		printf("\nThere is no matching words \nEND Program.");
		return 0;
	}
	int i = 0;
	while(group[i] != NULL){
		printf("\t%s\n",group[i]);
		i++;
	}
	printf("END Program.\n");
	return 0;
}
int atoi1(char *s){
	int i = 0;
	int sign = 1;
	int result = 0;
	while(isspace(s[i])){
		i++;
	}
	if(s[i] == '-'){
		sign = -1;
		i++;
	}else if(s[i] == '+'){
		i++;
	}

	while(s[i] >= '0' && s[i] <= '9'){
		result = result * 10 + s[i] - '0';
		i++;
	}
	return sign * result;
}
int getch(void){
	return (bufp > 0) ? buf[--bufp] : getchar();
}
void ungetch(int c){
	if(bufp >= BUFSIZE){
		printf("ungetch : too many characters pushed back\n");
	}else{
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

			char prev = '/';
			while((prev != '*' || c != '/' ) && c != EOF){
					prev = c;
					c = getch();	
			}
			if(c == EOF)
				return EOF;
		} else{
			ungetch(c);
			c = '/';
		}
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

void search(char* words[]){
	int flag = 1;		/* flag to store a word once not twice */
	int i = 0,j = 1;
	int h = 0;
	while(words[i] != NULL && words[j] != NULL)
	{
		if(strncmp( words[i], words[j], n ) == 0){
			if(flag == 1){
				group[h++] = words[i];
			}
			group[h++] = words[j];
			j++;
			flag = 0;
		} else{
			flag = 1;
			i = j;
			j++;	
		}
	}
	group[h] = NULL;
}
struct tnode *talloc(){	
	return (struct tnode *)malloc( sizeof(struct tnode));
}

struct  tnode *addtree(struct tnode *p,char *w)
{
	int cond;

	if(p == NULL){		/* a new word has arrived */
		p = talloc();
		p->word = strdup(w);
		p->count = 1;
		p->left = p->right = NULL;
	} else if((cond = strcmp(w,p->word) ) == 0){
			p->count++; 	/* repeated word */
	} else if(cond < 0){
		p->left = addtree(p->left,w);
	} else{
		p->right = addtree(p->right,w);
	}
	return p;
}
void treewords(struct tnode *p){
	static int i = 0;
	if(p != NULL){
		treewords(p->left);
		words[i++] = p->word;
		treewords(p->right);
	}
	terminate = i;
}

