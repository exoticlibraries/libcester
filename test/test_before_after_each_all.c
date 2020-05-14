/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose --cester-noisolation */

#include <exotic/cester.h>
#include <stdio.h>

CESTER_BEFORE_ALL(test_instance,
    printf("Before All test, Arg Size %d\n", test_instance->argc);
    printf("==============================================================\n");
)

CESTER_BEFORE_EACH(test_instance, test_name, index,
    printf("Before Each test, Test %s, index %d\n", test_name, index);
)

CESTER_TEST(EmptyTestCase1, test_instance,
    printf("Test 1\n");
)

CESTER_TEST(EmptyTestCase2, test_instance,
    printf("Test 2\n");
)

CESTER_AFTER_EACH(test_instance, test_name, index,
    printf("After Each test, Test %s, index %d\n", test_name, index);
    printf("==============================================================\n");
)

CESTER_AFTER_ALL(test_instance,
    printf("After All test\n");
)
