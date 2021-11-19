/*!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

CESTER_BEFORE_ALL(test_instance, 
    test_instance->arg = (void*) "exoticlibs";
)

CESTER_TEST(test_string, test_instance, 
    cester_assert_str_equal((char*)test_instance->arg, "exoticlibs");
    cester_assert_str_not_equal((char*)test_instance->arg, CESTER_NULL);
)

CESTER_TEST(test_string_alias, test_instance, 
    cester_assert_str_eq((char*)test_instance->arg, "exoticlibs");
    cester_assert_str_ne((char*)test_instance->arg, CESTER_NULL);
)

CESTER_OPTIONS(
    CESTER_NO_ISOLATION();
)
