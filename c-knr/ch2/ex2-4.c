#include <stdio.h>

void squeez(char* s1,char* s2);


int main()
{
	char s1[] = {"hello"};
	char s2[] = {"lo"};

	squeez(s1,s2);

	printf("%s\n",s1);
	return 0;
}





void squeez(char* s1,char* s2){	
	int i,j,h = 0;
	for(i = 0;s1[i] != '\0';i++){
		int found = 0;
		for(j = 0;s2[j] != '\0';j++){
			if(s2[j] == s1[i]){
				found = 1;
				break;
			}
		}	
		if(!found){
			s1[h++] = s1[i];
		}
	}
		s1[h] = '\0';

}
