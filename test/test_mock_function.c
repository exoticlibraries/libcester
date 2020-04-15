//!gcc test_mock_function.c -I. -I../include/ -Wl,--wrap=multiply_by -o test_mock_function; ./test_mock_function

#include <exotic/cester.h>
#include "originals.c"

CESTER_MOCK_SIMPLE_FUNCTION(multiply_by, int, 5)

CESTER_TEST(assert_false, test_instance,
    cester_assert_equal(multiply_a_number(2), 10);
)

CESTER_OPTIONS(
    CESTER_VERBOSE();
    CESTER_MINIMAL();
)