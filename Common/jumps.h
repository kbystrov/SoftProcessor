/** @file */

//!@note The container for all jumps. Is used in assembler, processor and in const array for JUMPS in "assembler.h".

CMD_DEF(JMP, 20, instr_ptr =  *( (elem_t *) &byte_code[instr_ptr + 1] ) )
CMD_DEF(JA, 21, tmp_res = StackPop(stk, &err_code); if( tmp_res > StackPop(stk, &err_code) ){ instr_ptr = *( (elem_t *) &byte_code[instr_ptr + 1] ); }else{ instr_ptr += sizeof(elem_t) + 1;} )
CMD_DEF(JB, 22, )
CMD_DEF(JE, 23, )
CMD_DEF(JAE, 24, )
CMD_DEF(JBE, 25, )
CMD_DEF(JRE, 26, )
