#ifndef STACK_TESTS_H
#define STACK_TESTS_H

#include <stdio.h>
#include "data_types.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

/**
* @brief Macro for unittest: tests two inputs by specified operator. Prints out the result of unittest.
*
* @param what The tested input (may be the function or just variable)
* @param op The operator which used to compare what and ref
* @param ref The referenced result for comparision
* @param type1 Data type of what
* @param type2 Data type od ref
*/
#define UNITTEST(what, op, ref, type1, type2) \
{ \
    type1 result1 = (what); \
    type2 result2 = (ref); \
    if (result1 op result2) \
        printf("%s [passed]\n", #what); \
        else \
            printf("%s returned %td, but should return as in %s: %td [not passed]\n", #what, result1, #ref, result2); \
}

/**
* @brief Custom assert with printing out error code and file with line from which it was called
*
* @param err_code Special error code which caused this assertion
*/
#define AssertOk(err_code) \
{ \
    printf("ERROR CODE: %d in %s:%d\n", err_code, __FILE__, __LINE__); \
    assert(0); \
}

int StackNotOk(const Stack *stk);
int StackDump(const Stack * stk);
elem_t StackCalcHash(const Stack * stk, int * err_code);

#endif //STACK_TESTS_H
