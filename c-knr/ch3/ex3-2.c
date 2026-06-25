#include <stdio.h>

void escape(char* s,char* t);


int main()
{
	int c,i = 0;
	char t[20] = {""};
	char s[30] = {""};

	while( (c = getchar()) != EOF && i < 20){
		t[i] = c;
		i++;
	}
	t[i] = '\0';

	escape(s,t);

	printf("\n%s\n",s);
	return 0;
}



void escape(char* s,char* t){
	int i = 0,j = 0;
	for(i = j = 0;t[i] != '\0';i++){
		switch(t[i]){
			case '\n':
				s[j] = '\\';
				s[++j] = 'n';
				break;
			case '\t':
				s[j] = '\\';
				s[++j] = 't';
				break;	
			default:
				s[j] = t[i];	
				break;
		}
		j++;
	}
	
	s[j] = '\0';

}
