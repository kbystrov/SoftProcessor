#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../Common/err_codes.h"
#include "../SimpleStack/stack_utils.h"
#include "labels.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

//********************************************************************************************************************
//!@def Is used to automatically fill all commands after adding them into "commands.h"
#define CMD_DEF(name, num, code) CMD_##name = num,

typedef  enum{
    #include "../Common/commands.h"
} COMMAND;

#undef CMD_DEF
//********************************************************************************************************************

//********************************************************************************************************************
#define REG_DEF(name, num) REG_##name = num,

//!@def Is used to automatically fill all registers after adding them into "registers.h"
typedef enum{
    #include "../Common/registers.h"
} REGS;

#undef REG_DEF
//********************************************************************************************************************

//********************************************************************************************************************
//!@def Is used to automatically fill all jump commands after adding them into "jumps.h"
#define CMD_DEF(name, num, code) num,

const size_t JUMPS[] = {
    #include "../Common/jumps.h"
};

#undef CMD_DEF
//********************************************************************************************************************

int isJump(size_t x);
int CreateByteCode(char * in_name, char * out_name);

#endif //ASSEMBLER_H
