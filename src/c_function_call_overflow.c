#include "includes/c_function_call_overflow.h"
#include "includes/utils.h"

#include <string.h>

char alphabet[] = "abcdefghjklmnpqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
size_t alphabet_len = 51;

static size_t find_index(char c)
{
    for (size_t i = 0; i < alphabet_len; i++)
    {
        if (alphabet[i] == c)
            return i;
    }
    return -1;
}

static void increment(struct Buffer * buffer)
{
    if ((buffer->buff[buffer->curr_size - 1] == alphabet[alphabet_len - 1]) && buffer->curr_size == 1)
    {
        buffer->buff[buffer->curr_size - 1] = 'a';
        add_buffer(buffer, "a", 1);
    }
    else if ((buffer->buff[buffer->curr_size - 1] == alphabet[alphabet_len - 1]) && buffer->curr_size > 1 
            && (buffer->buff[buffer->curr_size - 2] == alphabet[alphabet_len - 1]))
    {
        buffer->buff[buffer->curr_size - 1] = 'a';
        add_buffer(buffer, "a", 1);
    }
    else if ((buffer->buff[buffer->curr_size - 1] == alphabet[alphabet_len - 1]) && buffer->curr_size > 1 
            && (buffer->buff[buffer->curr_size - 2] != alphabet[alphabet_len - 1]))
    {
        buffer->buff[buffer->curr_size - 1] = 'a';
        buffer->buff[buffer->curr_size - 2] = alphabet[find_index(buffer->buff[buffer->curr_size - 2]) + 1];
    }
    else
    {
        buffer->buff[buffer->curr_size - 1] = alphabet[find_index(buffer->buff[buffer->curr_size - 1]) + 1];
    }
}

static struct Buffer *get_fct_arg(size_t number_args, struct Buffer *res, struct Buffer *arg)
{
    add_buffer(arg, "a", 1);
    add_buffer(res, FCT_BEGIN, sizeof(FCT_BEGIN) / sizeof(char) - 1);

    for (size_t i = 0; i < number_args; i++)
    {
        add_buffer(res, TYPE_ARGS, sizeof(TYPE_ARGS) / sizeof(char) - 1);
        add_buffer(res, arg->buff, arg->curr_size);
        add_buffer(res, ",", 1);

        increment(arg);
    }
    res->curr_size--;
    add_buffer(res, FCT_END, sizeof(FCT_END) / sizeof(char) - 1);
    add_buffer(res, "\n", 1);
    return res;
}

static struct Buffer *get_fct_return(size_t number_args, struct Buffer *res, struct Buffer *arg)
{
    struct Buffer *arg_res = init_buffer();
    if (!arg_res)
    {
        free_buffer(&arg);
        free_buffer(&res);
        return NULL;
    }

    add_buffer(arg_res, "a", 1);

    while (arg_res->curr_size != arg->curr_size)
    {
        add_buffer(res, arg_res->buff, arg_res->curr_size);
        add_buffer(res, "+", 1);
        increment(arg_res);
    }
    while(strncmp(arg_res->buff, arg->buff, arg->curr_size))
    {
        add_buffer(res, arg_res->buff, arg_res->curr_size);
        add_buffer(res, "+", 1);
        increment(arg_res);
    }
    free_buffer(&arg_res);
    return res;
}

struct Buffer *get_fct(size_t number_args)
{
    struct Buffer *res = init_buffer();
    if (!res)
        return NULL;

    struct Buffer *arg = init_buffer();
    if (!arg)
    {
        free_buffer(&res);
        return NULL;
    }

    res = get_fct_arg(number_args, res, arg);
    res = get_fct_return(number_args, res, arg);
    
    res->curr_size--;
    add_buffer(res, ";}\n\0", 5);
    free_buffer(&arg);
    return res;
}

struct Buffer *get_call(size_t number_args)
{
    struct Buffer *res = init_buffer();
    if (!res)
        return NULL;

    add_buffer(res, MAIN_BEGIN, sizeof(MAIN_BEGIN) / sizeof(char));
    add_buffer(res, FCT_NAME, sizeof(FCT_NAME) / sizeof(char));
    add_buffer(res, "(", 1);

    for (size_t i = 0; i < number_args; i++)
    {
        add_buffer(res, "1,", 2);
    }
    res->curr_size--;
    add_buffer(res, ")", 1);
    add_buffer(res, MAIN_END, sizeof(MAIN_END) / sizeof(char));
    return res;
}

void write_function(FILE *file, size_t number_args)
{
    struct Buffer *buffer = get_fct(number_args);
    if (!buffer)
        return;
    fwrite(buffer->buff, buffer->curr_size, sizeof(char), file);
    free_buffer(&buffer);
}

void write_call(FILE *file, size_t number_args)
{
    struct Buffer *buffer = get_call(number_args);
    if (!buffer)
        return;
    fwrite(buffer->buff, buffer->curr_size, sizeof(char), file);
    free_buffer(&buffer);
}