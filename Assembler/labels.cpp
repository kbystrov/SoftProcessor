#include "labels.h"
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

/** @file */

int LabelTableCTor(Label ** lab_table, stk_size_t lab_num) {
    stk_size_t i = 0;
    Label * labels = (Label *) malloc(lab_num * sizeof(Label));

    if (labels == nullptr){
        return  ERR_LAB_TAB_CTOR;
    }

    for (i = 0; i < lab_num; i++){
        labels[i].label = (char *) malloc(LAB_BUF);
    }

    *lab_table = labels;

    return 0;
}

int LabelTableDTor(Label * lab_table, stk_size_t lab_num) {
    stk_size_t i = 0;

    if (lab_table == nullptr){
        return ERR_LAB_TAB_DTOR_NULL;
    }

    if (lab_num < 0){
        return ERR_LAB_TAB_DTOR_NUM;
    }

    for (i = 0; i < lab_num; i++){
        free(lab_table[i].label);
    }

    free(lab_table);

    return 0;
}

int LabelTableRLC(Label * lab_table, stk_size_t lab_num) {
    stk_size_t i = 0;

    if (lab_table == nullptr){
        return ERR_LAB_TAB_RLC_NULL;
    }

    if (lab_num < 0){
        return ERR_LAB_TAB_RLC_NUM;
    }

    if ( realloc(lab_table, lab_num) == nullptr ){
        return ERR_LAB_TAB_RLC_RLC_TAB;
    }

    for (i = 0; i < lab_num; i++){
        if ( realloc(lab_table[i].label, LAB_BUF) == nullptr ){
            return ERR_LAB_TAB_RLC_RLC_LAB;
        }
    }

    return 0;
}

int ReadLabels(FILE * inp_file, Label ** lab_table, size_t * lab_count) {
    char buf[15] = {0};
    char tmp_buf[15] = {0};
    size_t instr_ptr = 0;
    size_t l_count = 0;
    bool jmp_flg = false;
    int err_code = 0;
    size_t i = 0;
    size_t lab_limit = LAB_TABLE_INIT;

    if(inp_file == nullptr){
        return ERR_READ_LAB_IN;
    }

    Label * labels = nullptr;
    err_code = LabelTableCTor(&labels, LAB_TABLE_INIT);

    if (err_code){
        return err_code;
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
                if( !(l_count % lab_limit) ){
                    lab_limit *= 2;
                    LabelTableRLC(labels, lab_limit);
                }
            }

            //! Increase current position by sizeof(uint32_t) because label's position should be written in byte-code after jump command
            if(jmp_flg){
                instr_ptr += sizeof(label_t);
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

    return err_code;
}