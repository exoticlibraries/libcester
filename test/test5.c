//!gcc {0} -IC -I../include/ -o test2; ./test2

#include <exotic/cester.h>
#include <stdio.h>

CESTER_TEST(assert_not, test_instance,
    cester_assert_not(1 == 2);
    cester_assert_not(2 == 1);
)

CESTER_TEST(assert, test_instance,
    cester_assert(1 == 1);
    cester_assert(2 == 2);
)

CESTER_OPTIONS(
    CESTER_NOCOLOR();
    CESTER_VERBOSE();
    CESTER_MINIMAL();
)