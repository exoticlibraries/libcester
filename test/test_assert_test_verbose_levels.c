/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

CESTER_TEST(test_assert_equal, test_instance,
    char *value = (char *)"Equal";
    int one = 1;
    int two = 2;
    cester_assert_ptr_equal(NULL, ((void*)0));
    cester_assert_str_not_equal(value, "NotEqual");
    cester_assert_int_ne(one, two);
)

CESTER_TEST(test_assert_not_equal, test_instance, 
    cester_assert_not_equal(NULL, "NotEqual");
    cester_assert_true(1);
)


CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(3);
)

