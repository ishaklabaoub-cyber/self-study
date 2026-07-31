#include <stdio.h>

void strcat1(char[],char[]);

int main()
{
	char s1[50] = "hello";
	char s2[20] = " world";

	strcat1(s1,s2);

	printf("\n%s\n",s1);
	return 0;
}

void strcat1(char s[], char t[])
{
    while (*s != '\0')     /* find end of s */
       	s++;
    while ((*(s++) = *(t++)) != '\0'){  /* copy t */
        ;
    }
}

