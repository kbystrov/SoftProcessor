/** @file */

//!@note The container for all commands. Is used in assembler, processor and commands enum.

//!Push into stack value from register with index following after this command
CMD_DEF(PUSHR, 1, err_code = StackPush(processor->stk, processor->regs[processor->byte_code[processor->instr_ptr + 1] - '0' - 1]);
if(err_code){
    return err_code;
}
processor->instr_ptr += 2)

//!Write value from stack to register with index following after this command
CMD_DEF(POPR, 2, processor->tmp_res = StackPop(processor->stk, &err_code);
if(err_code){
    return err_code;
}
processor->regs[processor->byte_code[processor->instr_ptr + 1] - '0' - 1] = processor->tmp_res;
processor->instr_ptr += 2)

//!Push value following after this command to stack
CMD_DEF(PUSH,3, err_code = StackPush(processor->stk, *( (elem_t *) &processor->byte_code[processor->instr_ptr + 1] ));
if(err_code){
    return err_code;
}
processor->instr_ptr += 1 + sizeof(elem_t))

//!Return value from the top of stack
CMD_DEF(POP,4, StackPop(processor->stk, &err_code);
if(err_code){
    return err_code;
}
processor->instr_ptr++)

//!Take two values from top of stack, add them and put to the top of stack this result
CMD_DEF(ADD, 5, processor->tmp_res = StackPop(processor->stk,&err_code);
if(err_code){
    return err_code;
}
processor->tmp_res2 = StackPop(processor->stk,&err_code);
if(err_code){
    return err_code;
}
err_code = StackPush(processor->stk, processor->tmp_res + processor->tmp_res2);
if(err_code){
    return err_code;
}
processor->instr_ptr++)

//!Take two values from top of stack, subtract last from next and put to the top of stack this result
CMD_DEF(SUB, 6, processor->tmp_res = StackPop(processor->stk,&err_code);
if(err_code){
    return err_code;
}
processor->tmp_res2 = StackPop(processor->stk,&err_code);
if(err_code){
    return err_code;
}
err_code = StackPush(processor->stk, processor->tmp_res2 - processor->tmp_res );
if(err_code){
    return err_code;
}
processor->instr_ptr++)

//!Take two values from top of stack, multiply them and put to the top of stack this result
CMD_DEF(MUL, 7, processor->tmp_res = StackPop(processor->stk,&err_code);
if(err_code){
    return err_code;
}
processor->tmp_res2 = StackPop(processor->stk,&err_code);
if(err_code){
    return err_code;
}
err_code = StackPush(processor->stk, processor->tmp_res2 * processor->tmp_res );
if(err_code){
    return err_code;
}
processor->instr_ptr++)

//!Take two values from top of stack, divide (last - 1) element by last element and put to the top of stack this result
CMD_DEF(DIV, 8, processor->tmp_res = StackPop(processor->stk,&err_code);
if(err_code){
    return err_code;
}
processor->tmp_res2 = StackPop(processor->stk,&err_code);
if(err_code){
    return err_code;
}
err_code = StackPush(processor->stk, processor->tmp_res2 / processor->tmp_res );
if(err_code){
    return err_code;
}
processor->instr_ptr++)

//!Take top stack element, finds its sqrt and put it to the top of stack. If input top stack element is negative value then it returns error.
CMD_DEF(SQRT, 9, processor->tmp_res = StackPop(processor->stk, &err_code);
if(err_code){
    return err_code;
}
if (processor->tmp_res < 0){
    err_code = ERR_NEG_SQRT;
} else {
    StackPush(processor->stk, sqrt(processor->tmp_res));
}
processor->instr_ptr++)

//!Takes last element from stack and prints out its value
CMD_DEF(OUT, 10, processor->tmp_res = StackPop(processor->stk, &err_code);
if (err_code){
    return err_code;
}
printf("OUT: %f\n", processor->tmp_res);
processor->instr_ptr++)

//!Takes value from console and puts it into stack
CMD_DEF(IN, 11,
if(!scanf("%f", &processor->tmp_res)){
    return ERR_PROC_SCNF_IN;
};
err_code = StackPush(processor->stk, processor->tmp_res);
if (err_code){
    return err_code;
}
processor->instr_ptr++)

//!Prints that there is no solution for square equation
CMD_DEF(NOSOLV, 12, printf("There is no solution with such coefficients.\n");
processor->byte_code[processor->instr_ptr + 1] = EOF;
processor->instr_ptr++)

#include "jumps.h"

//!Returns to one position after previously called CALL command position
CMD_DEF(RET, 31, processor->tmp_res = StackPop(processor->stkRet, &err_code);
if(err_code){
    return err_code;
}
processor->instr_ptr = processor->tmp_res)

//!Ends processing byte-code
CMD_DEF(END, 0, processor->byte_code[processor->instr_ptr + 1] = EOF; processor->instr_ptr++)
