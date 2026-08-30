#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define BUFSIZE 100
#define MAXWORD 100
#define MAXNUMS 100

char buf[BUFSIZE];
int  bufp = 0;
char *tree_words[MAXWORD];
int  tree_nums[MAXNUMS];
int  print_index = 0;


int 	getch(void);
void  	ungetch(int);
int 	getword(char*,int);
struct  tnode *addtree_words(struct tnode*,char*);
struct  tnode *talloc();
void 	print_tree(struct tnode*);
void    sorting(int[],char*[],int);
int 	find_max(int*,int,int);

struct tnode{
	char *word;			/* word from input */
	int  occ;			/* counter of occurrences */
	struct tnode *left;		/* left child */
	struct tnode *right;		/* right child */
};




int main()
{
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
	int len = sizeof(tree_nums) / sizeof(tree_nums[0]);
	sorting(tree_nums,tree_words,len);

	int i = 0;
	while(tree_words[i] != NULL){
		printf("\t%d %s\n", tree_nums[i], tree_words[i]);
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

int  find_max(int *arr,int len,int index){
	int max = arr[index];
	int j = index;
	for(int i = index+1;i < len;i++){
		if(arr[i] > max){
			max = arr[i];	
			j = i;
		}
	}
	return j;
}

void sorting(int arr[],char *words[],int len){
	char *temp_word;
	int  temp_num;
	int  j = 0;
	for(int i = 0;i < len-1;i++){
			j = find_max(arr,len,i);
		if(arr[i] < arr[j]){
			temp_word = words[i]; 		temp_num = arr[i];
			words[i]   = words[j];		arr[i]	 = arr[j];
			words[j]   = temp_word; 	arr[j]   = temp_num;
		}
	}
}
void print_tree(struct tnode *p){
	//static int i = 0;
	if(p != NULL){
		print_tree(p->left);
		tree_words[print_index] = p->word;
		tree_nums[print_index]  = p->occ;
		print_index++;
		print_tree(p->right);
	}
}
