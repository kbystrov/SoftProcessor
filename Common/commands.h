/** @file */

//!@note The container for all commands. Is used in assembler, processor and commands enum.

CMD_DEF(PUSHR, 1, StackPush(stk, regs[byte_code[instr_ptr + 1] - '0' - 1]) ; instr_ptr += 2)
CMD_DEF(POPR, 2, regs[byte_code[instr_ptr + 1] - '0' - 1] = StackPop(stk, &err_code); instr_ptr += 2)
CMD_DEF(PUSH,3, StackPush(stk, *( (elem_t *) &byte_code[instr_ptr + 1] )); instr_ptr += 1 + sizeof(elem_t))
CMD_DEF(POP,4, StackPop(stk, &err_code); instr_ptr++)
CMD_DEF(ADD, 5, StackPush(stk, StackPop(stk,&err_code) + StackPop(stk,&err_code)); instr_ptr++)
/**@note Can not understand why changing of sign of function result does not work here!!! With some additional temporal parameter works
 * - but also can not understand it
 * */
CMD_DEF(SUB, 6, tmp_res = StackPop(stk,&err_code) - StackPop(stk,&err_code); StackPush(stk, -tmp_res); instr_ptr++)
CMD_DEF(MUL, 7, StackPush(stk, StackPop(stk,&err_code) * StackPop(stk,&err_code)); instr_ptr++)
CMD_DEF(DIV, 8, tmp_res = StackPop(stk,&err_code); StackPush(stk, StackPop(stk,&err_code) / tmp_res); instr_ptr++)
CMD_DEF(SQRT, 9, tmp_res = StackPop(stk, &err_code); if (tmp_res < 0) { err_code = ERR_NEG_SQRT; } else { StackPush(stk, sqrt(tmp_res)); }; instr_ptr++)
CMD_DEF(OUT, 10, printf("OUT: %f\n", StackPop(stk, &err_code)); instr_ptr++)
CMD_DEF(IN, 11, scanf("%f", &tmp_res); StackPush(stk, tmp_res); instr_ptr++)

#include "jumps.h"

CMD_DEF(END, 0, byte_code[instr_ptr + 1] = EOF; instr_ptr++)
