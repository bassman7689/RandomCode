#include "malloc_freelist.h"
#include <memory.h>
#include <stdio.h>

typedef struct mytype {
    int x;
    int y;
    int width;
    int height;
} mytype;

#define MALLOC_SIZE (4 * 1024 * 1024)

int main(int argc, char** argv)
{
    void * my_block = malloc(MALLOC_SIZE); // for host system demonstration, alloc 4MB block

    printf("Allocated a block on the host, pointer: %p, size: %d\n", my_block, MALLOC_SIZE);

    // Initialize our simple freelist with the space.
    // On our embedded platform, this will be the RAM address for your pool and the size you desire.
    malloc_addblock(my_block, MALLOC_SIZE);

    void * t1 = fl_malloc(100);
    printf("Malloc'd from free list: %p\n", t1);

    void * t2 = fl_malloc(4 * 1024);
    printf("Molloc'd from free list: %p\n", t2);

    printf("Putting first pointer back into the pool\n");
    fl_free(t1), t1 = NULL;

    printf("Alloc'ing same size as first pointer\n");
    t1 = fl_malloc(100);

    printf("Malloc'd from free list: %p\n", t1);

    printf("Free'ing %p\n", t2);
    fl_free(t2), t2 = NULL;
    printf("Free'ing %p\n", t1);
    fl_free(t1), t1 = NULL;

    mytype *test = fl_malloc(sizeof(mytype));
    printf("Alloc'ing custom struct at pointer:%p\n", test);

    fl_free(test), test = NULL;

    printf("Free'ing memory block: %p\n", my_block);
    free(my_block);
}
