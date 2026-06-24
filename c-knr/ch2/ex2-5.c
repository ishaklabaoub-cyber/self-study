#include <stdio.h>

int any(char* s1,char* s2);


int main()
{
	char s1[] = {"hello world"};
	char s2[] = {"lo"};

	printf("%d\n",any(s1,s2));
	
	return 0;
}


int any(char* s1,char* s2){
	
	for(int i = 0;s1[i] != '\0';i++){
		int found = 0;
		for(int j = 0;s2[j] != '\0';j++){
			if(s1[i] == s2[j]){
				found = 1;
				break;
			}
		}
		if(found){
			return i;
		}
	}
	return -1;
}
