//!gcc test_mock.c -I. -I../include/ -Wl,--wrap=the_original_field -o test_mock; ./test_mock

#include <exotic/cester.h>
#include "originals.c"

CESTER_MOCK_FUNCTION(power_of(int* num1, int num2), int, 
    int return_val = *num1;
    while (num2-->1) {
        return_val *= *num1;
    }
    return return_val;
)

CESTER_TEST(check_mocked_function, test_instance,
    int num = 2;
    cester_assert_equal(power_of(&num, 3), 8);
)