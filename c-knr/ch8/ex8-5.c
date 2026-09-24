#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_PATH 1024

void dirwalk(char *, void (*fnc)(char *));
void fsize(char *name);


int main(int argc, char *argv[])
{
    
}

void fsize(char *name)
{
    struct stat stbuf;

    if(stat(name , &stbuf) == -1){
        fprintf(stderr,"fsize: can't access %s", name);
        return;
    }
    if((stbuf.st_mode & S_IFMT) == S_IFDIR){
        dirwalk( name, fsize);
    }
    printf("%8d %8d %8ld %ld %s\n", stbuf.st_gid, stbuf.st_uid, stbuf.st_size, (long)stbuf.st_ctim, name);

}
void dirwalk(char *dir, void (*fnc)(char *))
{
    char name[MAX_PATH];
    struct dirent *dp;
    DIR *dfd;

    if((dfd = opendir(dir)) == NULL){
        fprintf(stderr, "opendir: can't access %s", dir);
        return ;
    }
    while((dp = readdir(dfd)) != NULL){
        if(strcmp(dp->d_name, ".") == 0
           || strcmp(dp->d_name, "..") ==0){
            continue;       // skip self and parent
        }
        if(strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name)){
            fprintf(stderr,"dirwalk: name %s %s too long", dir, dp->d_name);
            return;
        } else{
            sprintf(name,"%s/%s",dir,dp->d_name);
            (*fnc)(name);
        }

    }
    if(closedir(dfd) == -1){
        perror("closedir");
        return;
    }
}
