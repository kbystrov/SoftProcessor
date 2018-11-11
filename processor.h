#ifndef PROCESSOR_H
#define PROCESSOR_H

#include <stdlib.h>
#include <stdio.h>
#include "err_codes.h"
#include "SimpleStack/stack_utils.h"
#include "assembler.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

int ReadByteCode (char * filename, char ** byte_code);
int ProccessByteCode(char * filename);

#endif //PROCESSOR_H
