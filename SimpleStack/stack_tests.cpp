#include "stack_tests.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

/**
* @brief Stack verificator - checks if stack has appropriate params
*
* @param stk Pointer to the stack
*
* @return If stack is normal then it returns zero, else - special error code
*/
int StackNotOk(const Stack *stk){

    if (stk == nullptr){
        return ERR_OK_STK;
    }

    if (stk->canary != CANARY){
        return ERR_OK_CANARY;
    }

    if (stk->size < 0){
        return ERR_OK_SIZE;
    }

    if (stk->size > stk->capacity){
        return ERR_OK_CAP;
    }

    if (stk->data == nullptr){
        return ERR_OK_DATA;
    }

    int err_code = 0;
    if (stk->hash != StackCalcHash(stk, &err_code)){
        return ERR_OK_HASH;
    }

    return err_code;
}

/**
* @brief Print out all information about the stack and its data
*
* @param stk Pointer to the stack
*
* @return Returns zero after completion in appropriate way, else - special error code
*/
int StackDump(const Stack * stk) {

    int err_code = 0;

    //! StackNotOk(const Stack *stk) is used to determine if stk or stk->data is nullptr for preventing SegFault in this function
    err_code = StackNotOk(stk);

    if (err_code == ERR_OK_STK){
        return err_code;
    }

    printf("Stack [%p]{\n", stk);
    printf("   canary = %zd\n", stk->canary);
    printf("   capacity = %zu\n", stk->capacity);
    printf("   size = %zu\n", stk->size);
    printf("   data[%zu] [%p]{\n", stk->size, stk->data);

    if (err_code == ERR_OK_DATA){
        return err_code;
    }

    stk_size_t i;
    for (i = 0; i < stk->capacity; i++){
        /** If stack element is filled with value equal to POISON (special value which filled
         *  in all stack elements after stack creation) then prints out also this info.
         */
        if (stk->data[i] != POISON){
            printf("      [%zu]: [%zd]\n", i, stk->data[i]);
        } else {
            printf("      [%zu]: [%zd] - POISON!!!\n", i, stk->data[i]);
        }
    }
    printf("   }\n");
    printf("   hash = %zd\n}\n", stk->hash);

    return err_code;
}

/**
* @brief Calculates stack's hash
*
* @param stk Pointer to the stack
* @param err_code The pointer to error variable. It is filled with error code and returned as function parameter if any error has been occurred.
*
* @return If no errors has benn occurred then - value of stack hash, else - special POISON value and filled err_code value as function parameter.
*/
elem_t StackCalcHash(const Stack * stk, int * err_code) {

    if(stk == nullptr){
        *err_code = ERR_CALC_HASH_STK;
        return POISON;
    }

    if(stk->data == nullptr){
        *err_code = ERR_CALC_HASH_DATA;
        return POISON;
    }

    //!Stack value is calculated as power polynomial : hash = canary * 1^1 + capacity * 2^2 + size * 3^3 + sum( data[n] * n^(n+4); n in [0; size - 1] )
    elem_t hash = stk->canary + (elem_t) pow(stk->capacity, 2) + (elem_t) pow(stk->size, 3);
    size_t i;
    for(i = 0; i < stk->size; i++){
        hash += stk->data[i] * pow(i + 4, i + 4);
    }

    return hash;
}
