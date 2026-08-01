#include <stdio.h>

void strncpy1(char[],char[],int);
void strncat1(char[],char[],int);
int  strncmp1(char[],char[],int);

int main()
{
	int n = 4;
	char s1[12] = "hello";
	char s2[7] = "he";
		
	int result = strncmp1(s1,s2,n);

	printf("\n%d\n",result);

	return 0;
}

void strncpy1(char s[],char t[],int n){
	/*for(;(*s = *t) != '\0' && --n;s++,t++)  // FOR Loop version
		;*/ 
	while((*s = *t) != '\0' && --n){	// WHILE Loop version
		s++;
		t++;
	}
	
	if(n > 0){
		*s = '\0';
	}
}


void strncat1(char s[], char t[],int n)
{
    while (*s != '\0')     /* find end of s */
       	s++;
    while ((*(s++) = *(t++)) != '\0' && --n)  /* copy t */
       		;
  
}

int  strncmp1(char s[],char t[],int n){
	while( (*s == *t) && *s != '\0'  && --n){
		s++;
		t++;	
	}
	
	return (n == 0) ? 0 : *s - *t;

}

