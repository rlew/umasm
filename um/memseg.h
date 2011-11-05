#include <stdlib.h>
#include <stdint.h>
#include "stack.h"
#include "uarray.h"

typedef uint32_t UM_Word;

void mapSegment(UArray_T memorySegments, UM_Word index, int length);
void unmapSegment(UArray_T memorySegments, UM_Word index);
UM_Word segmentedLoad(UArray_T memorySegments, int ID, int offset);
void segmentedStore(UArray_T memorySegments, int ID, int offset, UM_Word
                       value);
UM_Word nextIndexToMap(Stack_T unmappedSegs);
void unmapIndex(Stack_T unmappedSegs, UM_Word index);
