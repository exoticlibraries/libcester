//!gcc {0} -I. -I../include/ '-Wl,--wrap=multiply_by' '-Wl,--wrap=power_of' -o test_no_mock; ./test_no_mock

#include <exotic/cester.h>
#include "originals.c"

#define CESTER_NO_MOCK

CESTER_MOCK_SIMPLE_FUNCTION(multiply_by(), int, 5)

CESTER_TEST(check_mocked_function, test_instance,
    int num = 2;
    cester_assert_equal(multiply_a_number(2), 4);
)

CESTER_OPTIONS(
    CESTER_MINIMAL();
)