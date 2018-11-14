#include "assembler.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

/**
* @brief Checks if input command is one of JUMP command from automatically generated constant array JUMPS with JUMP command numbers
*
* @param x Number of input command
*
* @return If it is JUMP command then 1, else 0
*/
int isJump(size_t x) {
    size_t i;
    for(i = 0; i<(sizeof(JUMPS)/sizeof(*JUMPS)); i++) {
        if(JUMPS[i] == x){
            return 1;
        }
    }
    return 0;
}

/**
* @brief Creates specific byte-code for processor from input pseudo-assembler code
*
* @param in_name Pointer to the name of input assembler file with pseudo-assembler code
* @param out_name Pointer to the name of output assembler file with byte-code
*
* @return If byte-code was created successful then it returns zero, else - special error code
*/
int CreateByteCode(char * in_name, char * out_name) {
    FILE * asm_in = nullptr;
    FILE * asm_out = nullptr;
    Label * lab_table = nullptr;
    size_t lab_count = 0;
    elem_t value = 0;
    char buf[15] = {0};
    char rax[10] = {0};
    bool psh_num_flg = false;
    bool psh_rax_flg = false;
    size_t i = 0;
    int err_code = 0;

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

    err_code = ReadLabels(asm_in, &lab_table, &lab_count);

    if (err_code){
        return err_code;
    }

    //!@def Is used to automatically change code for parsing input commands after adding new commands into "commands.h" and "jumps.h"
    #define CMD_DEF(name, num, code) \
    if(strcmp(buf, #name) == 0){ \
        fprintf(asm_out, "%c", num + '0'); \
        if(isJump(num)){ \
            fscanf(asm_in, "%s", buf); \
            for (i = 0; i < lab_count; i++) { \
                if(strcmp(buf+1,lab_table[i].label) == 0){ \
                    fwrite(&lab_table[i].pos, sizeof(label_t), 1, asm_out); \
                } \
            } \
        } \
    }

    //!@def Is used to automatically change code after adding new registers into "registers.h"
    #define REG_DEF(name, num) \
    if(strcmp(rax, #name) == 0){ \
        fprintf(asm_out, "%c", num + '0'); \
    }

    //!Reading all symbols from pseudo-assembler code one by one
    while( fscanf(asm_in, "%s", buf) != EOF){

        //! Additional parsing logic for PUSH/POP for numbers and registers
        if (!strcmp(buf, "PUSH") || !strcmp(buf, "POP")) {
            if (fscanf(asm_in, "%f", &value)) {
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

    LabelTableDTor(lab_table, lab_count);
    fclose(asm_in);
    fclose(asm_out);

    return err_code;
}
