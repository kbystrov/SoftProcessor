/** @file */

//!@note The container for all commands. Is used in assembler, processor and commands enum.

//!Push into stack value from register with index following after this command
CMD_DEF(PUSHR, 1, StackPush(stk, regs[byte_code[instr_ptr + 1] - '0' - 1]) ; instr_ptr += 2)
//!Write value from stack to register with index following after this command
CMD_DEF(POPR, 2, regs[byte_code[instr_ptr + 1] - '0' - 1] = StackPop(stk, &err_code); instr_ptr += 2)
//!Push value following after this command to stack
CMD_DEF(PUSH,3, StackPush(stk, *( (elem_t *) &byte_code[instr_ptr + 1] )); instr_ptr += 1 + sizeof(elem_t))
//!Return value from the top of stack
CMD_DEF(POP,4, StackPop(stk, &err_code); instr_ptr++)
//!Take two values from top of stack, add them and put to the top of stack this result
CMD_DEF(ADD, 5, StackPush(stk, StackPop(stk,&err_code) + StackPop(stk,&err_code)); instr_ptr++)
/**@note Can not understand why changing of sign of function result does not work here!!! With some additional temporal parameter works
 * - but also can not understand it
 * */
//!Take two values from top of stack, subtract last from next and put to the top of stack this result
CMD_DEF(SUB, 6, tmp_res = StackPop(stk,&err_code) - StackPop(stk,&err_code); StackPush(stk, -tmp_res); instr_ptr++)
//!Take two values from top of stack, multiply them and put to the top of stack this result
CMD_DEF(MUL, 7, StackPush(stk, StackPop(stk,&err_code) * StackPop(stk,&err_code)); instr_ptr++)
//!Take two values from top of stack, divide (last - 1) element by last element and put to the top of stack this result
CMD_DEF(DIV, 8, tmp_res = StackPop(stk,&err_code); StackPush(stk, StackPop(stk,&err_code) / tmp_res); instr_ptr++)
//!Take top stack element, finds its sqrt and put it to the top of stack. If input top stack element is negative value then it returns error.
CMD_DEF(SQRT, 9, tmp_res = StackPop(stk, &err_code); if (tmp_res < 0) { err_code = ERR_NEG_SQRT; } else { StackPush(stk, sqrt(tmp_res)); }; instr_ptr++)
//!Takes last element from stack and prints out its value
CMD_DEF(OUT, 10, printf("OUT: %f\n", StackPop(stk, &err_code)); instr_ptr++)
//!Takes value from console and puts it into stack
CMD_DEF(IN, 11, scanf("%f", &tmp_res); StackPush(stk, tmp_res); instr_ptr++)

#include "jumps.h"

//!Returns to one position after previously called CALL command position
CMD_DEF(RET, 31, instr_ptr = StackPop(stkRet, &err_code) )
//!Ends processing byte-code
CMD_DEF(END, 0, byte_code[instr_ptr + 1] = EOF; instr_ptr++)
