/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

CESTER_TEST(test_assert_equal, test_instance, 
    cester_assert_equal(NULL, ((void*)0));
)

CESTER_TEST(test_assert_not_equal, test_instance, 
    cester_assert_not_equal(NULL, "NotEqual");
)