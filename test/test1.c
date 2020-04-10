//!gcc {0} -I../include/ -o test1; ./test1

#include <libopen/cester.h>
#include <stdio.h>

CESTER_BEFORE_ALL(test_instance) {
    printf("Before All test, Arg Size %d\n", test_instance->argc);
}

CESTER_BEFORE(test_instance, test_name) {
    printf("Before test %s \n", test_name);
}

CESTER_AFTER(test_instance, test_name) {
    printf("After test %s \n", test_name);
}

CESTER_AFTER_ALL(test_instance) {
    printf("After All test\n");
}

int main(int argc, char **argv) {
    CESTER_RUN_ALL_TESTS(argc, argv);
}