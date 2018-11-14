#include "processor.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

/**
* @brief Reads all specific byte-code for processor into chars array
*
* @param filename Pointer to the name of output assembler file with byte-code to be read
* @param byte_code Pointer to pointer of byte array to be written with byte-code. Returned as function parameter.
*
* @return If byte-code was read successful then it returns zero and filled function parameter, else - special error code
*/
int ReadByteCode(char * filename, char ** byte_code) {
    FILE * inp_file;

    if (filename == nullptr){
        return ERR_PROC_IN;
    }

    if ( !( inp_file = fopen(filename, "rb") ) ){
        #ifndef NDEBUG
        printf("Error: specified file %s can not be opened in ReadByteCode\n", filename);
        #endif
        return ERR_PROC_OPEN_IN;
    }

    //! Get the length of the input file in bytes
    fseek(inp_file, 0, SEEK_END);
    size_t inp_file_len = ftell(inp_file);
    rewind(inp_file);

    if(!inp_file_len){
        return ERR_PROC_ZERO_LEN;
    }

    //!Create array of bytes and fill it
    char * input_strs = (char *) malloc(inp_file_len);
    size_t read_res = fread(input_strs, 1, inp_file_len, inp_file);

    /** If number of read elements in fread differs from input file length then there is some error
     */
    if ( !read_res) {
        printf("Warning: no bytes were read from input file in fileread function\n");
        return ERR_PROC_READ;
    }

    //!Fills byte_code to return it to ProccessByteCode(char * filename) function and close input file
    *byte_code = input_strs;
    fclose(inp_file);

    return 0;
}

/**
* @brief Processes input byte-code
*
* @param filename Pointer to the name of output assembler file with byte-code to be read
*
* @return If byte-code was processed successful then it returns zero, else - special error code
*/
int ProccessByteCode(char * filename) {
    int err_code = 0;
    char * byte_code = nullptr;
    size_t instr_ptr = 0;
    int digit = 0;
    Stack * stk = nullptr;
    Stack * stkRet = nullptr;
    elem_t tmp_res = 0;

    //!@var Registers' array
    elem_t regs[REG_NUM] = {0};

    if (filename == nullptr){
        return ERR_PROC_FILE;
    }

    //! Reads byte code from input file to special byte array
    err_code = ReadByteCode(filename, &byte_code);

    if(err_code){
        return err_code;
    }

    if (byte_code == nullptr){
        return ERR_PROC_NULL_CODE;
    }

    StackCtor(&stk, 100);
    StackCtor(&stkRet, 100);

    //!@def Is used to automatically change code for parsing input byte-code after adding new commands into "commands.h"
    #define CMD_DEF(name, num, code) \
    case CMD_##name : \
        code; \
        break;

    //!Processing byte-code with commands from "commands.h" before EOF
    while (byte_code[instr_ptr] != EOF) {

        digit = byte_code[instr_ptr] - '0';

        switch(digit){

            #include "../Common/commands.h"

            default:
                break;
        }

        if(err_code){
            return err_code;
        }

    }

    #undef CMD_DEF

    free(byte_code);
    StackDtor(stkRet);
    StackDtor(stk);

    return err_code;
}

