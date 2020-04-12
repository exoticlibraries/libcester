//!gcc {0} -IC -I../include/ -o test6; ./test6
//this test shares data between tests

#include <exotic/cester.h>

CESTER_BEFORE_ALL(test_instance,
    test_instance->arg = "Hello World";
)

CESTER_TEST(check_number_equals, test_instance,
    cester_assert_false(cester_string_equals(test_instance->arg, "Hello World"));
)

CESTER_TEST(validate_shared_arg, test_instance,
    cester_assert_true(cester_string_equals(test_instance->arg, "Hello World"));
    cester_assert_false(cester_string_equals(test_instance->arg, "World"));
    cester_assert_false(cester_string_equals(test_instance->arg, "Hello"));
)