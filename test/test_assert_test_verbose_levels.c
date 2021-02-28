/*!clang -m32 {0} -I. -I../include/ -o out.exe; ./out.exe --cester-verbose */

#include <exotic/cester.h>

CESTER_TEST(test_assert_equal, test_instance,
    cester_assert_ptr_equal(CESTER_NULL, ((void*)0));
)

CESTER_TEST(test_assert_equal_one, test_instance,
    int one = 1;
    int two = 2;
    cester_assert_int_ne(one, two);
)

CESTER_TEST(test_assert_equal_two, test_instance,
    char *value = (char *)"Equal";
    cester_assert_str_not_equal(value, "NotEqual");
)

CESTER_TEST(test_assert_not_equal, test_instance, 
    cester_assert_not_equal(CESTER_NULL, "NotEqual");
    cester_assert_true(1);
)


CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(3);
)

