//!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose

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
    AStruct* arg_value = malloc(sizeof(AStruct*));
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

CESTER_TEST(test_direct_variables, test_instance,
    cester_assert_equal(((AStruct*)test_instance->arg)->index, 20);
    cester_assert_equal(((AStruct*)test_instance->arg)->value, "A string");
    cester_assert_not_equal(((AStruct*)test_instance->arg)->value, "Unknown");
)

CESTER_OPTIONS(
    CESTER_OUTPUT_JUNITXML();
)

#ifndef __BASE_FILE__
CESTER_BODY(
int main(int argc, char** argv) {
	CESTER_REGISTER_TEST(test_assert_false);
	return CESTER_RUN_ALL_TESTS(argc, argv);
}
)
#endif