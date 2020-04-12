//!gcc {0} -IC -I../include/ -o test4; ./test4

#include <exotic/cester.h>

CESTER_TEST(Test1, test_instance,
    cester_assert(1 == 2);
    cester_assert(1 == 1);
    cester_assert(1 == 3);
)

CESTER_TEST(Test2, test_instance,
    cester_assert(2 == 2);
    cester_assert(4 != 1);
    cester_assert(1 != 3);
)

