#include "umsections.h"
#include "table.h"
#include "seq.h"
#include "mem.h"
#include "assert.h"
#include "atom.h"
#include "bitpack.h"

#define T Umsections_T
struct T{
    Seq_T current;
    Table_T section_table;
    Seq_T section_seq;
    int (*error)(void* errstate, const char *message);
    void* errstate;
};


T Umsections_new(const char *section, 
            int (*error)(void *errstate, const char *message),
            void *errstate){
    T sections;
    NEW(sections);
    sections->section_table = Table_new(0,NULL,NULL);
    sections->section_seq = Seq_new(10);
    Seq_T first_seq = Seq_new(10);
    Table_put(sections->section_table, Atom_string(section), first_seq);
    Seq_addhi(sections->section_seq,(void*)Atom_string(section));
    sections->error = error;
    sections->errstate = errstate;
    sections->current = first_seq;

    return sections;
}
void Umsections_free(T *asmp) {
    assert(asmp && *asmp);
    int length = Seq_length((*asmp)->section_seq);
    for(int i = 0; i < length; i++){
        const char *name = Seq_get((*asmp)->section_seq,i);
        Seq_T section = Table_get((*asmp)->section_table,name);
        if(section)
            Seq_free(&section);
    }
    Seq_free(&(*asmp)->section_seq);
    Table_free(&(*asmp)->section_table);
    FREE(*asmp);
}

int Umsections_error(T asm, const char *msg){
    return asm->error(asm->errstate, msg);
}

void Umsections_section(T asm, const char *section){
    assert(asm);
    Seq_T sec = Table_get(asm->section_table,Atom_string(section));
    if(sec)
        asm->current = sec;
    else{
        Seq_T new_seq = Seq_new(10);
        Table_put(asm->section_table, Atom_string(section), new_seq);
        Seq_addhi(asm->section_seq, (void*)Atom_string(section));
        asm->current = new_seq;
    }
}

void Umsections_emit_word(T asm, Umsections_word data){
    assert(asm);
    assert(asm->current);
    Seq_addhi(asm->current, (void *)(uintptr_t)data);
}

void Umsections_map(T asm, void apply(const char *name, void *cl), void *cl){
    int length = Seq_length(asm->section_seq);
    for(int i = 0; i < length; i++){
        apply(Seq_get(asm->section_seq,i),cl);
    }
}

int Umsections_length(T asm, const char *name){
    assert(asm);
    Seq_T section = Table_get(asm->section_table,Atom_string(name));
    if(!section)
        Umsections_error(asm,"invalid section name in Umsections_length");
    return Seq_length(section);
}

Umsections_word Umsections_getword(T asm, const char *name, int i){
    assert(asm);
    Seq_T section = Table_get(asm->section_table,Atom_string(name));
    if(!section)
        Umsections_error(asm,"invalid section name in Umsections_getword");
    return (Umsections_word)(uintptr_t)Seq_get(section,i);
}

void Umsections_putword(T asm, const char *name, int i, Umsections_word w){
    assert(asm);
    Seq_T section = Table_get(asm->section_table,Atom_string(name));
    if(!section)
        Umsections_error(asm,"invalid section name in Umsections_putword");
    Seq_put(section,i,(void*)(uintptr_t)w);
}

void Umsections_write(T asm, FILE *output){
    int length = Seq_length(asm->section_seq);
    for(int i = 0; i < length; i++){
            const char *name = Seq_get(asm->section_seq,i);
            int sec_length = Umsections_length(asm,name);
            for(int j = 0; j < sec_length; j++){
                Umsections_word word = Umsections_getword(asm, name, j);
                for(int k = 3; k >= 0; k--){
                    putc(Bitpack_getu(word,8,k*8),output);
                }
            }
        
    }
}



