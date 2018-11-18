#include "processor.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

/**
* @brief Constructor for processor struct
*
* @param processor Pointer address of the processor struct to be created and initialized
*
* @return If processor was created and all its parameters were initialized in appropriate way than returns zero, else - special error code
*/
int ProcessorCTor(Processor ** processor, char * filename) {
    int err_code = 0;

    if (processor == nullptr){
        return ERR_PROC_CTOR_NULL;
    }

    if (filename == nullptr){
        return ERR_PROC_CTOR_FLNM;
    }

    Processor * proc = (Processor *) malloc(sizeof(Processor));
    proc->instr_ptr = 0;
    proc->digit = 0;
    proc->tmp_res = 0;
    proc->tmp_res2 = 0;

    Stack * stk = nullptr;
    Stack * stkRet = nullptr;

    err_code = StackCtor(&stk, 100);
    if(err_code){
        return err_code;
    }
    proc->stk = stk;

    err_code = StackCtor(&stkRet, 100);
    if(err_code){
        return err_code;
    }
    proc->stkRet = stkRet;

    proc->regs[REG_NUM] = {0};

    char * byte_code = nullptr;
    err_code = ReadByteCode(filename, &byte_code);
    if(err_code){
        return err_code;
    }
    if (byte_code == nullptr){
        return ERR_PROC_NULL_CODE;
    }
    proc->byte_code = byte_code;

    *processor = proc;

    return err_code;
}


/**
* @brief Destructor for processor struct
*
* @param processor Pointer to the processor struct to be freed
*
* @return If all processor struct memory was freed in appropriate way, else - special error code
*/
int ProcessorDTor(Processor * processor) {

    if (processor == nullptr){
        return ERR_PROC_DTOR_NULL;
    }

    free(processor->byte_code);
    free(processor->stkRet);
    free(processor->stk);

    return 0;
}

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
    Processor * processor = nullptr;

    if (filename == nullptr){
        return ERR_PROC_FILE;
    }

    err_code = ProcessorCTor(&processor, filename);
    if(err_code){
        return err_code;
    }

    //!@def Is used to automatically change code for parsing input byte-code after adding new commands into "commands.h"
    #define CMD_DEF(name, num, code) \
    case CMD_##name : \
        code; \
        break;

    //!Processing byte-code with commands from "commands.h" before EOF
    while (processor->byte_code[processor->instr_ptr] != EOF) {

        processor->digit = processor->byte_code[processor->instr_ptr] - '0';

        switch(processor->digit){

            #include "../Common/commands.h"

            default:
                break;
        }

        if(err_code){
            return err_code;
        }

    }
    //!Undef macro for preventing possible mistakes
    #undef CMD_DEF

    err_code = ProcessorDTor(processor);
    if (err_code){
       return err_code;
    }

    return err_code;
}

