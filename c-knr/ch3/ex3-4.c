#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void reverse(char* s);
void itoa(int n,char s[]);

int main()
{
	char s[200] = "";
	int n = INT_MIN;

	itoa(n,s);

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


/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
	int i, sign;
	sign = n;
	i = 0;
	do {/* generate digits in reverse order */
			s[i++] = abs(n % 10) + '0'; /* get next digit */

	}while ((n /= 10) != 0);
 		/* delete it */
	if (sign < 0){
		s[i++] = '-';
	}
	s[i] = '\0';
	reverse(s);
}
