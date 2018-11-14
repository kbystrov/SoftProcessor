/** @file */

//!@note The container for all jumps. Is used in assembler, processor and in const array for JUMPS in "assembler.h".

//!Jump to the position specified after this command
CMD_DEF(JMP, 20, instr_ptr =  *((label_t *) & byte_code[instr_ptr + 1] ) )
//!Jump to the position specified after this command if last element from stack is bigger than one previous to it
CMD_DEF(JA, 21, if( StackPop(stk, &err_code) > StackPop(stk, &err_code) ){ instr_ptr = *( (label_t *) &byte_code[instr_ptr + 1] ); }else{ instr_ptr += sizeof(label_t) + 1;} )
//!Jump to the position specified after this command if last element from stack is lower than one previous to it
CMD_DEF(JB, 22, if( StackPop(stk, &err_code) < StackPop(stk, &err_code) ){ instr_ptr = *( (label_t *) &byte_code[instr_ptr + 1] ); }else{ instr_ptr += sizeof(label_t) + 1;} )
//!Jump to the position specified after this command if last element from stack equals to one previous to it
CMD_DEF(JE, 23, if( StackPop(stk, &err_code) == StackPop(stk, &err_code) ){ instr_ptr = *( (label_t *) &byte_code[instr_ptr + 1] ); }else{ instr_ptr += sizeof(label_t) + 1;} )
//!Jump to the position specified after this command if last element from stack is bigger than one previous to it or equals to it
CMD_DEF(JAE, 24, if( StackPop(stk, &err_code) >= StackPop(stk, &err_code) ){ instr_ptr = *( (label_t *) &byte_code[instr_ptr + 1] ); }else{ instr_ptr += sizeof(label_t) + 1;} )
//!Jump to the position specified after this command if last element from stack is lower than one previous to it or equals to it
CMD_DEF(JBE, 25, if( StackPop(stk, &err_code) <= StackPop(stk, &err_code) ){ instr_ptr = *( (label_t *) &byte_code[instr_ptr + 1] ); }else{ instr_ptr += sizeof(label_t) + 1;} )
//!Jump to the position specified after this command if last element from stack is not equal to one previous to it
CMD_DEF(JRE, 26, if( StackPop(stk, &err_code) != StackPop(stk, &err_code) ){ instr_ptr = *( (label_t *) &byte_code[instr_ptr + 1] ); }else{ instr_ptr += sizeof(label_t) + 1;} )

/** Pushes next after this command and label position in byte-code to special Stack with "return values"
 * (is used after return from function with RET command) and jumps to the position specified after command
 */
CMD_DEF(CALL, 30, StackPush(stkRet, instr_ptr + sizeof(label_t) + 1);instr_ptr = *((label_t *) & byte_code[instr_ptr + 1] ) )