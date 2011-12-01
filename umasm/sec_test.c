#include "umsections.h"
#include <stdio.h>

void apply(const char *name, void *cl){
    (void) cl;
    fprintf(stdout, " %s/n",name);
}

int main(){
    Umsections_T asm = Umsections_new("text",NULL,NULL);
    Umsections_emit_word(asm,97);
    Umsections_emit_word(asm,98);
    Umsections_emit_word(asm,99);
    Umsections_section(asm,"bss");
    Umsections_emit_word(asm,101);
    Umsections_emit_word(asm,102);
    Umsections_emit_word(asm,103);
    Umsections_section(asm,"text");
    Umsections_emit_word(asm,100);

    Umsections_putword(asm,"text",0,98);


    Umsections_write(asm,stdout);
    Umsections_map(asm,apply,NULL);
    Umsections_free(&asm);
}

