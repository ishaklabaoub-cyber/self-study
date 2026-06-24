#include <stdio.h>


int main()
{
	float f = 0;
	double d = 0;
	unsigned int i = 0;
	short int s = 0;


	printf("float size: %ld\n",sizeof(f));
	printf("double size: %ld\n",sizeof(d));
	printf("unsigned integer size: %ld\n",sizeof(i));
	printf("short integer size: %ld",sizeof(s));
	return 0;
}
