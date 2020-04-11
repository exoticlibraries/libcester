//!gcc {0} -I../include/ -o test1; ./test1

#include <exotic/cester.h>
#include <stdio.h>

CESTER_NO_AFTER_EACH;
CESTER_NO_BEFORE_EACH;

CESTER_BEFORE_ALL(test_instance) {
    printf("Before All test, Arg Size %d\n", test_instance->argc);
}

CESTER_AFTER_ALL(test_instance) {
    printf("After All test\n");
}

int main(int argc, char **argv) {
    return CESTER_RUN_ALL_TESTS(argc, argv);
}