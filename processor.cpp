#include "processor.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

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

    /** If number of read elements in fread differs from input file length then:
     *  - If it is positive number then some elements were read and function execution continues
     *  - Else - there is some error then function returns an error code to main()
     */
    if ( (read_res != inp_file_len) && !read_res) {
        printf("Warning: no bytes were read from input file in fileread function\n");
        return ERR_PROC_READ;
    }

    //!Fills file_strs to return it to ProccessByteCode(char * filename) function and close input file
    *byte_code = input_strs;
    fclose(inp_file);

    return 0;
}

int ProccessByteCode(char * filename) {
    int err_code = 0;
    char * byte_code = nullptr;
    size_t instr_ptr = 0;
    int digit = 0;

    if (filename == nullptr){
        return ERR_PROC_FILE;
    }

    err_code = ReadByteCode(filename, &byte_code);

    if(err_code){
        return err_code;
    }

    if (byte_code == nullptr){
        return ERR_PROC_NULL_CODE;
    }

    Stack * stk = nullptr;
    StackCtor(&stk, 100);

    #define CMD_DEF(name, num, code) \
    case CMD_##name : \
        code; \
        break;

    while (byte_code[instr_ptr] != EOF){

        digit = byte_code[instr_ptr] - '0';

        switch(digit){

            #include "commands.h"

            default:
                break;
        }

    }

    #undef CMD_DEF

    return 0;
}

