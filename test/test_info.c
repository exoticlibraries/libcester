/*!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose */

/*#define CESTER_NO_PRINT_INFO*/
#define CESTER_NO_MAIN
#include <exotic/cester.h>
#include "originals.c"

CESTER_MOCK_SIMPLE_FUNCTION(multiply_by(void), int, 5)

CESTER_MOCK_FUNCTION(power_of(int* num1, int num2), int, 
    int return_val = *num1;
    while (num2-->1) {
        return_val *= *num1;
    }
    return return_val;
)

CESTER_BODY(
	static int index__ = 500;
)

CESTER_COMMENT(
    This is a multiline comment in \n
    the source code this text is printed out \n
    before any test cases is executed.
)

CESTER_BEFORE_ALL(test_instance, 
    test_instance->arg = (void*) "exoticlibs";
)

CESTER_BEFORE_EACH(test_instance, test_name, index,
    printf("Before Each test, Test %s, index %d\n", test_name, index);
)

CESTER_TEST(test_string, test_instance, 
    cester_assert_str_equal((char*)test_instance->arg, "exoticlibs");
    cester_assert_str_not_equal((char*)test_instance->arg, CESTER_NULL);
)

CESTER_TEST(test_string_alias, test_instance, 
    cester_assert_str_eq((char*)test_instance->arg, "exoticlibs");
    cester_assert_str_ne((char*)test_instance->arg, CESTER_NULL);
)

CESTER_TODO_TEST(write_test_after_implementation, test_instance,
    void *p = CESTER_NULL;
)

CESTER_SKIP_TEST(this_test_will_fail, test_instance,
    void *p = CESTER_NULL;
)

CESTER_SKIP_TEST(works_only_on_linux, test_instance,
    void *p = CESTER_NULL;
)

CESTER_AFTER_EACH(test_instance, test_name, index,
    printf("After Each test, Test %s, index %d\n", test_name, index);
    printf("==============================================================\n");
)

CESTER_AFTER_ALL(test_instance, 
    test_instance->arg = CESTER_NULL;
)

CESTER_OPTIONS(
    CESTER_NO_ISOLATION();
)

CESTER_BODY(
int main(int argc, char** argv) {
	CESTER_REGISTER_OPTIONS();
	CESTER_REGISTER_BEFORE_ALL();
	CESTER_REGISTER_BEFORE_EACH();
	CESTER_REGISTER_TEST(test_string);
	CESTER_REGISTER_TEST(test_string_alias);
	CESTER_REGISTER_SKIP_TEST(this_test_will_fail);
	CESTER_REGISTER_SKIP_TEST(works_only_on_linux);
	CESTER_REGISTER_TODO_TEST(write_test_after_implementation);
	CESTER_REGISTER_AFTER_ALL();
	CESTER_REGISTER_AFTER_EACH();
	return CESTER_RUN_ALL_TESTS(argc, argv);
}
)
