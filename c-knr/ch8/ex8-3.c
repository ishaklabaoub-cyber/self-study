#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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

int _flushbuf(int c, FILE1 *fp)
{   
    int    num_written, bufsize;
    size_t character_written;
    unsigned char uc = c;

    if(fp->base == NULL && !fp->flags.unbuf){
        if((fp->base = (char *) malloc(BUFSIZ)) == NULL){
            fp->flags.unbuf = 1;        // failed to allocate
            return EOF;
        } else{
            // resetting
            fp->ptr = fp->base;
            fp->cnt = BUFSIZ - 1;
        }
    }

    if(!fp->flags.write || fp->flags.err || fp->flags.eof)      /* can't write to this fd */
        return EOF;

    if(fp->flags.unbuf){
        // unbuffered writing
        fp->ptr = fp->base = NULL;
        fp->cnt = 0;
        if(c == EOF)
            return EOF;
        if((num_written = write(fp->fd, &uc, 1)) == -1){
            perror("write");
            return EOF;
        }
        character_written = 1;      
        bufsize = 1;
    } else{
        character_written = fp->ptr - fp->base;
        if((num_written = write(fp->fd, fp->base, character_written)) == -1){
            perror("write");
            return EOF;
         }
        fp->ptr  = fp->base;
        *fp->ptr = c;
        fp->ptr++;
        fp->cnt = BUFSIZ - 1;
    }

    if((size_t)num_written == character_written){
        return c;
    } else {
        fp->flags.err = 1;
        return EOF;
    }
}

int fflush1(FILE1 *fp)
{
    int num_written;
    size_t character_written;
    
    if(!fp->flags.write || fp->flags.err || fp->flags.eof)
        return EOF;
    
    if(fp->base == NULL && !fp->flags.unbuf){
        if((fp->base = (char *) malloc(BUFSIZ)) == NULL){
            fp->flags.unbuf = 1;
            return EOF;
        } else{
            fp->ptr = fp->base;
            fp->cnt = BUFSIZ - 1;
        }
    }
    
    character_written = fp->ptr - fp->base;
         
    if((num_written = write(fp->fd, fp->base, character_written)) == -1){
        perror("write");
        return EOF;
    }
    fp->ptr = fp->base;
    fp->cnt = BUFSIZ - 1;
    
    if((size_t)num_written == character_written){
        return 0;
    } else{
        return EOF;
    }
}

int fclose1(FILE1 *fp)
{
    if(fflush1(fp) == EOF)
        return EOF;
    fp->flags.write = 0;
    fp->flags.read = 0;
    
    free(fp->base);
    
    if(close(fp->fd) != 0){
        perror("close");
        return EOF;
    }
    return 0;
}

int main()
{
    return 0;
}


