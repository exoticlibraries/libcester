//!gcc {0} -IC -I../include/ -o out; ./out

#include <exotic/cester.h>

CESTER_TEST(Test1, test_instance,
    cester_assert_true(1 != 2);
    cester_assert_true(1 == 1);
    cester_assert_true(5 >= 3);
)

CESTER_TEST(Test2, test_instance,
    cester_assert_true(2 == 2);
    cester_assert_true(4 != 1);
    cester_assert_true(1 != 3);
)

