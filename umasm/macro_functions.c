#include "macro_functions.h"

static inline uint32_t bitpackWord(uint32_t word, enum Um_Opcode op, int A, 
                                   int B, int C) {
    word = Bitpack_newu(word, 4, 28, op);
    word = Bitpack_newu(word, 3, 6, A);
    word = Bitpack_newu(word, 3, 3, B);
    word = Bitpack_newu(word, 3, 0, C);

    return word;
}

static inline uint32_t bitpackLoadVal(uint32_t word, int reg, int value){
    word = Bitpack_newu(word, 4, 28, LV);
    word = Bitpack_newu(word, 3, 25, reg);
    word = Bitpack_newu(word, 25, 0, value);

    return word;
}

Seq_T move(int A, int B, int C, Seq_T instructions){
    //loadVal into C
    uint32_t load;
    load = bitpackLoadVal(load, C, 1);
    Seq_addhi(instructions, (void *)(uintptr_t)load);
    //conditional move with a,b,c
    uint32_t cmov;
    cmov = bitpackWord(cmov, CMOV, A, B, C);
    Seq_addhi(instructions, (void *)(uintptr_t)cmov);
    
    return instructions;
}

Seq_T complement(int A, int B, int C, Seq_T instructions){
    (void) C;
    uint32_t nand;
    nand = bitpackWord(nand, NAND, A, B, B);
    Seq_addhi(instructions, (void *)(uintptr_t)nand);
    return instructions;
}

Seq_T negate(int A, int B, int C, Seq_T instructions){
    instructions = complement(A, B, C, instructions);
    uint32_t load;
    load = bitpackLoadVal(load, C, 1);
    Seq_addhi(instructions, (void *)(uintptr_t)load);
    uint32_t add;
    add = bitpackWord(add, ADD, A, A, C);
    Seq_addhi(instructions, (void *)(uintptr_t)add);

    return instructions;
}

Seq_T subtract(int A, int B, int C, int temp, Seq_T instructions){
    instructions = negate(C, C, temp, instructions);
    uint32_t add;
    add = bitpackWord(add, ADD, A, B, C);
    Seq_addhi(instructions, (void *)(uintptr_t)add);

    return instructions;
}

Seq_T bitwise_and(int A, int B, int C, Seq_T instructions){
    uint32_t nand;
    nand = bitpackWord(nand, NAND, A, B, C);
    Seq_addhi(instructions, (void *)(uintptr_t)nand);
    
    return complement(A, A, A, instructions);
}

Seq_T bitwise_or(int A, int B, int C, Seq_T instructions){
    instructions = complement(B, B, B, instructions);
    instructions = complement(C, C, C, instructions);
    uint32_t nand;
    nand = bitpackWord(nand, NAND, A, B, C);
    Seq_addhi(instructions, (void *)(uintptr_t)nand);

    return instructions;
}
