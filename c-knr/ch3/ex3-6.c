#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char* s);
void itoa(int n,char* s,int fw);


int main()
{
	char s[200] = "";
	int n = 1;

	itoa(n,s,6);

	printf("\n%s\n",s);

	return 0;
}

void reverse(char* s) {

    // Initialize l and r pointers
    int l = 0;
    int r = strlen(s) - 1;
    char t;

    // Swap characters till l and r meet
    while (l < r) {

        // Swap characters
        t = s[l];
        s[l] = s[r];
        s[r] = t;

        // Move pointers towards each other
        l++;
        r--;
    }
}

void itoa(int n,char* s,int fw){
	int i,sign;

	sign = n;
	i = 0;

	do{
		s[i++] = abs(n % 10) + '0';
	}while((n /= 10) != 0);

	if(sign < 0){
		s[i++] = '-';
	}
	if(i < fw){
		for(int j = i;j < fw;j++){
			s[i++] = ' ';
		}
	}
	s[i] = '\0';
	reverse(s);
}
