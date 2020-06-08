/*!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

#undef unix
#undef _WIN32

CESTER_TEST(quick_test, test_instance, 
    cester_assert_true(1);
)
