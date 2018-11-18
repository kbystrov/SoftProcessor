#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdlib.h>
#include <stdio.h>
#include "../Common/err_codes.h"
#include "../Assembler/assembler.h"
#include "../SimpleStack/stack_utils.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//!@typedef Typedef for LabelStr struct
typedef struct ProcessorStr Processor;

/**@brief  Processor structure
 *
 * @param byte_code The pointer to byte-code to be processed
 * @param instr_ptr The current position in byte-code which is processed
 * @param digit The number of current command
 * @param stk The pointer to stack with values for commands
 * @param stkRet The pointer to stack with "return values" - addresses for command RET to return from function which was called with CALL command
 * @param tmp_res The variable for saving temporary result of calculations
 * @param tmp_res Another variable for saving temporary result of calculations
 * @param regs - The poiner to array of REG_NUM (defined at compilation step from "registers.h") registers to save some values
 */
struct ProcessorStr {
    char * byte_code;
    size_t instr_ptr;
    int digit;
    Stack * stk;
    Stack * stkRet;
    elem_t tmp_res;
    elem_t tmp_res2;
    elem_t regs[REG_NUM];
};

int ProcessorCTor (Processor ** processor, char * filename);
int ProcessorDTor (Processor * processor);
int ReadByteCode (char * filename, char ** byte_code);
int ProccessByteCode(char * filename);

#endif //PROCESSOR_H
