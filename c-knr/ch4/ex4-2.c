#include <stdio.h>
#include <ctype.h>

double atof(char* s);


int main(){
	char s[200] = "123.45e6";
	double n;
	n = atof(s);
	
	printf("\n%lf\n",n);
}


double atof(char* s){
	double val,power;
	int i,sign;
	int exp = 0,esign = 1;


	for(i = 0;isspace(s[i]);i++){
		;
	}

	sign = (s[i] == '-') ? -1 : 1;

	if(s[i] == '-' || s[i] == '+'){
		i++;
	}

	for(val = 0.0;isdigit(s[i]);i++){
		val = 10 * val + (s[i] - '0');
	}
	if(s[i] == '.'){
		i++;
	}
	for(power = 1.0;isdigit(s[i]);i++){
		val = 10 * val + (s[i] - '0');
		power *= 10;
	}
	if(s[i] == 'e' || s[i] == 'E'){
		i++;
		esign = (s[i] == '-') ? -1 : 1;
		i++;
		while(isdigit(s[i])){
			exp = 10 * exp + (s[i++] - '0');
		}
		while(exp-- != 0){
			if(esign < 0){
				power *= 10;
			}else{
				power /= 10;
			}
		}
	}
	return sign * val / power;
}
