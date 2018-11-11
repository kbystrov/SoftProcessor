#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "err_codes.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

#define CMD_DEF(name, num, code) CMD_##name = num,

typedef  enum{
    #include "commands.h"
} COMMAND;

#undef CMD_DEF

int CreateByteCode(char * in_name, char * out_name);

#endif //ASSEMBLER_H
