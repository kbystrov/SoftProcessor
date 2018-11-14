/** @file */

//!@note The container for all jumps. Is used in assembler, processor and in const array for JUMPS in "assembler.h".

CMD_DEF(JMP, 20, instr_ptr =  *((label_t *) & byte_code[instr_ptr + 1] ) )
CMD_DEF(JA, 21, if( StackPop(stk, &err_code) > StackPop(stk, &err_code) ){ instr_ptr = *( (label_t *) &byte_code[instr_ptr + 1] ); }else{ instr_ptr += sizeof(label_t) + 1;} )
CMD_DEF(JB, 22, if( StackPop(stk, &err_code) < StackPop(stk, &err_code) ){ instr_ptr = *( (label_t *) &byte_code[instr_ptr + 1] ); }else{ instr_ptr += sizeof(label_t) + 1;} )
CMD_DEF(JE, 23, if( StackPop(stk, &err_code) == StackPop(stk, &err_code) ){ instr_ptr = *( (label_t *) &byte_code[instr_ptr + 1] ); }else{ instr_ptr += sizeof(label_t) + 1;} )
CMD_DEF(JAE, 24, if( StackPop(stk, &err_code) >= StackPop(stk, &err_code) ){ instr_ptr = *( (label_t *) &byte_code[instr_ptr + 1] ); }else{ instr_ptr += sizeof(label_t) + 1;} )
CMD_DEF(JBE, 25, if( StackPop(stk, &err_code) <= StackPop(stk, &err_code) ){ instr_ptr = *( (label_t *) &byte_code[instr_ptr + 1] ); }else{ instr_ptr += sizeof(label_t) + 1;} )
CMD_DEF(JRE, 26, if( StackPop(stk, &err_code) != StackPop(stk, &err_code) ){ instr_ptr = *( (label_t *) &byte_code[instr_ptr + 1] ); }else{ instr_ptr += sizeof(label_t) + 1;} )

CMD_DEF(CALL, 30, StackPush(stkRet, instr_ptr + sizeof(label_t) + 1);instr_ptr = *((label_t *) & byte_code[instr_ptr + 1] ) )