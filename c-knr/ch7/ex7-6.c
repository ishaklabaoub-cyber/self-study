#include <stdio.h>

#define MAX_LENGTH 100

char *fcmp(char *path1,char *path2);

int main(int argc,char **argv)
{
    //FILE *fp1, *fp2;

    if(argc == 1){      // there is no arguments
        printf("No files given to compare\n");
        printf("Usage: %s <filename1.txt> <filename2.txt>\n", argv[0]);
        return 1;
    } else if(argc > 2){
    
        char *str;
        if(( str = fcmp(argv[1], argv[2]) ) == NULL){
            printf("There is no different between the files\n");
        } else{
            printf("Here's the different line: %s\n", str);
        }
    
    } else{
        printf("Too few arguments\n");
        printf("Usage: %s <filename1.txt> <filename2.txt>\n", argv[0]);
        return 1;
    }

    return 0;
}

char *fcmp(char *path1,char *path2){
    FILE *fp1, *fp2;

    
}
