#include <stdio.h>


unsigned invert(unsigned x, int p, int n);

int main()
{
	unsigned x = 0xCA;
	int p = 2,n = 3;

	printf("%u\n",invert(x,p,n));	

	return 0;
}



unsigned invert(unsigned x,int p,int n){
	unsigned mask = (1 << n) - 1;
	unsigned result = x ^ (mask << p);// XOR is the perfect choice for inversion 
	
	return result;
}
