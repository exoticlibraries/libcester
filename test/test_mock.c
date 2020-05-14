/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ '-Wl,--wrap=multiply_by' '-Wl,--wrap=power_of' -o out; ./out */

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
    int num = 5;
    cester_assert_equal(power_of(&num, 10), 9765625);
)

CESTER_BEFORE_ALL(test_instance,
    FILE* output = fopen("./result.txt", "w+");
    CESTER_CHANGE_STREAM(output);
)

CESTER_OPTIONS(
    CESTER_NO_ISOLATION();
)
