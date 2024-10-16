#include "includes/utils.h"

#include <stdlib.h>

struct Buffer *init_buffer(void)
{
    struct Buffer *res = malloc(sizeof(struct Buffer));
    if (!res)
        return NULL;
    
    res->buff = calloc(DEFAULT_SIZE_UTILS_BUFFER, sizeof(char));

    if (!res->buff)
    {
        free(res);
        return NULL;
    }

    res->size = DEFAULT_SIZE_UTILS_BUFFER;
    res->curr_size = 0;
    return res;
}

bool increase_size(struct Buffer *buffer)
{
    if (!buffer || !buffer->buff)
        return false;
    
    buffer->buff = realloc(buffer->buff, 2 * buffer->size + 1);
    if (!buffer->buff)
    {
        free(buffer);
        return false;
    }
    
    buffer->size *= 2;
    return true;
}

bool add_buffer(struct Buffer *buffer, char *element, size_t size)
{
    if (!buffer || !buffer->buff)
        return false;
    while (buffer->size < buffer->curr_size + size)
    {
        if (!increase_size(buffer))
        {
            return false;
        }
    }
    for (size_t i = buffer->curr_size; i < buffer->curr_size + size; i++)
    {
        buffer->buff[i] = element[i - buffer->curr_size];
    }
    buffer->curr_size += size;
    return true;
}

void free_buffer(struct Buffer **buffer)
{
    if (!buffer || !(*buffer))
        return;
    if ((*buffer)->buff)
    {
        free((*buffer)->buff);
    }
    free(*buffer);
    *buffer = NULL;
}

size_t str_to_size_t(char *str)
{
    size_t value = 0;
    for (size_t i = 0; i < strlen(str); i++)
    {   
        value *= 10;
        value += str[i] - '0';
    }
    return value;
}