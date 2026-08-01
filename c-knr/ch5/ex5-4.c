#include <stdio.h>

int strend(char[],char[]);

int main()
{
	char s1[12] = "world hello";
	char s2[6] = "hello";

	if(strend(s1,s2)){
		printf("\nEXISTS\n");
	}else{
		printf("\nYAAW\n");
	}
	
	return 0;
}

int strend(char s[],char t[]){
	int i = 0;
	while(*s != '\0')
		s++;
	while(*t != '\0'){
		t++;
		i++;
	}
	

	for(;*s == *t && (i > 0); s--,t--){
		i--;
	}

	if(i == 0){	// Loop goes through all of t
		return 1;
	}else{		// There is a character that does not match
		return 0;
	}
}
