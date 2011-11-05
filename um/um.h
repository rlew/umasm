#include <stdlib.h>

typedef uint32_t UM_Word;

void build_and_execute_um(FILE* program);
// Reads in program from file in 32bit word chunks and returns program counter
UM_Word* loadProgram(FILE* program, UM_Word* memorySegments, Stack_T
                           unmappedSegs);
void execute_instruction(UM_Word* memorySegments, Stack_T unmappedSegs,
                         UM_Word* registers);

