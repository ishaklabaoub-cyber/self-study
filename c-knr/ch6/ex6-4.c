#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFSIZE 100
#define MAXWORD 100
#define MAXNUMS 100

char buf[BUFSIZE];
int  bufp = 0;
int  print_index = 0;


int 	getch(void);
void  	ungetch(int);
int 	getword(char*,int);
struct  tnode *addtree_words(struct tnode*,char*);
struct  tnode *talloc();
void 	print_tree(struct tnode*);
void    sorting(struct tnode*,int);
int 	find_max(struct tnode*,int,int);

struct tnode{
	char *word;			/* word from input */
	int  occ;			/* counter of occurrences */
	struct tnode *left;		/* left child */
	struct tnode *right;		/* right child */
};

struct tnode result[MAXWORD];



int main()
{
	int i;
	struct tnode *root;
	char word[MAXWORD];


	root = NULL;
	while(getword(word,MAXWORD) != EOF){
		if ( isalpha(word[0])){
			root = addtree_words(root,word);
		}
	}
	putchar('\n');
	print_tree(root);
	sorting(result,print_index);

	i = 0;
	while(result[i].occ != 0){
		printf("\t%d %s\n", result[i].occ, result[i].word);
		i++;
	}
		
	return 0;
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
	return (struct tnode*)malloc(sizeof(struct tnode));
}
struct tnode *addtree_words(struct tnode *p,char* w){
	int cond;
	if(p == NULL){		/* new node */
		p = talloc();
		p->word = strdup(w);
		p->occ = 1;
		p->left = p->right = NULL;	
	} else if( (cond =strcmp(w,p->word)) == 0){
		p->occ++; 	// repeated word
	} else if(cond < 0){
		p->left = addtree_words(p->left,w);
	} else {
		p->right = addtree_words(p->right,w);
	}
	return p;
}

int  find_max(struct tnode *result,int len,int index){
	int max = result[index].occ;
	int j = index;
	for(int i = index+1;i < len;i++){
		if(result[i].occ > max){
			max = result[i].occ;	
			j = i;
		}
	}
	return j;
}

void sorting(struct tnode *result,int len){
	char *temp_word;
	int  temp_num;
	int  j = 0;
	for(int i = 0;i < len-1;i++){
		j = find_max(result,len,i);
		if(result[i].occ < result[j].occ){
			temp_word = result[i].word; 			temp_num 	 = result[i].occ;
			result[i].word   = result[j].word;		result[i].occ	 = result[j].occ;
			result[j].word   = temp_word; 			result[j].occ   = temp_num;
		}
	}
}
void print_tree(struct tnode *p){
	if(p != NULL){
		print_tree(p->left);
		result[print_index].word = p->word;
		result[print_index].occ  = p->occ;
		print_index++;
		print_tree(p->right);
	}
}
