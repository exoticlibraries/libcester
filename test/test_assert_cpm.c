/*!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

CESTER_TEST(test_assert_cmp, test_instance, 
    cester_assert_cmp(CESTER_NULL, ==, ((void*)0));
    cester_assert_cmp(CESTER_NULL, !=, "String");
)

CESTER_TEST(test_assert_cmp_arithmetic, test_instance, 
    cester_assert_cmp(10, >, 2);
    cester_assert_cmp(3, <, 4);
    cester_assert_cmp(2, <=, 2);
    cester_assert_cmp(5, >=, 5);
    cester_assert_cmp(6, ==, 6);
    cester_assert_cmp(0, !=, 1);
)
