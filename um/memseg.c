#include <stdlib.h>
#include "memseg.h"
#include "uarray.h"
#include <stdio.h>
#include <mem.h>

/*
 * Increase the available set of IDs in unmappedIDs and sets the corresponding
 * IDs in mappedIDs to NULL
 */
static void resizeMem(Mem* memorySegments) {
    for(int i = Seq_length(memorySegments->mappedIDs); 
        i < Seq_length(memorySegments->mappedIDs) * 2; i++) {
        UM_Word* value;
        NEW(value);
        *value = i;
        Seq_addhi(memorySegments->unmappedIDs, value);
        Seq_put(memorySegments->mappedIDs, i, NULL);
    }

}

/*
 * Allocates memory for the mapped and unmapped IDs in memory that can be used
 * to created mapped memory segments
 */
void instantiateMem(Mem* mem, int length) {
    mem->mappedIDs = Seq_new(length);
    mem->unmappedIDs = Seq_new(length);
    
    mem->i = 5;
    for(int i = 0; i < length; i++) {
        UM_Word* value;
        NEW(value);
        *value = i;
        Seq_addhi(mem->mappedIDs, NULL);
        Seq_addhi(mem->unmappedIDs, value);
    }
}

/*
 * Maps a segment in memory by marking an ID as in use and allocating a
 * segment of memory of the specified length. Returns the index of the mapped
 * segment
 */
UM_Word mapSegment(Mem* memorySegments, int length) {
    if(Seq_length(memorySegments->unmappedIDs) == 0){
        resizeMem(memorySegments);
    }

    UArray_T segment = UArray_new(length, sizeof(UM_Word));
    
    // Initializing each UM_Word in the memory segment to 0
    for(int i = 0; i < length; i++) {
        UM_Word* elem = UArray_at(segment, i);
        *elem = 0;
    }

    UM_Word* ID = (UM_Word*)Seq_remlo(memorySegments->unmappedIDs);
    UM_Word index = *ID;
    FREE(ID);
    Seq_put(memorySegments->mappedIDs, index, segment);

    return index;
}

/*
 * Returns an ID to the pool of available IDs and frees all associated memory
 * with the given ID
 */
void unmapSegment(Mem* memorySegments, UM_Word index) {
    UArray_T segmentID = Seq_get(memorySegments->mappedIDs, index);
    UArray_free(&segmentID);
    Seq_put(memorySegments->mappedIDs, index, NULL);
    UM_Word* value;
    NEW(value);
    *value = index;
    Seq_addlo(memorySegments->unmappedIDs, value);
}

/*
 * Returns the memory segment stored at the specified ID and offset
 */
UM_Word segmentedLoad(Mem* memorySegments, int ID, int offset){
  return *(UM_Word*)UArray_at((UArray_T)Seq_get(memorySegments->mappedIDs,
  ID), offset);
}

/*
 * Stores the value passed at the specified index and offset in the memory
 * segments
 */
void segmentedStore(Mem* memorySegments, int ID, int offset, UM_Word
                       value){
    UM_Word* word = UArray_at((UArray_T)Seq_get(memorySegments->mappedIDs, ID),
                              offset);
    *word = value;
}

void freeMem(Mem* memorySegments) {
    while(Seq_length(memorySegments->mappedIDs) != 0) {
        UArray_T seg = Seq_remlo(memorySegments->mappedIDs);
        if(seg != NULL) {
            UArray_free(&seg);
        }
    }
    while(Seq_length(memorySegments->unmappedIDs) != 0) {
        UM_Word* ID = Seq_remlo(memorySegments->unmappedIDs);
        FREE(ID);
    }
    Seq_free(&memorySegments->mappedIDs);
    Seq_free(&memorySegments->unmappedIDs);
    FREE(memorySegments);
}
