#include <stdio.h>

char *lower(char* s);


int main()
{
	char s[] = {"HELLO wORLD"};
	lower(s);
	printf("%s",s);
	return 0;
}


char *lower(char* s){
	for(int i = 0;s[i] != '\0';i++){
		(s[i] >= 'A' && s[i] <= 'Z') ? s[i] = s[i] + 32 : s[i];
	}
	return s;
}
