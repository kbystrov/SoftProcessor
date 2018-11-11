#include "stack_utils.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

/**
* @brief Stack constructor - used for stack creation and its data initialization
*
* @param stk The address of pointer to the stack. Returned as function parameter.
* @param capacity The maximum number of elements in stack
*
* @return If stack was created in appropriate way then it returns zero, else - special error code
*/
int StackCtor(Stack ** stk, stk_size_t capacity) {

    //!Checks input params
    if(capacity < 1){
        return ERR_CTOR_CAP;
    }

    #ifndef NDEBUG
    if(stk == nullptr){
        return ERR_CTOR_STK;
    }
    #endif

    //!Allocate memory for stack and its data and initialize stack params. If some troubles during memory allocation - returns error code
    *stk = (Stack *) malloc(sizeof(Stack));

    if(*stk == nullptr){
        return ERR_CTOR_STK_MLC;
    }

    (*stk)->canary = CANARY;
    (*stk)->capacity = capacity;
    (*stk)->size = 0;
    (*stk)->data = (elem_t *) malloc(sizeof(elem_t) * capacity);

    if((*stk)->data == nullptr){
        return ERR_CTOR_DATA_MLC;
    }

    //! Fills in all elements of stack with special value POISON for debug issues
    #ifndef NDEBUG
    size_t i;
    for (i = 0; i < capacity; i++){
        (*stk)->data[i] = POISON;
    }
    #endif

    //!Fills hash
    int err_code = 0;
    (*stk)->hash = StackCalcHash(*stk, &err_code);

    return err_code;
}

/**
* @brief Memory reallocation for stack
*
* @param stk The pointer to the stack
* @param new_capacity The new value of maximum number of elements in stack
*
* @return If memory for stack was reallocated in appropriate way then it returns zero, else - special error code
*/
int StackRloc(Stack * stk, stk_size_t new_capacity) {

    #ifndef NDEBUG
    if(stk == nullptr){
        return ERR_RLOC_STK;
    }
    #endif

    //!If new_capacity is not positive value then Stack is freed with StackDtor(Stack * stk) function, else - memory is reallocated for stack
    if(new_capacity < 1){
        StackDtor(stk);
        return ERR_RLOC_CAP;
    } else {
        stk->data = (elem_t *) realloc(stk->data, new_capacity * sizeof(elem_t));
        if(stk->data == nullptr){
            return ERR_RLOC_RLC;
        }
        stk->capacity = new_capacity;
    }

    return 0;
}

/**
* @brief Stack destructor - frees memory of stack and its data
*
* @param stk The pointer to the stack
*
* @return Returns zero
*/
int StackDtor(Stack * stk) {
    free(stk->data);
    free(stk);
    return 0;
}

/**
* @brief Takes last element from the top of the stack
*
* @param stk The pointer to the stack
* @param error The pointer to error variable. It is filled with error code and returned as function parameter if any error has been occurred.
*
* @return Returns value of top element from stack if no troubles has been occurred,
* else - return POISON value and filled error value as function parameter.
*/
elem_t StackPop(Stack * stk, int * error) {

    int err_code = 0;

    //!Checks stack with StackNotOk(const Stack *stk) function before taking new value from stack
    err_code = StackNotOk(stk);
    if (err_code){
        #ifndef NDEBUG
        err_code = StackDump(stk);
        #endif
        *error = err_code;
        return POISON;
    }

    //!If stack is already empty then return special error_code
    if(stk->size == 0){
        *error = ERR_POP_SIZE;
        return POISON;
    }

    //!Takes last element value from stack, fills in this element with special empty element value and decreases stack counter by 1
    elem_t res = stk->data[--stk->size];
    stk->data[stk->size] = POISON;

    //!Changes hash after taking last element from stack
    elem_t ret_hash = StackCalcHash(stk, &err_code);
    if (err_code){
        *error = err_code;
        return POISON;
    } else {
        stk->hash = ret_hash;
    }

    //!Checks stack with StackNotOk(const Stack *stk) function after taking new value from stack
    err_code = StackNotOk(stk);
    if (err_code){
        #ifndef NDEBUG
        err_code = StackDump(stk);
        #endif
        *error = err_code;
        return POISON;
    }

    return res;
}

/**
* @brief Pushes new element at the top of the stack
*
* @param stk The pointer to the stack
* @param val The value to be pushed in the stack
*
* @return If new element was pushed in stack in appropriate way then it returns zero,
* else - special error code in Release mode and crashes with custom assert in Debug mode
*/
int StackPush(Stack * stk, elem_t val) {

    int err_code = 0;

    //!Checks stack with StackNotOk(const Stack *stk) function before pushing new value
    err_code = StackNotOk(stk);
    if (err_code){
        #ifndef NDEBUG
        StackDump(stk);
        #endif
        return err_code;
    }

    //!If stack has already filled then return special error_code
    if (stk->size >= stk->capacity){
        return ERR_PUSH_FILL;
    }

    //!Pushes new value at the top of the stack and increase the stack counter by 1
    stk->data[stk->size++] = val;
    //!Changes hash after pushing new element in stack
    elem_t ret_hash = StackCalcHash(stk, &err_code);
    if (err_code){
        return err_code;
    } else {
        stk->hash = ret_hash;
    }

    //!Checks stack with StackNotOk(const Stack *stk) function after pushing new value
    err_code = StackNotOk(stk);
    if (err_code){
        #ifndef NDEBUG
        StackDump(stk);
        #endif
        return err_code;
    }

    return err_code;
}
