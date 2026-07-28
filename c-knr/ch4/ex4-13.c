#include <stdio.h>
#include <string.h>

void reverse(char s[], int l, int r);
int main()
{
	char s[6] = "hello";

	reverse(s ,0 ,strlen(s) - 1);

	printf("\n%s\n",s);
	return 0;
}



void reverse(char s[],int l,int r){
	char temp;
	if(l >= r){
		return;
	}else{
		temp = s[l];
		s[l] = s[r];
		s[r] = temp;
		reverse(s,l+1,r-1);
	}
}
