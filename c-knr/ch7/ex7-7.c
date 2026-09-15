#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LENGTH 100

int file_find_pattern(char *path, char* pattern);
int input_find_pattern(char *pattern);


int main(int argc,char **argv)
{
    char *pattern;
    char *path; 

    if(argc == 1){
    
        printf("Too few arguments.\n");
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
    
    } else if(argc == 2){
        
        pattern = argv[1];
        if(input_find_pattern(pattern) == 0){
            printf("\npattern not found.\n");
        }

    } else if(argc > 2){
        pattern  = argv[1];
        path = argv[2];
        if(file_find_pattern( path, pattern) == 0){
            printf("pattern not found.\n");
        }
    }

    return 0;
}

int file_find_pattern(char *path, char* pattern){
    FILE *fp;
    char *lineptr[MAX_LENGTH];
    size_t n = MAX_LENGTH;
    long lineno = 0;
    int  found = 0;

    fp = fopen(path, "r");
    if(fp == NULL){
        perror("fopen");
        return -1;
    }

    while(getline(lineptr, &n, fp) > 0){
            lineno++;
            if(strstr(*lineptr, pattern) != NULL){
                found++;
                printf("%ld: ", lineno);
                printf("%s", *lineptr);
            }
    }
    return found;
}

int input_find_pattern(char *pattern){
    char *lineptr[MAX_LENGTH];
    size_t n = MAX_LENGTH;
    int found = 0;
    long lineno = 0;

    while(getline(lineptr, &n, stdin) > 0){
        lineno++;        
       
        if(strstr(*lineptr, pattern) != NULL){
            found++;
            printf("%ld: ", lineno);
            printf("%s", *lineptr);
        }
    }
    return found;
}
