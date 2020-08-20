/*!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

#undef        __USE_POSIX
#undef        __USE_POSIX2
#undef        __USE_POSIX199309
#undef        __USE_POSIX199506

CESTER_TEST(quick_test, test_instance, 
    cester_assert_true(1);
)
