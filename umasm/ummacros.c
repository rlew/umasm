#include "ummacros.h"
#include "bitpack.h"
#include "macro_functions.h"
#include <stdint.h>
#include <assert.h>
#include <stdlib.h>

void Ummacros_op(Umsections_T asm, Ummacros_Op operator, int temporary,
                 Ummacros_Reg A, Ummacros_Reg B, Ummacros_Reg C){
    Seq_T instructions = Seq_new(1);
    switch(operator){
    case MOV:
        instructions = move(A,B,C,instructions);
        break;
    case COM:
        instructions = complement(A,B,C,instructions);
        break;
    case NEG:
        instructions = negate(A,B,C,instructions);
        break;
    case SUB:
        if(temporary < 0) {
            Umsections_error(asm, 
            "No temporary register provided for subtraction function.");
        }
        instructions = subtract(A,B,C, temporary, instructions);
        break;
    case AND:
        instructions = bitwise_and(A,B,C,instructions);
        break;
    case OR:
        instructions = bitwise_or(A,B,C,instructions);
        break;
    }
    int length = Seq_length(instructions);
    for(int i = 0; i < length; i++){
        Umsections_emit_word(asm, 
            (uint32_t)(uintptr_t)Seq_get(instructions,i));
    }

    Seq_free(&instructions);

}

static inline uint32_t shr(uint32_t word, unsigned bits){
    assert(bits <= 32);
    if(bits == 32)
        return 0;
    return word >> bits;
}

static inline bool fitsu(int32_t n, unsigned width){
    if(width >= 32) return true;
    return shr(n, width) == 0;
}

void Ummacros_load_literal(Umsections_T asm, int temporary,
                           Ummacros_Reg A, uint32_t k){

    if(fitsu(k, 25) || fitsu(~k, 25)){
        k = Bitpack_getu(k, 25, 0);
        k = Bitpack_newu(k,3,25,A);
        k = Bitpack_newu(k,4,28,LV);
        Umsections_emit_word(asm,k);
    }
    else {
        if(temporary < 0){
            Umsections_error(asm,
            "No temporary register provided for load literal function.");
        }
        uint32_t upper = Bitpack_getu(k, 16, 16);
        uint32_t lower = Bitpack_getu(k, 16, 0);
        uint32_t instr; 
        instr = Bitpack_newu(instr, 4, 28, LV);
        instr = Bitpack_newu(instr, 3, 25, A);
        instr = Bitpack_newu(instr, 25, 0, upper);
        Umsections_emit_word(asm, instr);

        instr = Bitpack_newu(instr, 3, 25, temporary);
        instr = Bitpack_newu(instr, 25, 0, 65536);
        Umsections_emit_word(asm, instr);
        
        instr = Bitpack_newu(instr, 4, 28, MUL);
        instr = Bitpack_newu(instr, 3, 6, A);
        instr = Bitpack_newu(instr, 3, 3, A);
        instr = Bitpack_newu(instr, 3, 0, temporary);
        Umsections_emit_word(asm, instr);
        
        instr = Bitpack_newu(instr, 4, 28, LV);
        instr = Bitpack_newu(instr, 3, 25, temporary);
        instr = Bitpack_newu(instr, 25, 0, lower);
        Umsections_emit_word(asm, instr);
        
        instr = Bitpack_newu(instr, 4, 28, ADD);
        instr = Bitpack_newu(instr, 3, 6, A);
        instr = Bitpack_newu(instr, 3, 3, A);
        instr = Bitpack_newu(instr, 3, 0, temporary);
        Umsections_emit_word(asm, instr);
    }
}
