#ifndef STACK_UTILS_H
#define STACK_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "data_types.h"
#include "stack_tests.h"
#include "../err_codes.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

int StackCtor(Stack ** stk, stk_size_t capacity);
int StackRloc(Stack * stk, stk_size_t new_capacity);
int StackDtor(Stack * stk);
elem_t StackPop(Stack * stk, int * error);
int StackPush(Stack * stk, elem_t val);

#endif //STACK_UTILS_H
