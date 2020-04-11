//!gcc {0} -I../include/ -o test4; ./test4

#include <libopen/cester.h>
#include <stdio.h>

CESTER_NO_BEFORE_AFTER;

CESTER_TEST(Test1, test_instance) {
    cester_assert(1 == 2);
    cester_assert(1 == 1);
    cester_assert(1 == 3);
}

int main(int argc, char **argv) {
    //print version first option for no version
    //can also set attr from command line 
    // can specify the tests to run
    // try increse variable for detecting test case
    CESTER_REGISTER(Test1);
    return CESTER_RUN_ALL_TESTS(argc, argv);
}