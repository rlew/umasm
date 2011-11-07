#include "registers.h"
#include "memseg.h"
#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

/*
 * Stores the value at $r[original] in $r[toSet] if value is not 0. Called
 * with command 0.
 */
void conditionalMove(int toSet, int original, int value){
    (void)toSet;
    (void)original;
    (void)value;
}

/*
 * Adds the values in $r[val1] and $r[val2] and takes the first 32 significant 
 * bits and stores the sum in $r[sum]. Called with command 1.
 */
void addition(int sum, int val1, int val2) {
    (void)sum;
    (void)val1;
    (void)val2;
}

/*
 * Multiplies $r[val1] and $r[val2] and takes the first 32 signifcant bits
 * and stores the product in $r[product]. Called with command 2.
 */
void multiplication(int product, int val1, int val2) {
    (void)product;
    (void)val1;
    (void)val2;
}

/*
 * Divides the value in $r[numerator] by that found in $r[denominator] and
 * stores the result in $r[quotient]. Called with command 3.
 */
void division(int quotient, int numerator, int denominator) {
    (void)quotient;
    (void)numerator;
    (void)denominator;
}

/* 
 * Performs bitwise NOT and AND operations on the values in $r[val1] and
 * $r[val2] and stores the result in $r[result]. Called with command 4.
 */
void bitwiseNAND(int result, int val1, int val2) {
    (void)result;
    (void)val1;
    (void)val2;
}

/*
 * Load the value passed into the register $r[reg]. Called with command 13.
 */
void loadValue(int reg, UM_Word value) {
    (void)reg;
    (void)value;
}

/*
 * Reads from std input and stores in the register $r[reg]. Called with
 * command 11.
 */
void input(int reg) {
    (void)reg;
}

/*
 * Reads the value in $r[reg] to std output. Called with command 10.
 */
void output(int reg) {
    (void)reg;
}

/*
 * Halts all program operations and frees all corresponding memory. Called
 * with command 7.
 */
void halt(){
}
