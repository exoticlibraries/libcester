//!gcc {0} -I../include/ -o test2; ./test2

#include <libopen/cester.h>
#include <stdio.h>

CESTER_TEST(TestAssertion1, test_instance) {
    printf("Hello World %d\n", (1==2));
}

int main(int argc, char **argv) {
    return CESTER_RUN_ALL_TESTS(argc, argv);
}