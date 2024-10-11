#ifndef UTILS
#define UTILS

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

size_t str_to_size_t(char *str);

#endif // UTILS