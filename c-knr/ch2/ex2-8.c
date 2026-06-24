#include <stdio.h>


unsigned rightrot(unsigned x,int n);

int main()
{	
	int n = 0;
	unsigned x = 10;
	printf("how many do you want to rotate: ");
	scanf("%d",&n);
	unsigned result = rightrot(x,n);

	printf("The result is: %u\n",result);
	return 0;
}


unsigned rightrot(unsigned x,int n){
    int wordlength = sizeof(x) * 8;
    n = n % wordlength;
    return (x >> n) | (x << (wordlength - n));
}
