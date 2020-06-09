/*!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose */

#define CESTER_NO_TIME

#include <exotic/cester.h>

CESTER_TEST(quick_test, test_instance, 
    cester_assert_true(1);
)
