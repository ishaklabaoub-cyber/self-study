#include <stdio.h>
#include <string.h>

int htoi(char* s);

int main(){
	char s[] = {"0x1A3F"};
	int result = htoi(s);
	
	if(result == -1){
		printf("\nINPUT ERROR!!\n");
	}else{
		printf("%d\n",result);
	}
	
		
	return 0;
}



int htoi(char* s){

	int result = 0,c = 0;

	if(s[0] != '0' && (s[1] != 'x' || s[1] != 'X')){
		return -1;
	}
	
	for(int i = 2;s[i] != '\0';i++){
		if(s[i] >= '0' && s[i] <= '9'){
			c = s[i] - '0';
		}else if(s[i] >= 'a' && s[i] <= 'f'){
			c = s[i] - 'a' + 10;
		}else if(s[i] >= 'A' && s[i] <= 'F'){
			c = s[i] - 'A' + 10;
		}else{
			
		}

		result = result * 16 + c;
	}
	return result;	
}
