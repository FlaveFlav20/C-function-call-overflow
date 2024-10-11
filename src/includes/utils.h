#ifndef UTILS
#define UTILS

#include <stdio.h>
#include <stdbool.h>

#define DEFAULT_SIZE_UTILS_BUFFER 32

struct Buffer {
    char *buff;
    size_t curr_size;
    size_t size;
};

struct Buffer *init_buffer(void);

bool increase_size(struct Buffer *buffer);

bool add_buffer(struct Buffer *buffer, char *element, size_t size);

void free_buffer(struct Buffer **buffer);

#endif // UTILS