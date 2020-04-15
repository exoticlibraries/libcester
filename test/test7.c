//!gcc {0} -IC -I../include/ -o test7; ./test7

#include <exotic/cester.h>

#define CESTER_NO_MAIN

CESTER_TEST(assert_false, test_instance,
    cester_assert_equal(1, 1);
)

CESTER_TEST(assert_true, test_instance,
    cester_assert_not_equal(2, 1);
)

CESTER_BODY(

int main(int argc, char **argv) {
    return CESTER_RUN_ALL_TESTS(argc, argv);
}

)