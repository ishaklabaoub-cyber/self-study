#include <stdio.h>
#define swap(t,x,y) {t temp = x;x = y;y = temp;}



int main()
{
	int a = 4,b = 5;
	printf("Before: a = %d , b = %d\n",a,b);
	swap(int,a,b);
	printf("After: a = %d , b = %d\n",a,b); 
	return 0;
}
