//!g++ {0} -I. -I../include/ -o out; ./out

#include <exotic/cester.h>

CESTER_TEST(check_shared_arg, test_instance,
   cester_assert_equal(NULL, ((void*)0));
   cester_assert_not_equal(2, 1);
)