/*!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

CESTER_TEST(test_case_name, test_instance, 
    int size = 2;
    cester_assert_int_eq(0, size);
)
