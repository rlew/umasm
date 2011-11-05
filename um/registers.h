#include <stdint.h>
#include <stdlib.h>

typedef uint32_t UM_Word;

void conditionalMove(int toSet, int original, int value);
void addition(int sum, int val1, int val2);
void multiplication(int product, int val1, int val2);
void division(int quotient, int numerator, int denominator);
void bitwiseAND(int result, int val1, int val2);
void loadValue(int reg, UM_Word value);
void input(int reg);
void output(int reg);
void halt();
