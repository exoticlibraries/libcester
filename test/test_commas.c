/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

#ifdef __STDC_VERSION__
CESTER_TEST(test_commas, test_instance,
    int num1 = 1, num2 = 2, num3 = 3;
    cester_assert_equal(num1, 1);
    cester_assert_not_equal(num1, num2);
)
#else
CESTER_TEST(test_commas, test_instance, 
    int num1 = 1;
    int num2 = 2;
    cester_assert_equal(num1, 1);
    cester_assert_not_equal(num1, num2);
)
#endif

