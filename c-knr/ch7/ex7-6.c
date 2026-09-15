#include <stdio.h>
#include <string.h>

#define MAX_LENGTH 100

char *fcmp(char *path1,char *path2);

int main(int argc,char **argv)
{

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
    char s1[MAX_LENGTH], s2[MAX_LENGTH];
    char *ret;
    fp1 = fopen(path1, "r");    
    fp2 = fopen(path2, "r");
    
    if(fp1 == NULL || fp2 == NULL){
        perror("fopen");
        return NULL;
    }
    
    while(fgets(s1, MAX_LENGTH, fp1) != NULL && fgets(s2, MAX_LENGTH, fp2) != NULL){
       
        if(strcmp(s1, s2) == 0){
            continue;   // if they match fetch another two lines
        } else{
            ret = strdup(s1);
            return ret;    // different lines
        }
    }

    fclose(fp1);
    fclose(fp2);
    return NULL;    // there is no difference
}
