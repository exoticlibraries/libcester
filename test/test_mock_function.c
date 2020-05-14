/*!gcc {0} -I. -I../include/ '-Wl,--wrap=multiply_by' '-Wl,--wrap=power_of' -o out.exe; ./out*/

#include <exotic/cester.h>
#include "originals.c"

CESTER_MOCK_SIMPLE_FUNCTION(multiply_by(), int, 5)

CESTER_MOCK_FUNCTION(power_of(int* num1, int num2), int, 
    int return_val = *num1;
    while (num2-->1) {
        return_val *= *num1;
    }
    return return_val;
)

CESTER_TEST(check_mocked_function, test_instance,
    int num = 2;
    cester_assert_int_eq(multiply_a_number(2), 10);
    cester_assert_int_eq(power_of(&num, 3), 8);
)

CESTER_OPTIONS(
    CESTER_VERBOSE();
    CESTER_MINIMAL();
)
