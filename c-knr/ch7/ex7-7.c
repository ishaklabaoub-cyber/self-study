#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int file_find_pattern(char *path, char* pattern, int file_nbr);
int input_find_pattern(char *pattern);


int main(int argc,char **argv)
{
    char *pattern;
    char *path; 
    int i, filenbr;

    if(argc == 1){
    
        printf("Too few arguments.\n");
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
    
    } else if(argc == 2){
        
        pattern = argv[1];
        if(input_find_pattern(pattern) == 0){
            printf("\npattern not found.\n");
        }

    } else if(argc > 2){
        filenbr = argc - 2;
        pattern  = argv[1];
        i = 0;
        while(argc-- > 2){
            path = argv[2 + i];
            if(file_find_pattern( path, pattern, filenbr) == 0){
                printf("pattern not found.\n");
            }
            i++;
        }
    }

    return 0;
}

int file_find_pattern(char *path, char* pattern, int file_nbr){
    FILE *fp;
    char *lineptr;
    size_t n = 0;
    long lineno = 0;
    int  found = 0;

    fp = fopen(path, "r");
    if(fp == NULL){
        perror("fopen");
        return -1;
    }
    if(file_nbr > 1)
        printf("%s:\n", path);
    while(getline(&lineptr, &n, fp) > 0){
            lineno++;
            if(strstr(lineptr, pattern) != NULL){
                found++;
                printf("%ld: ", lineno);
                printf("%s", lineptr);
            }
    }
    return found;
}

int input_find_pattern(char *pattern){
    char *lineptr;
    size_t n = 0;
    int found = 0;
    long lineno = 0;

    while(getline(&lineptr, &n, stdin) > 0){
        lineno++;        
       
        if(strstr(lineptr, pattern) != NULL){
            found++;
            printf("%ld: ", lineno);
            printf("%s", lineptr);
        }
    }
    return found;
}
