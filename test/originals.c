
#ifndef ORIGINALS
#define ORIGINALS
#include "originals.h"

char *the_original_field = "Adewale Azeez";

int multiply_by() {
    return 2;
}

int multiply_a_number(int a) {
    return a * multiply_by() ;
}

int power_of(int* num1, int num2) {
    return *num1 * num2;
}

char *get_author_name() {
    return the_original_field;
}

#endif