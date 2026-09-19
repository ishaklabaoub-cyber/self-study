#include <stdio.h>
#include <stdlib.h>

void display_files(char *path, int filenbr);


int main(int argc, char *argv[])
{
    char *lineptr = NULL;
    size_t n = 0;
    int filenbr;
    char *path;
    if(argc == 1){

        while(getline(&lineptr, &n, stdin) > 0){
            printf("%s", lineptr);
        }
        free(lineptr);
    } else if(argc > 1){
        
        filenbr = argc - 1;
        
        for(int i = 0;i < argc -1; i++){
            path = argv[1 + i];
            display_files(path, filenbr);
        }
    }

    return 0;
}


void display_files(char *path, int filenbr){
    FILE *fp;
    char *lineptr = NULL;
    size_t n = 0;

    fp = fopen(path, "r");
    if(fp == NULL){
        perror("fopen");
        return;
    }
    
    if(filenbr > 1){
        printf("%s:\n", path);
    }
    
    while(getline(&lineptr, &n, fp) > 0){
        printf("%s",lineptr);
    }
    
    free(lineptr);
    fclose(fp);
}
