//!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose

#include <exotic/cester.h>

CESTER_TEST(test_assert_cmp_msg, test_instance, 
    cester_assert_cmp_msg(NULL, ==, ((void*)0), "Check if NULL is same as ((void*)0)");
    cester_assert_cmp_msg(NULL, !=, "String", "is NULL equal to 'String'");
)

CESTER_TEST(test_assert_cmp_msg_arithmetic, test_instance, 
    cester_assert_cmp_msg(10, >, 2, "is 10 greater than 2");
    cester_assert_cmp_msg(3, <, 4, "is 3 less than 4");
    cester_assert_cmp_msg(2, <=, 2, "is 2 less than or equal to 2");
    cester_assert_cmp_msg(5, >=, 5, "is 5 greater than or equal to 5");
    cester_assert_cmp_msg(12, >, 11, "is 12 greater than 11");
    cester_assert_cmp_msg(6, ==, 6, "is 6 equal to 6");
    cester_assert_cmp_msg(0, !=, 1, "is 0 not equal to 1");
)