# SoftProcessor
Parses input pseudo-assembler code to byte-code with using custom assembler realization and processing this byte-code with custom processor realization.

Assembler/ - contains utils for working with Assembler and Label Tables - converting input pesudo-assembler to output byte-code for Processor

Processor/ - contains utils for working with Processor for executing input byte-code

StackUtils/ - contains utils for working with Stack Structures (it was duplicated from https://github.com/kbystrov/SimpleStack)

Common/ - global error codes, commands for Processor, registers

IOFiles/ - the container for saving pseduo-assembler programs to be executed and output byte-code



To run program use SoftCommon in the following way:
./SoftCommon $inp_file $out_file

$inp_file - path to input file with pseudo-assembler code

$out_file - path to output file with byte-code to be processed
