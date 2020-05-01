//!gcc {0} -I. -I../include/ -o out; ./out

#include <exotic/cester.h>

CESTER_BEFORE_ALL(test_instance, 
    test_instance->arg = "exoticlibs";
)

CESTER_TEST(test_string, test_instance, 
    cester_assert_equal(test_instance->arg, "exoticlibs");
    cester_assert_string_equal(test_instance->arg, "exoticlibs");
    cester_assert_not_equal(NULL, test_instance->arg);
    cester_assert_string_not_equal(test_instance->arg, NULL);
)