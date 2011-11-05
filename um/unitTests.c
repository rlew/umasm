#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <mem.h>
#include "memseg.h"
#include "uarray.h"
#include "stack.h"
#include "seq.h"

static int MEM_SEG_LEN = 500;


void verifyMapped(UArray_T memorySegments, Stack_T unmappedSegments) {
    Stack_T verified = Stack_new();
    // Verifies that the available unmapped segments is updated upon mapping
    while(!Stack_empty(unmappedSegments)){
        UM_Word* index = Stack_pop(unmappedSegments);
        if(UArray_at(memorySegments, *index) != NULL){
            fprintf(stderr, "unmapped segments not updated correctly\n");
            exit(1);
        }
        Stack_push(unmappedSegments, &index);
    }
    unmappedSegments = verified;
    Stack_free(&verified);

    for(int i = 1; i < MEM_SEG_LEN; i++) {
        if (UArray_at(memorySegments, i) != NULL) {
            for(int j = 0; j < Seq_length(UArray_at(memorySegments, i)); j++) {
                // Each 32-bit word must be initialized to 0
                if((Seq_get(UArray_at(memorySegments, i), j)) != 0) {
                    fprintf(stderr, "segment incorrectly initialized");
                    exit(1);
                }
            }
        }
    }
}

int main(int argc, char* argv[]) {
    (void) argc; (void) argv;
    UArray_T memorySegments = UArray_new(MEM_SEG_LEN, sizeof(UM_Word*));
    Stack_T unmappedSegs = Stack_new();
    Stack_T unmappedSegs2 = Stack_new();
    for(UM_Word i = MEM_SEG_LEN - 1; i >= 1; i--) {
        Stack_push(unmappedSegs, &i);
        Stack_push(unmappedSegs2, &i);
    }

    UM_Word index = nextIndexToMap(unmappedSegs);
    mapSegment(memorySegments, index, 10);
    verifyMapped(memorySegments, unmappedSegs);

    unmapSegment(memorySegments, index);
    unmapIndex(unmappedSegs, index);
    verifyMapped(memorySegments, unmappedSegs);

    UM_Word value = 20;
    segmentedStore(memorySegments, 1, 0, value);

    if(segmentedLoad(memorySegments, 1, 0) != value) {
        fprintf(stderr, "incorrect load and store");
        exit(1);
    }

    // Should fail because it will attempt to map the same ID to another
    // segment
    index = nextIndexToMap(unmappedSegs2);
    mapSegment(memorySegments, index, 1);

    return 0;
}
