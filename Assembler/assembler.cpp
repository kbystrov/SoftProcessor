#include "assembler.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */


/**
* @brief Creates specific byte-code for processor from input pseudo-assembler code
*
* @param in_name Pointer to the name of input assembler file with pseudo-assembler code
* @param out_name Pointer to the name of output assembler file with byte-code
*
* @return If byte-code was created successful then it returns zero, else - special error code
*/
int CreateByteCode(char * in_name, char * out_name) {
    FILE * asm_in;
    FILE * asm_out;
    int value = 0;
    char buf[10] = {0};
    char rax[10] = {0};
    bool psh_num_flg = false;
    bool psh_rax_flg = false;

    if (in_name == nullptr){
        return ERR_ASM_IN;
    }

    if (out_name == nullptr){
        return ERR_ASM_OUT;
    }

    if ( !( asm_in = fopen(in_name, "rb") ) ){
        #ifndef NDEBUG
        printf("Error: specified file %s can not be opened in CreateByteCode\n", in_name);
        #endif
        return ERR_ASM_OPEN_IN;
    }

    if ( !( asm_out = fopen(out_name, "wb") ) ){
        #ifndef NDEBUG
        printf("Error: specified file %s can not be opened in CreateByteCode\n", out_name);
        #endif
        return ERR_ASM_OPEN_OUT;
    }

    //!@def Is used to automatically change code for parsing input commands after adding new commands into "commands.h"
    #define CMD_DEF(name, num, code) \
    if(strcmp(buf, #name) == 0){ \
        fprintf(asm_out, "%c", num + '0'); \
        }

    #define REG_DEF(name, num) \
    if(strcmp(rax, #name) == 0){ \
        fprintf(asm_out, "%c", num + '0'); \
    }

    //!Reading all symbols from pseudo-assembler code one by one
    while( fscanf(asm_in, "%s", buf) != EOF){

        //! Additional parsing logic for PUSH/POP for numbers and registers
        if (!strcmp(buf, "PUSH") || !strcmp(buf, "POP")) {
            if (fscanf(asm_in, "%d", &value)) {
                psh_num_flg = true;
            } else {
                fscanf(asm_in, "%s", rax);
                strcat(buf, "R");
                psh_rax_flg = true;
            }
        }

        #include "../Common/commands.h"

        //! Additional parsing logic for PUSH/POP for numbers and registers
        if (psh_num_flg){
            fwrite(&value, sizeof(elem_t), 1, asm_out);
            psh_num_flg = false;
        } else if (psh_rax_flg) {
            #include "../Common/registers.h"

            psh_rax_flg = false;
        }

    }

    //!Undef macro for preventing possible mistakes
    #undef REG_DEF
    #undef CMD_DEF

    fclose(asm_in);
    fclose(asm_out);

    return 0;
}
