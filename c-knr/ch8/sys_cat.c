#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

#define BUFSIZE 1024

void read_file(char *path, int filenbr);

int main(int argc,char *argv[])
{
    char buf[BUFSIZE];
    int n, filenbr;
    char *path;

    if(argc == 1){
        while((n = read(0, buf, BUFSIZE)) > 0){
            if(write(1, buf, n) != n)
                perror("write");
        }
    } else if(argc > 1){

        filenbr = argc - 1;
        
        for(int i = 0;i < argc - 1;i++){
            path = argv[i + 1];
            read_file(path, filenbr);
        }
    
    }

    return 0;
}

void read_file(char *path, int filenbr){
    int  fd, n;
    char buf[BUFSIZE];
    
    fd = open(path, O_RDONLY, 0);
    if(fd == -1){
        perror("open");
        return ;
    }
    
    if(filenbr > 1)
        printf("%s:\n", path);

    while ((n = read(fd, buf, BUFSIZE)) > 0){
        if(write(1, buf, n) != n)
            perror("write");
    }
}
