#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define  HASHSIZE 101
#define  MAXWORD  100
#define  BUFSIZE  100

struct nlist{		/* table entry:  */
	struct nlist *next;		/* next entry of the chain */
	char *name;			/* defined name */
	char *defn;			/* replacement text */
};

static struct nlist *hashtab[HASHSIZE];		/* pointer table */
char	buf[BUFSIZE];
int 	bufp = 0;
int     defn_flag = 0;
char    name1[BUFSIZE];

unsigned hash(char*);
struct nlist *lookup(char*);
struct nlist *install(char*,char*);
int    getch();
void   ungetch(int);
int    getword(char*,int);
int    undef(char*);

int main()
{
	struct nlist *to_replace;
	char word[MAXWORD];

	while( (getword(word,MAXWORD)) != EOF){
		if((to_replace = lookup(word)) != NULL){
			printf(" %s",to_replace->defn);
		} else{
			printf(" %s",word);
		}
	}
	return 0;
}
int getch(){
	return (bufp > 0) ? buf[bufp--] : getchar();
}
int getword(char *word,int limit){
	char defn[BUFSIZE];
	int c;
	char *w = word;

	while(isspace(c = getch()))
		;
	if(c == '#'){
		if(getword(word,limit) == EOF)
			return EOF;
		if( strcmp(word,"define") == 0){	/* preprocessor definition */

			while(isspace(c = getch()))
				;
			if(getword(name1,limit) == EOF)
				return EOF;
			
			while(isspace(c = getch()))
				;
			
			int i = 0;
			 while((c = getch()) != '\n' && c != EOF){
				defn[i++] = c;			
			}
			
			defn[i] = '\0';			
			
			if(c == EOF)
				return EOF;
			
			install(name1, defn);
		}	
	}
	
	if(c == '/'){
		c = getch();

		if(c == '/'){
			while((c = getch()) != '\n' && c != EOF)
				;
			if(c == EOF)
				return EOF;
		} else if(c == '*'){
			char prev = 0;
			while(!(prev == '*' && c == '/') && c != EOF){
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
	if(c == '"'){
		int prevc = 0;
		while((c = getch()) != EOF){
			if(c == '"' && prevc != '\\')
				break;
			prevc = c;
		}
		if(c == EOF)
			return EOF;
		return getword(word, limit);
	}
	if(c != EOF){
		*w++=c;
	}
	if( !isalpha(c) && c != '_'){
		*w = '\0';
		return c;
	}
	for(;limit-- > 0;w++){
		if( !isalnum(*w = getch()) && *w != '_'){
			ungetch(*w);
			break;
		}
	}
	*w  = '\0';
	return word[0];
}
void ungetch(int c){
	if(bufp >= BUFSIZE){
		printf("ungetch : too many characters pushed back\n");
	} else {
		buf[bufp++] = c;
	}
}

unsigned hash(char *s){
	unsigned hashval;

	for(hashval = 0; *s != '\0';s++){
		hashval = *s + 31 * hashval;
	}
	return hashval % HASHSIZE;
}

struct nlist *lookup(char *s){
	struct nlist *np;

	for((np = hashtab[hash(s)]);np != NULL;np = np->next){
		if(strcmp(s,np->name) == 0){
			return np;    /* found */	
		}
	}
	return NULL;	/* not found */
}


struct nlist *install(char *s,char *defn){
	unsigned hashval;
	struct nlist *np;
	
	if( (np = lookup(s)) == NULL){	/* not found */
		np = (struct nlist *)malloc(sizeof(struct nlist));
		if(np == NULL || (np->name = strdup(s)) == NULL)
			return NULL;
		hashval = hash(s);
		np->next = hashtab[hashval];	
		hashtab[hashval] = np;
	} else{		/* already there */
		free((void *) np->defn);	/* free previous defn */
	}
	if((np->defn = strdup(defn)) == NULL)
			return NULL;
	
	return np;
}

int undef(char *s){
	struct nlist *np,*prev;
	unsigned hashval;

	hashval = hash(s);

	prev = NULL;
	np = hashtab[hashval];

	while( np != NULL && strcmp(np->name,s) != 0){
		prev = np;
		np = np->next;
	}

		if(np == NULL)
			return 1;
		if(prev == NULL){
			hashtab[hashval] = np->next;
		} else{
			prev->next = np->next;
		}
			//freeing
			free((void *)np->name);
			free((void *)np->defn);
			free((void *)np);

	return 0;
}
