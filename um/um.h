#ifndef UM_INCLUDED
#define UM_INCLUDED
#include <stdlib.h>
#include <stdint.h>
#include "registers.h"
#include "memseg.h"
#include <stdio.h>

void build_and_execute_um(FILE* program);
// Reads in program from file in 32bit word chunks and returns program counter
UM_Word* loadProgram(FILE* program);
void execute_instruction();

#endif
