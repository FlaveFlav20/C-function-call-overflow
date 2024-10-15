#include "src/includes/c_function_call_overflow.h"
#include "src/includes/utils.h"
#include "src/includes/compilator.h"
int main(int argc, char* argv[])
{
    size_t size;
    if (argc < 2)
        size = 100;
    else
    {
        size = str_to_size_t(argv[1]);
    }
    custom_compile(size);

    /*FILE *file_ = fopen("te.c", "w");
    if (!file_)
        return -1;
    write_call(file_,size);
    FILE *file = fopen("t.c", "w");
    if (!file)
        return -1;
    write_function(file,size);
    fclose(file_);
    fclose(file);*/
}
