#ifndef C_FUNCTION_CALL_OVERFLOW
#define C_FUNCTION_CALL_OVERFLOW

#define MAIN_BEGIN "#include \"t.c\"\nint main(){int i="
#define MAIN_END ";return i;}"

#define FCT_NAME "fct"

#define FCT_BEGIN "int fct("
#define FCT_END "){return "

#define MAX_ARG_BEFORE_WRITE 100
#define TYPE_ARGS "int "

#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

struct Buffer *get_fct(size_t number_args);
struct Buffer *get_call(size_t number_args);
void write_call(FILE *file, size_t number_args);
void write_function(FILE *file, size_t number_args);

#endif // C_FUNCTION_CALL_OVERFLOW