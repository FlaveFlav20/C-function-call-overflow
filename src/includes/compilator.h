#ifndef COMPILATOR_H
#define COMPILATOR_H

#define CALL_NAME ".global overflow\noverflow:\n\tpush %rbp\n\tmov %rsp, %rbp\n"
#define BEGIN_FUNCTION "\tpush %rbp\nmov %rsp,,%rbp\n"

#define ARG_ONE_CALL "\tmov $0x1, %edi\n"
#define ARG_TWO_CALL "\tmov $0x1, %esi\n"
#define ARG_THREE_CALL "\tmov $0x1, %edx\n"
#define ARG_FOUR_CALL "\tmov $0x1, %ecx\n"
#define ARG_FIVE_CALL "\tmov $0x1, %r8d\n"
#define ARG_SIX_CALL "\tmov $0x1, %r9d\n"
#define ARG_SEVEN_MORE_CALL "\tpush 0x01\n"

#define ARG_ONE_FUNCTION_IN_PREPARE "\tmov %edi, -0x4(%rbp)\n"
#define ARG_TWO_FUNCTION_IN_PREPARE "\tmov %esi, -0x8(%rbp)\n"
#define ARG_THREE_FUNCTION_IN_PREPARE "\tmov %edx, -0xc(%rbp)\n"
#define ARG_FOUR_FUNCTION_IN_PREPARE "\tmov %ecx, -0x10(%rbp)\n"
#define ARG_FIVE_FUNCTION_IN_PREPARE "\tmov %r8d, -0x14(%rbp)\n"
#define ARG_SIX_FUNCTION_IN_PREPARE "\tmov %r9d, -0x18(%rbp)\n"

#define ARG_POP_FIRST "\tmov -0x4(%rbp), %eax\n"
#define BEGIN_HEX "0x"

// ARG_POP_MORE: the arg 0x?? shoule be before (%rbp)
#define ARG_POP_MORE "(%rbp), %edx\n"
#define ARG_ADD "\tadd %edx, %eax\n"

#define END_FUNCTION "\tmov %rbp, %rsp\n\tpop %rbp\n\tret"

#include <stdio.h>
/*
 * This program will generate a custom compilator for intel x86 : the main goal is to creata a specific program
*/

int custom_compile(size_t number_args);


#endif // COMPILATOR_H
