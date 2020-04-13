//!gcc {0} -IC -I../include/ -o test7; ./test7
//this test shares data between tests

#include <exotic/cester.h>

CESTER_TEST(assert_false, test_instance,
    cester_assert_equal(1, 1);
)

CESTER_TEST(assert_true, test_instance,
    cester_assert_not_equal(2, 1);
)

CESTER_OPTIONS(
    CESTER_VERBOSE();
    CESTER_MINIMAL();
)