#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

void itoa(int n);

int main()
{
	int n = INT_MIN;

	itoa(n);
	return 0;
}

void itoahelper(int n){
	if(n / 10)
		itoahelper(n / 10);
	putchar(abs(n % 10) + '0'); 
}
/* itoa: convert n to characters*/
void itoa(int n)
{
	if(n < 0){
		putchar('-');
	}
	itoahelper(n); 
}
