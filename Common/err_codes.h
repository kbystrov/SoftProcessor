#ifndef ERR_CODES_H
#define ERR_CODES_H
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//! Error code: input capacity is not positive value in StackCtor(Stack * stk, stk_size_t capacity) function
#define ERR_CTOR_CAP 1
//! Error code: input stack pointer is nullptr in StackCtor(Stack * stk, stk_size_t capacity) function
#define ERR_CTOR_STK 2
//! Error code: malloc has returned NULL for stack pointer in StackCtor(Stack * stk, stk_size_t capacity) function
#define ERR_CTOR_STK_MLC 3
//! Error code: malloc has returned NULL for stack data pointer in StackCtor(Stack * stk, stk_size_t capacity) function
#define ERR_CTOR_DATA_MLC 4

//! Error code: input stack pointer is nullptr in StackNotOk(const Stack *stk) function
#define ERR_OK_STK 5
//! Error code: canary is wrong in StackNotOk(const Stack *stk) function
#define ERR_OK_CANARY 6
//! Error code: input stack size is not positive value in StackNotOk(const Stack *stk) function
#define ERR_OK_SIZE 7
//! Error code: input stack size is more than its capacity in StackNotOk(const Stack *stk) function
#define ERR_OK_CAP 8
//! Error code: input stack data is nullptr in StackNotOk(const Stack *stk) function
#define ERR_OK_DATA 9
//! Error code: hash is not valid in StackNotOk(const Stack *stk) function
#define ERR_OK_HASH 10

//! Error code: input stack pointer is nullptr in StackCalcHash(const Stack * stk, int * err_code) function
#define ERR_CALC_HASH_STK 11
//! Error code: input stack data is nullptr in StackCalcHash(const Stack * stk, int * err_code) function
#define ERR_CALC_HASH_DATA 12

//! Error code: input stack pointer is nullptr in StackRloc(Stack * stk, stk_size_t new_capacity) function
#define ERR_RLOC_STK 13
//! Error code: new capacity is not positive value in StackRloc(Stack * stk, stk_size_t new_capacity) function
#define ERR_RLOC_CAP 14
//! Error code: realloc has returned NULL for stack data pointer in StackRloc(Stack * stk, stk_size_t new_capacity) function
#define ERR_RLOC_RLC 15

//! Error code: stack is already filled with data and new value can not be pushed in it in StackPush(Stack * stk, elem_t val) function
#define ERR_PUSH_FILL 16

//! Error code: input stack size is zero in StackPop(Stack * stk, int * error) function
#define ERR_POP_SIZE 17

//! Error code: not enough input arguments in main(int args, char * argv[])
#define ERR_ASM_ARGS 18

//! Error code: can not open input assembler file in CreateByteCode(char * in_name, char * out_name)
#define ERR_ASM_OPEN_IN 19
//! Error code: can not open output assembler file in CreateByteCode(char * in_name, char * out_name)
#define ERR_ASM_OPEN_OUT 20
//! Error code: input file name pointer is nullptr in CreateByteCode(char * in_name, char * out_name)
#define ERR_ASM_IN 21
//! Error code: output file name pointer is nullptr in CreateByteCode(char * in_name, char * out_name)
#define ERR_ASM_OUT 22

//! Error code: input file name pointer is nullptr in ReadByteCode(char * filename, char * byte_code)
#define ERR_PROC_IN 23
//! Error code: can not open input assembler file in ReadByteCode(char * filename, char * byte_code)
#define ERR_PROC_OPEN_IN 24
//! Error code: file length is zero in ReadByteCode(char * filename, char * byte_code)
#define ERR_PROC_ZERO_LEN 25
//! Error code: the number of read bytes from input file differs from input file length in ReadByteCode(char * filename, char * byte_code)
#define ERR_PROC_READ 26

//! Error code: input file name pointer is nullptr in ProccessByteCode(char * filename)
#define ERR_PROC_FILE 27
//! Error code: returned byte code pointer from ReadByteCode(char * filename, char * byte_code) is nullptr in ProccessByteCode(char * filename)
#define ERR_PROC_NULL_CODE 28

//! Error code: input file is nullptr in ReadLabels(FILE * inp_file, Label ** lab_table, size_t * lab_count)
#define ERR_READ_LAB_IN 29

//! Error code: malloc returned nullptr in LabelTableCTor(Label ** lab_table, stk_size_t lab_num)
#define ERR_LAB_TAB_CTOR 30

//! Error code: input label array is nullptr in LabelTableDTor(Label * lab_table, stk_size_t lab_num)
#define ERR_LAB_TAB_DTOR_NULL 31
//! Error code: input number of labels is negative number in LabelTableDTor(Label * lab_table, stk_size_t lab_num)
#define ERR_LAB_TAB_DTOR_NUM 32

//! Error code: input label array is nullptr in LabelTableRLC(Label * lab_table, stk_size_t lab_num)
#define ERR_LAB_TAB_RLC_NULL 33
//! Error code: input number of labels is negative number in  LabelTableRLC(Label * lab_table, stk_size_t lab_num)
#define ERR_LAB_TAB_RLC_NUM 34
//! Error code: realloc returned nullptr in LabelTableRLC(Label * lab_table, stk_size_t lab_num) for Label Struct
#define ERR_LAB_TAB_RLC_RLC_TAB 35
//! Error code: realloc returned nullptr for label buffer of Label Struct in LabelTableRLC(Label * lab_table, stk_size_t lab_num) for Label
#define ERR_LAB_TAB_RLC_RLC_LAB 36

//! Error code: negative input for SQRT command
#define ERR_NEG_SQRT 37

#endif //ERR_CODES_H
