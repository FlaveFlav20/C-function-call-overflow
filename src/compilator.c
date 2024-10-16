#include "./includes/compilator.h"
#include "./includes/utils.h"

static bool push_args(struct Buffer *assembly_code, size_t number_args)
{
    if (!add_buffer(assembly_code, CALL_NAME,
                                      strlen(CALL_NAME)))
    {
        free_buffer(&assembly_code);
        return false;
    }

    if (number_args > 0 && !add_buffer(assembly_code, ARG_ONE_FUNCTION_IN_PREPARE,
                                      strlen(ARG_ONE_FUNCTION_IN_PREPARE)))
    {
        free_buffer(&assembly_code);
        return false;
    }

    if (number_args > 1 && !add_buffer(assembly_code, ARG_TWO_FUNCTION_IN_PREPARE ,
                                      strlen(ARG_TWO_FUNCTION_IN_PREPARE )))
    {
        free_buffer(&assembly_code);
        return false;
    }

    if (number_args > 2 && !add_buffer(assembly_code, ARG_THREE_FUNCTION_IN_PREPARE,
                                      strlen(ARG_THREE_FUNCTION_IN_PREPARE)))
    {
        free_buffer(&assembly_code);
        return false;
    }

    if (number_args > 3 && !add_buffer(assembly_code, ARG_FOUR_FUNCTION_IN_PREPARE,
                                      strlen(ARG_FOUR_FUNCTION_IN_PREPARE)))
    {
        free_buffer(&assembly_code);
        return false;
    }

    if (number_args > 4 && !add_buffer(assembly_code, ARG_FIVE_FUNCTION_IN_PREPARE,
                                      strlen(ARG_FIVE_FUNCTION_IN_PREPARE)))
    {
        free_buffer(&assembly_code);
        return false;
    }

    if (number_args > 5 && !add_buffer(assembly_code, ARG_SIX_FUNCTION_IN_PREPARE,
                                      strlen(ARG_SIX_FUNCTION_IN_PREPARE)))
    {
        free_buffer(&assembly_code);
        return false;
    }

    return true;
}

static void to_lower_case(char *buffer, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        if (buffer[i] >= 'A' && buffer[i] <= 'Z')
            buffer[i] += 'a' - 'A';
    }
}

bool add_numbers(struct Buffer *assembly_code, size_t number_args)
{
    if (!add_buffer(assembly_code, ARG_POP_FIRST, strlen(ARG_POP_FIRST)))
    {
        free_buffer(&assembly_code);
        return false;
    }

    size_t i = 1;
    while (i < number_args && i <= 6)
    {
        if (!add_buffer(assembly_code, "\tmov -", strlen("\tmov -")))
        {
            free_buffer(&assembly_code);
            return false;
        }

        if (!add_buffer(assembly_code, BEGIN_HEX, strlen(BEGIN_HEX)))
        {
            free_buffer(&assembly_code);
            return false;
        }

        char buffer[20] = { '\0' };
        sprintf(buffer, "%x", i * 4);
        to_lower_case(buffer, strlen(buffer));
        if (!add_buffer(assembly_code, buffer, strlen(buffer)))
        {
            free_buffer(&assembly_code);
            return false;
        }

        if (!add_buffer(assembly_code, ARG_POP_MORE, strlen(ARG_POP_MORE)))
        {
            free_buffer(&assembly_code);
            return false;
        }

        if (!add_buffer(assembly_code, ARG_ADD, strlen(ARG_ADD)))
        {
            free_buffer(&assembly_code);
            return false;
        }
        i++;
    }

    int begin = 16;

    while (i < number_args)
    {
        if (!add_buffer(assembly_code, "\tmov 0x", strlen("\tmov 0x")))
        {
            free_buffer(&assembly_code);
            return false;
        }
        char buffer[20] = { '\0' };
        sprintf(buffer, "%X", begin);
        to_lower_case(buffer, strlen(buffer));
        if (!add_buffer(assembly_code, buffer, strlen(buffer)))
        {
            free_buffer(&assembly_code);
            return false;
        }

        if (!add_buffer(assembly_code, ARG_POP_MORE, strlen(ARG_POP_MORE)))
        {
            free_buffer(&assembly_code);
            return false;
        }

        if (!add_buffer(assembly_code, ARG_ADD, strlen(ARG_ADD)))
        {
            free_buffer(&assembly_code);
            return false;
        }

        i++;
        begin+=8;
    }


    if (!add_buffer(assembly_code, END_FUNCTION, strlen(END_FUNCTION)))
    {
        free_buffer(&assembly_code);
        return false;
    }

    return true;
}

int custom_compile(size_t number_args, FILE *file_to_write)
{
    if (!number_args || !file_to_write)
        return -1;

    struct Buffer *assembly_code = init_buffer();
    if (!assembly_code)
        return -1;

    if (!push_args(assembly_code, number_args))
        return -1;

    if (!add_numbers(assembly_code, number_args))
        return -1;

    fwrite(assembly_code->buff, sizeof(char), assembly_code->curr_size, file_to_write);
    free_buffer(&assembly_code);
    return 0;
}
