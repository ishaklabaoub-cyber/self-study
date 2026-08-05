#include <stdio.h>
#include <stdlib.h>
//#define TABSTOP 8

int main(int argc, char **argv)
{
	int c,i,that_stop = 0;
	int spaces = 0,column_c = 0;
	int tabstop[100] = {8 , 16 ,  24};
	int ntabs = 3;
	if(argc > 1){
		ntabs = argc - 1;
	}	

	if(argc > 1){
		i = 0;
		for(;argc > 1;argc--){
			tabstop[i] = atoi(argv[i + 1]);
			++i;
		}

	}
	while( (c = getchar()) != EOF){
		if(c == '\t'){
			/* stop search loop */
			for(i = 0;i < ntabs;i++){
				if(tabstop[i] > column_c){
					that_stop = tabstop[i];
					break;
				}
			}
			if(that_stop == 0){
				that_stop = tabstop[ntabs];
				while(that_stop < column_c){
					that_stop += tabstop[0];
				}
			}
			spaces = that_stop - column_c;
		
			for(int i = 0;i < spaces;i++){
				putchar(' ');
			}
			column_c += spaces;
			that_stop = 0;
		 }else {
			putchar(c);
			if(c == '\n'){
				column_c = 0;
			}else{
				++column_c;
			}
		}
	}
	return 0;
}
