/*!gcc {0} -I. -I../include/ -o out; ./out --cester-output=tap */

#ifndef __BASE_FILE__
#define CESTER_NO_MAIN
#endif
#include <exotic/cester.h>

CESTER_BODY(

typedef struct a_struct {
    int index ;
    char* value;
} AStruct;

)

CESTER_BEFORE_ALL(test_instance,
    AStruct* arg_value = (AStruct*) malloc(sizeof(AStruct*));
    arg_value->index = 20;
    arg_value->value = "A string";
    test_instance->arg = arg_value;
)

CESTER_TEST(modify_test_instance, test_instance,
    AStruct* arg_value = ((AStruct*)test_instance->arg);
    cester_assert_equal(arg_value->index++, 20);
    cester_assert_equal(arg_value->value, "A string");
    arg_value->value = "Unknown";
)

CESTER_TODO_TEST(after_we_write_the_array_struct, test_instance,
    cester_assert_nothing();
)

CESTER_TEST(test_direct_variables, test_instance,
    cester_assert_int_eq(((AStruct*)test_instance->arg)->index, 21);
    cester_assert_str_not_equal(((AStruct*)test_instance->arg)->value, "A string");
    cester_assert_str_equal(((AStruct*)test_instance->arg)->value, "Unknown");
)

CESTER_TODO_TEST(write_test_after_implementation, test_instance,
    cester_assert_nothing();
)

CESTER_SKIP_TEST(skip_this_test_it_breaks, test_instance,
    cester_assert_true('a' == 'b');
)

CESTER_OPTIONS(
    CESTER_OUTPUT_TAP();
    CESTER_VERBOSE();
    CESTER_MINIMAL();
    CESTER_NO_ISOLATION();
)

#ifndef __BASE_FILE__
CESTER_BODY(
int main(int argc, char** argv) {
    CESTER_REGISTER_BEFORE_ALL();
    CESTER_REGISTER_SKIP_TEST(skip_this_test_it_breaks);
	CESTER_REGISTER_TEST(modify_test_instance);
	CESTER_REGISTER_TEST(test_direct_variables);
    CESTER_REGISTER_TODO_TEST(write_test_after_implementation);
    CESTER_REGISTER_TODO_TEST(after_we_write_the_array_struct);
	return CESTER_RUN_ALL_TESTS(argc, argv);
}
)
#endif
