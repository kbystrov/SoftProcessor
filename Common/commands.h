/** @file */

//!@note The container for all commands. Is used in assembler, processor and commands enum.

CMD_DEF(END, 0, byte_code[instr_ptr + 1] = EOF; instr_ptr++)
CMD_DEF(PUSH,1, StackPush(stk, *( (elem_t *) &byte_code[instr_ptr + 1] )); instr_ptr += 1 + sizeof(elem_t))
CMD_DEF(POP,2, StackPop(stk, &err_code); instr_ptr++)
CMD_DEF(ADD, 3, StackPush(stk, StackPop(stk,&err_code) + StackPop(stk,&err_code)); instr_ptr++)
/**@note Can not understand why changing of sign of function result does not work here!!! With some additional temporal parameter works
 * - but also can not understand it
 * */
CMD_DEF(SUB, 4, tmp_res = StackPop(stk,&err_code) - StackPop(stk,&err_code); StackPush(stk, -tmp_res); instr_ptr++)
CMD_DEF(MUL, 5, StackPush(stk, StackPop(stk,&err_code) * StackPop(stk,&err_code)); instr_ptr++)
CMD_DEF(DIV, 6, tmp_res = StackPop(stk,&err_code); StackPush(stk, StackPop(stk,&err_code) / tmp_res); instr_ptr++)
CMD_DEF(OUT, 7, printf("OUT: %d\n", StackPop(stk, &err_code)); instr_ptr++)
CMD_DEF(JA, 8, )
CMD_DEF(JB, 9, )
CMD_DEF(JE, 10, )
CMD_DEF(JAE, 11, )
CMD_DEF(JBE, 12, )
CMD_DEF(JRE, 13, )
CMD_DEF(PUSHR, 14, StackPush(stk, regs[byte_code[instr_ptr + 1] - '0' - 1]) ; instr_ptr += 2)
CMD_DEF(POPR, 15, regs[byte_code[instr_ptr + 1] - '0' - 1] = StackPop(stk, &err_code); instr_ptr += 2)

