#include <stdio.h>

int strindex(char* s,char* t);


int main()
{
	char s[200] = "Hello hello!";
	char t[200] = "ello";

	int i = strindex(s,t);
	printf("\n%d\n",i);

	return 0;
}


int strindex(char* s,char* t){
	int i,j,k,index = -1;

	for(i = 0;s[i] != '\0';i++){
		for(j=i,k=0;t[k] != '\0' && s[j] == t[k];k++,j++){
			;
		}
		if(k > 0 && t[k] == '\0'){
			index = i;
		}
	}
		return index;
	
}
