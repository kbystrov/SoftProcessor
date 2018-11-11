#include "Assembler/assembler.h"
#include "Processor/processor.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main(int args, char * argv[]) {

    printf("# Soft Processor v.0.1 (c) Kirill Bystrov\n");
    printf("# This program takes input file with pseudo-assembler code, convert it in custom byte-code and executes it\n");

    if (args < 3){
        printf("No input arguments. Please run the program in the following format: ./SoftProcessor $asm_input $asm_output");
        return ERR_ASM_ARGS;
    }

    int err_code = CreateByteCode(argv[1], argv[2]);

    ProccessByteCode(argv[2]);

    return err_code;
}