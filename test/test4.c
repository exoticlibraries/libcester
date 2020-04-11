//!gcc {0} -I../include/ -o test3; ./test3

#include <libopen/cester.h>
#include <stdio.h>

CESTER_NO_AFTER_ALL;
CESTER_NO_AFTER_EACH;
CESTER_NO_BEFORE_ALL;
CESTER_NO_BEFORE_EACH;

CESTER_TEST(Test1, test_instance) {
    CESTER_ASSERT(1 == 2);
}

int main(int argc, char **argv) {
    CESTER_REGISTER(Test1);
    return CESTER_RUN_ALL_TESTS(argc, argv);
}