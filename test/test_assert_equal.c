/*!clang++ -ansi -pedantic-errors {0} -I. -I../include/ -o out.exe; ./out.exe --cester-verbose */

#include <exotic/cester.h>

CESTER_TEST(test_assert_equal, test_instance, 
    cester_assert_equal(CESTER_NULL, ((void*)0));
)

CESTER_TEST(test_assert_not_equal, test_instance, 
    cester_assert_not_equal(CESTER_NULL, "NotEqual");
)

CESTER_OPTIONS(
    CESTER_VERBOSE_LEVEL(3);
    CESTER_PRINT_ERROR_ONLY(1);
)
