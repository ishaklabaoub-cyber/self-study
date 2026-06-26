#include <stdio.h>
#include <ctype.h>


void expand(char* s1,char* s2);

int main()
{	
	char s1[200] = {"Hello w-z- 0-9 H-z"};
	char s2[200] = "";

	expand(s1,s2);

	printf("\n%s\n",s2);

	return 0;
}



void expand(char *s1,char* s2){
	int i,j = 0;

	for(i = 0;s1[i] != '\0';i++){
		if(s1[i+1] == '-' && s1[i] <= s1[i+2] &&
		   ((s1[i] >= 'a' && s1[i+2] <= 'z')||
   		   (s1[i] >= 'A' && s1[i+2] <= 'Z')||
		   (s1[i] >= '0' && s1[i+2] <= '9'))){
			for(char c = s1[i];c <= s1[i + 2];c++){
				s2[j++] = c;
			
			}
			i += 2;	
		}else{
			s2[j++] = s1[i];
		}
	}
	s2[j] = '\0';

}
