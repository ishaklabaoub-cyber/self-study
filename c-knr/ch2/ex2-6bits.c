#include <stdio.h>


unsigned setbits(unsigned x,int p,int n,unsigned y);

int main()
{
	unsigned x = 0xCA,y = 0xB5;
	int p = 4,n = 3;
	
	printf("%u\n",setbits(x,p,n,y));
	
	return 0;
}



unsigned setbits(unsigned x,int p,int n,unsigned y){
	int mask = (1 << n) - 1;
	unsigned rmb = y & mask; // right most bits of 'y'
	unsigned clear_mask = ~(mask << p);// to clear the bits in 'x' and use OR later to put the bits of 'y' 
	unsigned result = (x & clear_mask) | (rmb << p);
	return result;
}	
