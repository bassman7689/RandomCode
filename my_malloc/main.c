#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

struct header {
    size_t size;
    struct header *next;
    int free;
    int magic; // For debugging only. TODO: remove this in non-debug mode.
};

typedef struct header header_t;

#define META_SIZE sizeof(header_t)

void *global_base = NULL;

header_t *find_free_block(header_t **last, size_t size) {
    header_t *current = global_base;
    while (current && !(current->free && current->size >= size)) {
        *last = current;
        current = current->next;
    }
    return current;
}

header_t *request_space(header_t * last, size_t size) {
    header_t *block;
    block = sbrk(0);
    void *request = sbrk(size + META_SIZE);
    assert((void*)block == request);
    if (request == (void*) - 1) {
        return NULL;
    }

    if (last) {
        last->next = block;
    }
    block->size = size;
    block->next = NULL;
    block->free = 0;
    block->magic = 0x12345678;
    return block;
}

void *my_malloc(size_t size) {
    header_t *block;

    if (size <= 0) {
        return NULL;
    }

    if (!global_base) {
        block = request_space(NULL, size);
        if (!block) {
            return NULL;
        }
        global_base = block;
    } else {
        header_t *last = global_base;
        block = find_free_block(&last, size);
        if (!block) {
            block = request_space(last, size);
            if (!block) {
                return NULL;
            }
        } else {
            block->free = 0;
            block->magic = 0x77777777;
        }
    }

    return block+1;
}

header_t *get_header_pointer(void *ptr) {
    return (header_t *)ptr - 1;
}

void my_free(void *ptr) {
    if (!ptr) {
        return;
    }

    header_t* header_ptr = get_header_pointer(ptr);
    assert(header_ptr->free == 0);
    assert(header_ptr->magic == 0x77777777 || header_ptr->magic == 0x12345678);
    header_ptr->free = 1;
    header_ptr->magic = 0x55555555;
}

void *my_realloc(void *ptr, size_t size) {
    if (!ptr) {
        return my_malloc(size);
    }

    header_t *header_ptr = get_header_pointer(ptr);
    if (header_ptr->size >= size) {
        return ptr;
    }

    void *new_ptr;
    new_ptr = my_malloc(size);
    if (!new_ptr) {
        return NULL;
    }
    memcpy(new_ptr, ptr, header_ptr->size);
    my_free(ptr);
    return new_ptr;
}

int main(int argc, char* argv[]) {
    int *test[100000];
    for (int i = 0; i < 5000; i++) {
        for (int j = 0; i < 100000; i++) {
            test[i] = my_malloc(sizeof(int));
            *test[i] = i;
        }

        for (int j = 0; i < 100000; i++) {
            my_free(test[i]);
        }
    }
}
