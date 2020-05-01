//!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose

#include <exotic/cester.h>

CESTER_TEST(test_assert_null, test_instance, 
    cester_assert_null(NULL);
)

CESTER_TEST(test_assert_false, test_instance, 
    cester_assert_not_null("NotNull");
)