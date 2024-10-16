#ifndef TESTS_H
#define TESTS_H

#include <stdio.h>

size_t test_with_c_code(size_t max_char, FILE *file_to_test_fct, FILE *file_to_test_fct_call);
size_t test_with_assembly_code(size_t max_char, FILE *file_to_test_fct, FILE *file_to_test_fct_call);

#endif // TESTS_H
