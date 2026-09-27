#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


#define NALLOC 1024     /* minimum #units to requeste */


typedef long Align;

union header{
    struct{
        union header *ptr;      /* next block if in a free list */ 
        unsigned size;          /* size of this block */
    }s;
    Align x;            /* force alignement of blocks */
};

typedef union header Header;

static Header base;             /* empty list to get started */
static Header *freep = NULL;    /* staht of free list */

void *malloc1(unsigned nbytes);
static Header *morecore(unsigned nu);
void *calloc1(unsigned nobj, unsigned size);

int main()
{
        
    return 0;
}

static Header *morecore(unsigned nu) {
    char *cp;
    Header *up;

    if(nu < NALLOC)
        nu = NALLOC;

    cp = sbrk(nu * sizeof(Header));
    if(cp == (char *) -1)
        return NULL;
    up = (Header *) cp;
    up->s.size = nu;
    free((void *) (up+1));
    return freep;
}

void *malloc1(unsigned nbytes) {
    Header *p, *prevp;
    unsigned nunits;
    
    nunits = (nbytes+sizeof(Header)-1) / sizeof(Header) + 1;
    
    if((prevp = freep) == NULL){
        base.s.ptr = freep  = prevp = &base;
        base.s.size = 0;
    }


    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
        if(p->s.size >= nunits){        /* big enough */
            if(p->s.size == nunits)     /* exactly */
                prevp->s.ptr = p->s.ptr;
            else {          /* split the block */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = p;
            return (void *)p+1;
        }
        if(p == freep){
            if((p = morecore(nunits)) == NULL)
                return NULL;            /* none left */
        }
    }

}

void *calloc1(unsigned nobj, unsigned size) {
    
    char *p;
    unsigned total = nobj * size;
    p = malloc1(total);

    if(p != NULL)
        memset(p, 0, total);

    return p;
}
