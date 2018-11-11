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
    char buf[100] = {0};

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

    //! Macro for auto-filling all commands
    #define CMD_DEF(name, num, code) \
        if(strcmp(buf, #name) == 0){ \
        fprintf(asm_out, "%d", num); \
        }

    /**Reading all symbols from pseudo-assebler code one by one
     * - if it is command then macro is used to convert in into number, else if number - in standard way.
     */

    int value = 0;
    while( fscanf(asm_in, "%s", buf) != EOF){

        #include "commands.h"

        if ( fscanf(asm_in, "%d", &value) ){
            fwrite(&value, sizeof(code_t), 1, asm_out);
            //fprintf(asm_out, "%d ", value);
        }

    }

    //!Undef macro for preventing possible mistakes
    #undef CMD_DEF

    fclose(asm_in);
    fclose(asm_out);

    return 0;
}
