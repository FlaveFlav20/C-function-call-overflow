#include "includes/c_function_call_overflow.h"
#include "includes/utils.h"

#include <string.h>

struct Buffer *get_fct(size_t number_args)
{
    struct Buffer *res = init_buffer();
    if (!res)
        return NULL;

    struct Buffer *arg = init_buffer();
    if (!arg)
    {
        free_buffer(res);
        return NULL;
    }

    add_buffer(arg, "A", 1);
    add_buffer(res, FCT_BEGIN, sizeof(FCT_BEGIN) / sizeof(char) - 1);

    for (size_t i = 0; i < number_args; i++)
    {
        add_buffer(res, TYPE_ARGS, sizeof(TYPE_ARGS) / sizeof(char) - 1);
        add_buffer(res, arg->buff, arg->curr_size);
        add_buffer(res, ",", 1);

        if (arg->buff[arg->curr_size - 1] == 'Z')
            add_buffer(arg, "A", 1);
        else
            arg->buff[arg->curr_size - 1]++;
    }
    res->curr_size--;
    add_buffer(res, FCT_END, sizeof(FCT_END) / sizeof(char) - 1);
    add_buffer(res, "\n", 1);
    struct Buffer *arg_res = init_buffer();
    if (!arg_res)
    {
        free_buffer(arg);
        free_buffer(res);
        return NULL;
    }

    add_buffer(arg_res, "A", 1);

    while (arg_res->curr_size != arg->curr_size)
    {
        add_buffer(res, arg_res->buff, arg_res->curr_size);
        add_buffer(res, "+", 1);
        if (arg_res->buff[arg_res->curr_size - 1] == 'Z')
            add_buffer(arg_res, "A", 1);
        else
            arg_res->buff[arg_res->curr_size - 1]++;
    }
    while(strncmp(arg_res->buff, arg->buff, arg->curr_size))
    {
        add_buffer(res, arg_res->buff, arg_res->curr_size);
        add_buffer(res, "+", 1);
        if (arg_res->buff[arg->curr_size - 1] == 'Z')
            add_buffer(arg_res, "A", 1);
        else
            arg_res->buff[arg_res->curr_size - 1]++;
    }
    res->curr_size--;
    add_buffer(res, ";}\n\0", 5);
    free_buffer(arg);
    free_buffer(arg_res);
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
    free_buffer(buffer);
}

void write_call(FILE *file, size_t number_args)
{
    struct Buffer *buffer = get_call(number_args);
    if (!buffer)
        return;
    fwrite(buffer->buff, buffer->curr_size, sizeof(char), file);
    free_buffer(buffer);
}