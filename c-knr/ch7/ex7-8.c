#include <stdio.h>

#define MAX_LINES  20


int main(int argc, char **argv)
{
    FILE   *fp;
    int    page_count, lineno;
    char   *lineptr = NULL; 
    char   *path;
    size_t n = 0;

    if(argc == 1){
        printf("Too few arguments.\n");
        printf("Usage: %s <filename1> <filename2> ...", argv[0]);
    } else if(argc > 1){
        for(int i = 0;i < argc-1;i++){
           
            path = argv[1 + i];
            
            fp = fopen(path, "r"); 
            if(fp == NULL){
                perror("fopen");
                return 1;
            }

            lineno     = 0;             /* reset for every new file*/
            page_count = 1;                   
            
            printf("%s\t\t\t Page %d\n", path, page_count);
            
            
            while(getline(&lineptr, &n, fp) > 0){
                lineno++;
              
                if(lineno == MAX_LINES){
                
                    lineno = 0;
                    page_count++;
                    printf("%s\t\t\t Page %d\n", path, page_count);
                    printf("%s", lineptr);
                
                } else{
                    printf("%s", lineptr);
                }
            }
            fclose(fp);
        }
    }

    return 0;
}
