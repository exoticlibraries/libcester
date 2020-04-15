//!gcc test_mock_fields.c -I. -I../include/ -Wl,--wrap=the_original_field -o test_mock_fields; ./test_mock_fields

#include <exotic/cester.h>
#include "originals.c"

CESTER_MOCK_SIMPLE_FUNCTION(multiply_by, int, 5)

CESTER_TEST(assert_false, test_instance,
    cester_assert_equal(the_original_field, "Exotic Libs");
)

CESTER_OPTIONS(
    CESTER_VERBOSE();
    CESTER_MINIMAL();
)