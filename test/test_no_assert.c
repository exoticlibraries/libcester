/*!gcc -ansi -pedantic-errors {0} -IC -I../include/ -o out; ./out */

#include <exotic/cester.h>
#include <stdio.h>

CESTER_TEST(TestAssertion1, test_instance,
    printf("Hello World %d\n", (1==2));
)

CESTER_TEST(CountCommandLineArg, test_instance,
    printf("The number of command line arg: %d\n", test_instance->argc);
)
