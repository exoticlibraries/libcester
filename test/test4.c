//!gcc {0} -I../include/ -o test4; ./test4

#include <exotic/cester.h>
#include <stdio.h>

CESTER_NO_BEFORE_AFTER;

CESTER_TEST(Test1, test_instance) {
    cester_assert(1 == 2);
    cester_assert(1 == 1);
    cester_assert(1 == 3);
}

CESTER_TEST(Test2, test_instance) {
    cester_assert(2 == 2);
    cester_assert(4 != 1);
    cester_assert(1 != 3);
}

int main(int argc, char **argv) {
    //print version first option for no version
    // can specify the tests to run
    // try increse variable for detecting test case
    CESTER_REGISTER(Test1);
    CESTER_REGISTER(Test2);
    return CESTER_RUN_ALL_TESTS(argc, argv);
}