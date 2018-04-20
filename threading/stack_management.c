#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/resource.h>
#define NTHREADS 4
#define N 1000
#define ALIGN_TO_SIZE(stack, size) ((stack) + ((size) - (stack) % (size)))
#define ALIGN_TO_4K(stack) ALIGN_TO_SIZE(stack, 4096)

pthread_attr_t* attr;

void *dowork(void *threadId)
{
    double A[N][N];
    int i, j;
    long tid;
    size_t ss;

    tid = (long)threadId;
    pthread_attr_getstacksize(attr, &ss);
    printf("Thread %ld: stack size %li\n", tid, ss);
    for(i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i][j] = ((i*j)/3.452) + (N-i);
        }
    }
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NTHREADS];
    int rc;
    long t;
    size_t currentStackSize;
    size_t newStackSize;

    attr = malloc(sizeof(pthread_attr_t));

    rc = 0;
    rc = pthread_attr_init(attr);
    if (rc != 0) {
        perror("attr_init");
        exit(1);
    }

    newStackSize = ALIGN_TO_4K(PTHREAD_STACK_MIN + (sizeof(double) * N * N));

    printf("New stack size for threads: %li\n", newStackSize);

    rc = 0;
    rc = pthread_attr_setstacksize(attr, newStackSize);
    if (rc != 0) {
        printf("Return code for attr_setstack = %d\n", rc);
        perror("attr_setstacksize");
        exit(1);
    } 

    rc = 0;
    for(t=0; t<NTHREADS; t++){
        rc = pthread_create(&threads[t], attr, dowork, (void *)t);
        if (rc){
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(1);
        }
    }
    printf("Created %ld threads.\n", t);
    pthread_exit(NULL);
    free(attr);
}
