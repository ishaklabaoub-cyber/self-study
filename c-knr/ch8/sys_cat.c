#include <stdio.h>
#include <unistd.h>

#define BUFSIZE 1024

int main(int argc,char *argv[])
{
    char buf[BUFSIZE];
    ssize_t n = 0;
    if(argc == 1){
        while((n = read(0, buf, n))){
            write(1, buf, n);            
        }
    }

    return 0;
}
