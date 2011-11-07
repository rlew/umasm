#ifndef MEMSEG_INCLUDED
#define MEMSEG_INCLUDED
#include <stdlib.h>
#include <stdint.h>
#include "seq.h"

typedef uint32_t UM_Word;

typedef struct Mem{
    Seq_T mappedIDs;
    Seq_T unmappedIDs;
    int i;
}Mem;

void instantiateMem(Mem* memorySegments, int length);
UM_Word mapSegment(Mem* memorySegments, int length);
void unmapSegment(Mem* memorySegments, UM_Word index);
UM_Word segmentedLoad(Mem* memorySegments, int ID, int offset);
void segmentedStore(Mem* memorySegments, int ID, int offset, UM_Word
                       value);
void freeMem(Mem* memorySegments);
#endif
