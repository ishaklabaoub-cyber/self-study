#include <stdio.h>

void escape1(char* s,char* t);



int main()
{	
	int c,i = 0;
	char t[20] = {""};
	char s[20] = {""};

	while( (c = getchar()) != EOF && i < 20){
		t[i] = c;
		i++;
	}
	t[i] = '\0';

	escape1(s,t);
	
	printf("\n%s\n",s);

	return 0;
}




void escape1(char* s,char* t){
	char prev = 0;
	int i = 0,j = 0;
	for(i = j = 0;t[i] != '\0';i++){
		if(prev == '\\'){
			switch(t[i]){
				case 't':
					s[--j] = 0;
					s[j] = '\t';
					break;
				case 'n':
					s[--j] = 0;
					s[j] = '\n';
					break;	
				default: 
					s[j] = t[i];
					break;	
			}
		}else{
			s[j] = t[i];
		}	
		prev = t[i];
		j++;
	}
	s[j] = '\0';
}
