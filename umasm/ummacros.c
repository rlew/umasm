#include "ummacros.h"
#include "bitpack.h"
#include "macro_functions.h"
#include <stdint.h>


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
void Ummacros_load_literal(Umsections_T asm, int temporary,
                           Ummacros_Reg A, uint32_t k){
    (void)asm;
    (void)temporary;
    k = Bitpack_newu(k,3,25,A);
    k = Bitpack_newu(k,4,28,LV);
    Umsections_emit_word(asm,k);
}
