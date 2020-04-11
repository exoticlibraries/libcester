//!gcc {0} -I../include/ -o test2; ./test2

#include <exotic/cester.h>
#include <stdio.h>

CESTER_NO_AFTER_ALL;
CESTER_NO_AFTER_EACH;
CESTER_NO_BEFORE_ALL;
CESTER_NO_BEFORE_EACH;

CESTER_TEST(TestAssertion1, test_instance) {
    printf("Hello World %d\n", (1==2));
}

CESTER_TEST(CountCommandLineArg, test_instance) {
    printf("The number of command line arg: %d\n", test_instance->argc);
}

int main(int argc, char **argv) {
    CESTER_REGISTER_TEST(TestAssertion1);
    CESTER_REGISTER_TEST(CountCommandLineArg);
    return CESTER_RUN_ALL_TESTS(argc, argv);
}