#ifndef DATA_TYPES_H
#define DATA_TYPES_H

#include <stddef.h>
#include <math.h>
#include "../err_codes.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! Value to be filled in not used elements of stack - for debug issues
#define POISON tan(M_PI_2)
//! Guard value for saving other data in stack
#define CANARY 666

//!@typedef Typedef for values of stack elements
typedef int32_t elem_t;
//!@typedef Typedef for sizes params of stack
typedef uint32_t stk_size_t;

//!@typedef Typedef for Stack_str struct
typedef struct Stack_str Stack;

/**@brief Stack structure
 *
 * @param canary Special parameter is used for guarding other stack data in case of
 * @param capacity The maximum number of elements in stack
 * @param size The current number of filled elements in stack
 * @param data The pointer to elements array in stack
 * @param hash Check sum for verifying that all data in stack is valid and was not changed in not appropriate way
 */
struct Stack_str {
    elem_t canary;
    stk_size_t  capacity;
    stk_size_t  size;
    elem_t * data;
    elem_t hash;
};

#endif //DATA_TYPES_H
