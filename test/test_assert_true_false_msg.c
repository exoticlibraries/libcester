/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

CESTER_TEST(test_assert_true_msg, test_instance, 
    cester_assert_true_msg(2 > 1, "is 2 greater than 1?"); 
    cester_assert_true_msg(test_instance != CESTER_NULL, "the test_instance must have been initialized"); 
    cester_assert_true_msg(test_instance->argc > 0, "The number of argument sent is not zero");
)

CESTER_TEST(test_assert_false_msg, test_instance, 
    cester_assert_false_msg(2 < 1, "yea 1 is definitely less than 2"); 
    cester_assert_false_msg(test_instance == CESTER_NULL, "The test instance is CESTER_NULL? sure no"); 
)
