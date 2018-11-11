#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdlib.h>
#include <stdio.h>
#include "../Common/err_codes.h"
#include "../Assembler/assembler.h"
#include "../SimpleStack/stack_utils.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

int ReadByteCode (char * filename, char ** byte_code);
int ProccessByteCode(char * filename);

#endif //PROCESSOR_H
