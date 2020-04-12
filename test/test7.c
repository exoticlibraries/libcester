//!gcc {0} -IC -I../include/ -o test7; ./test7
//this test shares data between tests

#include <exotic/cester.h>

CESTER_TEST(assert_false, test_instance,
    cester_assert_false(1 == 2);
    cester_assert_false(2 == 1);
)

CESTER_TEST(assert_true, test_instance,
    cester_assert_true(1 == 1);
    cester_assert_true(2 == 2);
)