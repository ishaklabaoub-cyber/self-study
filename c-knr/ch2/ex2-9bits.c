#include <stdio.h>


int bitcount(unsigned x); //Number of 1's in a number 

int main()
{
	unsigned x = 10;

	int count = bitcount(x);
	
	printf("%d",count);

	return 0;
}


int bitcount(unsigned x){
	int count = 0;

	while(x != 0){
		x &= (x-1);
		count++;
	}
	return count;
}
