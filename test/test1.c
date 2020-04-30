//!gcc {0} -IC -I../include/ -o out; ./out

#include <exotic/cester.h>
#include <stdio.h>

CESTER_BEFORE_ALL(test_instance,
    printf("Before All test, Arg Size %d\n", test_instance->argc);
)

CESTER_AFTER_ALL(test_instance,
    printf("After All test\n");
)