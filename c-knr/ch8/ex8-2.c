#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define PERMS 0666
#define OPEN_MAX 20

#define getc1(p) (--(p)->cnt >= 0 ? (unsigned char)*(p)->ptr++ : _fillbuf(p))

typedef struct _iobuf{
    int cnt;
    char *ptr;
    char *base;
    struct {
        unsigned read  : 1;
        unsigned write : 1;
        unsigned unbuf : 1;
        unsigned eof   : 1;
        unsigned err   : 1;
    } flags;
    int fd;
} FILE1;
static FILE1 _iob[OPEN_MAX] = {
    {0, (char *) 0, (char *) 0, {1,0,0,0,0}, 0},
    {0, (char *) 0, (char *) 0, {0,1,0,0,0}, 1},
    {0, (char *) 0, (char *) 0, {0,1,1,0,0}, 2},

};

FILE1 *fopen1(char *, char *);

int main()
{
    return 0;
}


FILE1 *fopen1(char *name, char *mode){
    int fd;
    FILE1 *fp;


    if(*mode != 'w' && *mode != 'r' && *mode != 'a')
        return NULL;

    for(fp = _iob;fp < _iob + OPEN_MAX;fp++)
        if(!fp->flags.read && !fp->flags.write)
            break;      /* found free slot */
    if(fp >= _iob + OPEN_MAX)       /* no free slots */
            return NULL;

    if(*mode == 'w'){
        fd = creat(name, PERMS);
    } else if(*mode == 'a'){
        if( (fd = open(name, O_WRONLY, 0) ) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    } else{
        fd = open(name, O_RDONLY, 0);
    }

    if(fd == -1)
        return NULL;
    
    fp->fd   = fd;
    fp->cnt  = 0;
    fp->base = NULL;
    fp->flags.read  = (*mode == 'r');
    fp->flags.write = (*mode != 'r');
    return fp;
}


int _fillbuf(FILE1 *fp){
    int bufsize;
    
    if( !fp->flags.read || (fp->flags.err || fp->flags.eof) )
        return EOF;        

    bufsize = (fp->flags.unbuf) ? 1 : BUFSIZ;

    if(fp->base == NULL)
        if((fp->base = (char *) malloc(bufsize)) == NULL)
            return EOF;
        
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if(--fp->cnt < 0){
        if(fp->cnt == -1){
            fp->flags.eof = 1;
        } else{
            fp->flags.err = 1;
        }
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char) *fp->ptr++;
}
