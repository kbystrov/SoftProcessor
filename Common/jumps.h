/** @file */

//!@note The container for all jumps. Is used in assembler, processor and in const array for JUMPS in "assembler.h".

//!Jump to the position specified after this command
CMD_DEF(JMP, 20, processor->instr_ptr =  *((label_t *) &processor->byte_code[processor->instr_ptr + 1] ) )

//!Jump to the position specified after this command if last element from stack is bigger than one previous to it
CMD_DEF(JA, 21, processor->tmp_res = StackPop(processor->stk, &err_code);
if(err_code){
    return err_code;
}
processor->tmp_res2 = StackPop(processor->stk, &err_code);
if(err_code){
    return err_code;
}
if( processor->tmp_res > processor->tmp_res2 ){ processor->instr_ptr = *( (label_t *) &processor->byte_code[processor->instr_ptr + 1] ); }else{ processor->instr_ptr += sizeof(label_t) + 1;} )

//!Jump to the position specified after this command if last element from stack is lower than one previous to it
CMD_DEF(JB, 22, processor->tmp_res = StackPop(processor->stk, &err_code);
if(err_code){
return err_code;
}
processor->tmp_res2 = StackPop(processor->stk, &err_code);
if(err_code){
return err_code;
}
if( processor->tmp_res < processor->tmp_res2 ){ processor->instr_ptr = *( (label_t *) &processor->byte_code[processor->instr_ptr + 1] ); }else{ processor->instr_ptr += sizeof(label_t) + 1;} )

//!Jump to the position specified after this command if last element from stack equals to one previous to it
CMD_DEF(JE, 23, processor->tmp_res = StackPop(processor->stk, &err_code);
if(err_code){
    return err_code;
}
processor->tmp_res2 = StackPop(processor->stk, &err_code);
if(err_code){
    return err_code;
}
if( processor->tmp_res == processor->tmp_res2 ){ processor->instr_ptr = *( (label_t *) &processor->byte_code[processor->instr_ptr + 1] ); }else{ processor->instr_ptr += sizeof(label_t) + 1;} )

//!Jump to the position specified after this command if last element from stack is bigger than one previous to it or equals to it
CMD_DEF(JAE, 24, processor->tmp_res = StackPop(processor->stk, &err_code);
if(err_code){
    return err_code;
}
processor->tmp_res2 = StackPop(processor->stk, &err_code);
if(err_code){
    return err_code;
}
if( processor->tmp_res >= processor->tmp_res2 ){ processor->instr_ptr = *( (label_t *) &processor->byte_code[processor->instr_ptr + 1] ); }else{ processor->instr_ptr += sizeof(label_t) + 1;} )

//!Jump to the position specified after this command if last element from stack is lower than one previous to it or equals to it
CMD_DEF(JBE, 25, processor->tmp_res = StackPop(processor->stk, &err_code);
if(err_code){
    return err_code;
}
processor->tmp_res2 = StackPop(processor->stk, &err_code);
if(err_code){
    return err_code;
}
if( processor->tmp_res <= processor->tmp_res2 ){ processor->instr_ptr = *( (label_t *) &processor->byte_code[processor->instr_ptr + 1] ); }else{ processor->instr_ptr += sizeof(label_t) + 1;} )

//!Jump to the position specified after this command if last element from stack is not equal to one previous to it
CMD_DEF(JRE, 26, processor->tmp_res = StackPop(processor->stk, &err_code);
if(err_code){
    return err_code;
}
processor->tmp_res2 = StackPop(processor->stk, &err_code);
if(err_code){
    return err_code;
}
if( processor->tmp_res != processor->tmp_res2 ){ processor->instr_ptr = *( (label_t *) &processor->byte_code[processor->instr_ptr + 1] ); }else{ processor->instr_ptr += sizeof(label_t) + 1;} )

/** Pushes next after this command and label position in byte-code to special Stack with "return values"
 * (is used after return from function with RET command) and jumps to the position specified after command
 */
CMD_DEF(CALL, 30, err_code = StackPush(processor->stkRet, processor->instr_ptr + sizeof(label_t) + 1);
if(err_code){
    return err_code;
}
processor->instr_ptr = *((label_t *) &processor->byte_code[processor->instr_ptr + 1] ) )