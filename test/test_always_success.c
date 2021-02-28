/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose; $LastExitCode */

#include <exotic/cester.h>

CESTER_TEST(test_assert_true, test_instance, 
    cester_assert_false(2 > 1); 
    cester_assert_false(test_instance != CESTER_NULL); 
    cester_assert_false(test_instance->argc > 0);
)

CESTER_TEST(test_assert_false, test_instance, 
    cester_assert_true(2 < 1); 
    cester_assert_true(test_instance == CESTER_NULL); 
)

CESTER_OPTIONS(
    CESTER_REPORT_SUCCESS_REGARDLESS();
)
