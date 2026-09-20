#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

#define PERMS 0666


int main()
{
    return 0;
}


FILE *fopen(char *name, char *mode){
    int fd;
    FILE *fp;


    if(*mode != 'w' && *mode != 'r' && *mode != 'a')
        return NULL;

    for(fp = _iob;fp < _iob + OPEN_MAX)
        if(fp->flag.read || fp->flag.write)
            break;      /* found free slot */
    if(fp >= _iob + OPEN_MAX)       /* no free slots */
            return NULL;

    if(*mode == 'w'){
        fd = creat(name, PERMS);
    } else if(*mode == 'a'){
        if( (fd = open(name, O_WONLY, 0) ) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else{
        fd = open(name, _RONLY, 0);
    }

    if(fd == -1)
        return NULL;
    
    fp->fd   = fd;
    fp->cnt  = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}
