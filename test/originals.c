
#ifndef ORIGINALS
#define ORIGINALS
#include "originals.h"

char *the_original_field = (char*) "Adewale Azeez";

int multiply_by(void) {
    return 2;
}

int multiply_a_number(int a) {
    return a * multiply_by() ;
}

int power_of(int* num1, int num2) {
    return *num1 * num2;
}

char *get_author_name(void) {
    return the_original_field;
}

#endif
