/*!gcc {0} -I. -I../include/ -o out; ./out */

#include <exotic/cester.h>

CESTER_TEST(test_example, _, 
    cester_assert_cmp_msg(10, >, 2, "is 10 greater than 2");
)