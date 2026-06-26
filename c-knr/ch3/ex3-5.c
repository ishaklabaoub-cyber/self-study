#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse(char* s);
void itob(int n,char* s,int b);

int main()
{
	char s[200] = "";
	int n = 25;

	itob(n,s,16);

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
void itob(int n,char *s,int b){
	int i,sign;

	sign = n;

	i = 0;
	int rem = 0;
	do{
		rem = abs(n%b);
			if(rem >= 10){
				s[i++] = 'A' + (rem - 10); 
			}else{
				s[i++] = rem + '0';
			}
		
	}while((n /= b) != 0);

	if(sign < 0){
		s[i++] = '-';
	}

	s[i] = '\0';
	reverse(s);

}
