#include "assembler.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

int ReadLabels(FILE * inp_file, Label ** lab_table, size_t * lab_count) {
    char buf[15] = {0};
    char tmp_buf[15] = {0};
    size_t instr_ptr = 0;
    size_t l_count = 0;
    bool jmp_flg = false;
    size_t i = 0;
    //! Test code
    Label * labels = (Label *) malloc(10 * sizeof(Label));
    for (i = 0; i < 10; i++){
        labels[i].label = (char *) malloc(100);
    }

    if(inp_file == nullptr){
        return ERR_READ_LAB_IN;
    }

    //!@def Macro for identifying that label is followed or not after jump command - is used for adding all jumps command from "jump.h" automatically
    #define CMD_DEF(name, num, code) \
    if (!strcmp(buf,#name)){ \
        jmp_flg = true; \
    }

    while ( fscanf(inp_file, "%s", buf) != EOF) {
        if(*buf == ':'){

            int not_filled = 1;
            strcpy(tmp_buf, buf + 1);

            //!Checks if this label has been written in table
            for(i = 0; i < l_count; i++){
                if(!strcmp(tmp_buf, labels[i].label)){
                    not_filled = 0;
                    //!If this label is not followed by jump command - then current position is label position and it is filled
                    if (!jmp_flg) {
                        labels[i].pos = instr_ptr;
                    }
                    break;
                }
            }

            //!If label was not found in table then it is written in it and increases label count
            if (not_filled) {
                strcpy(labels[l_count].label, tmp_buf);
                //!If this label is not followed by jump command - then current position is label position and it is filled
                if (!jmp_flg) {
                    labels[l_count].pos = instr_ptr;
                }
                l_count++;
            }

            //! Increase current position by sizeof(elem_t) because label's position should be written in byte-code after jump command
            if(jmp_flg){
                instr_ptr += sizeof(elem_t);
            }
            //!Jump flag should be changed to false after every label check because each label may has only one position in code
            jmp_flg = false;

        } else {

            #include "../Common/jumps.h"

            /**If it is not label then increase current position by 1 to commands and by sizeof(elem_t) for numbers -
             * it is used for identify labels position and write it during byte-code creation process
             */
            if (isdigit(*buf)) {
                instr_ptr += sizeof(elem_t);
            } else {
                instr_ptr++;
            }
        }
    }
    //!Undef macro for preventing possible mistakes
    #undef CMD_DEF

    //!Fills number of labels and pointer to label table and returns them as function parameters
    rewind(inp_file);
    *lab_table = labels;
    *lab_count = l_count;

    return 0;
}

/**
* @brief Cheks if input command is one of JUMP command from automatically generated constant array JUMPS with JUMP command numbers
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
    int value = 0;
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
                    fwrite(&lab_table[i].pos, sizeof(elem_t), 1, asm_out); \
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

    return err_code;
}
