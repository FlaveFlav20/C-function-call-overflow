#include "includes/tests.h"
#include "includes/c_function_call_overflow.h"

#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

size_t test_with_c_code(size_t max_char, FILE *file_to_test_fct, FILE *file_to_test_fct_call)
{
    if (max_char <= 0 || !file_to_test_fct || file_to_test_fct_call)
        return -1;
    
    size_t min_number_args = 127;
    size_t number_args = 127;
    bool loop = true;

    while (loop)
    {
        pid_t pid = fork();

        if (pid == -1)
            break;
        
        if (!pid)
        {
            write_call(file_to_test_fct_call, number_args);
            write_function(file_to_test_fct, number_args);
            char *args[]={"gcc","t.c", "te.c"};
            return execv(args[0], args);
        }
        else
        {
            int status = 0;
            waitpid(pid, &status, WNOHANG | WUNTRACED);

            if (status == -1 && number_args <= (min_number_args + 1))
                loop = false;
            else if (status == -1 && number_args > min_number_args)
                number_args = (min_number_args + number_args) /2;
            else
            {
                number_args*=2;
                min_number_args = number_args;
            }
        }
    }
    return min_number_args;
}

size_t test_with_assembly_code(size_t max_char, FILE *file_to_test_fct, FILE *file_to_test_fct_call)
{
    if (max_char <= 0 || !file_to_test_fct || !file_to_test_fct_call)
        return -1;

    size_t min_number_args = 127;
    size_t number_args = 127;
    bool loop = true;

    while (loop)
    {
        pid_t pid = fork();

        if (pid == -1)
            break;
        
        if (!pid)
        {
            custom_compile(file_to_test_fct, number_args);
            char *args[]={"gcc","t.c", "te.c"};
            return execv(args[0], args);
        }
        else
        {
            int status = 0;
            waitpid(pid, &status, WNOHANG | WUNTRACED);

            if (status == -1 && number_args <= (min_number_args + 1))
                loop = false;
            else if (status == -1 && number_args > min_number_args)
                number_args = (min_number_args + number_args) /2;
            else
            {
                number_args*=2;
                min_number_args = number_args;
            }
        }
    }
    return min_number_args;
    return 0;
}