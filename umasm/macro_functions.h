#include "um-opcode.h"
#include "seq.h"
#include "bitpack.h"

Seq_T move(int A, int B, int C, Seq_T instructions);
Seq_T complement(int A, int B, int C, Seq_T instructions);
Seq_T negate(int A, int B, int C, Seq_T instructions);
Seq_T subtract(int A, int B, int C, int temp, Seq_T instructions);
Seq_T bitwise_and(int A, int B, int C, Seq_T instructions);
Seq_T bitwise_or(int A, int B, int C, Seq_T instructions);
