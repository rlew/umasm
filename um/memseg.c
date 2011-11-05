#include "stack.h"
#include <stdlib.h>
#include "memseg.h"

UM_Word nextIndexToMap(Stack_T t)
{
  (void)t;
  return 0;
}

void mapSegment(UArray_T memorySegments, UM_Word index, int length) {
  (void) memorySegments;
  (void) index;
  (void) length;
}
void unmapSegment(UArray_T memorySegments, UM_Word index) {
  (void) memorySegments;
  (void) index;
}
UM_Word segmentedLoad(UArray_T memorySegments, int ID, int offset){
  (void) memorySegments;
  (void) ID;
  (void) offset;
  return 0;
}
void segmentedStore(UArray_T memorySegments, int ID, int offset, UM_Word
                       value){
  (void) memorySegments;
  (void) ID;
  (void) offset;
  (void) value;
}
void unmapIndex(Stack_T unmappedSegs, UM_Word index){
  (void) unmappedSegs;
  (void) index;
}
