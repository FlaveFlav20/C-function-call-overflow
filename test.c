#include "src/includes/c_function_call_overflow.h"
#include "src/includes/utils.h"

int main(void)
{
    size_t size = 100;
    FILE *file_ = fopen("te.c", "w");
    if (!file_)
        return -1;
    write_call(file_,size);
    FILE *file = fopen("t.c", "w");
    if (!file)
        return -1;
    write_function(file,size);
}