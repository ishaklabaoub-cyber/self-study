#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>


#define NALLOC 1024        /* minimum #units to requeste */
#define MAX_CAP 6400000    /* maximum capacity to request */

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
void free1(void* ap);
int  bfree(char *p, unsigned n    );
static void init_list(void);


int main()
{
        
    return 0;
}
static void init_list(void)
{
    freep = base.s.ptr = &base; 
    base.s.size = 0;
}

void free1(void *ap)
{
    Header *bp, *p;
    if(ap == NULL){
        fprintf(stderr, "free1: pointer passed is null.\n");
        return;
    } else if(freep == NULL){       /* nothing gets allocated */
        fprintf(stderr, "free1: nothing gets allocated.\n");
        return;
    }
    bp = (Header *)ap - 1;    /* point to block header */
    
    if(bp->s.size >= MAX_CAP || bp->s.size == 0){
        fprintf(stderr, "free1: pointer passed to free1 its size is invalid.\n");
        return;
    }
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;  /* freed block at start or end of arena */

    if (bp + bp->s.size == p->s.ptr) {  /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    } else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp) {          /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
    freep = p;
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
    free1((void *) (up+1));
    return freep;
}

void *malloc1(unsigned nbytes) {
    Header *p, *prevp;
    unsigned nunits;
    if(nbytes == 0)
        return NULL;

    nunits = (nbytes+sizeof(Header)-1) / sizeof(Header) + 1;
        if(nunits >= MAX_CAP)
            return NULL;        /* invalid size to request */
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
            freep = prevp;
            return (void *) (p+1);
        }
        if(p == freep){
            if((p = morecore(nunits)) == NULL)
                return NULL;            /* none left */
        }
    }

}
int bfree(char*p, unsigned n)
{
    if(n == 0)
        return 1;
    if(p == NULL)
        return 1;
    if(freep == NULL)
        init_list();

    uintptr_t align = (uintptr_t )p % sizeof(Header);
    if(align != 0){
        p += (sizeof(Header) - align);
        
        if(n < align){
            return 1;
        } else{
            n -= (sizeof(Header) - align);
        }
    }
    int units = n / sizeof(Header);
    if(units < 2){              
        fprintf(stderr, "bfree: not enough units to be freed.\n");
        return 1;
    }

    Header *start;          /* initialize the start of the block */
    start = (Header *) p;
    start->s.size = units;

    free1((void *) (start + 1));    /* add it to the free list */

    return 0;
}
