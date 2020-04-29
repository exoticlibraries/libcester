//!gcc {0} -I. -I../include/ -o test_segfault; ./test_segfault

#include <exotic/cester.h>

CESTER_BODY(

typedef struct a_struct {
    int index ;
    char* value;
} AStruct;

)

CESTER_TEST(segfault_test_null_ptr, test_instance,
    AStruct* arg_value ;
    cester_assert_equal(1, 1);
    cester_assert_equal(2, 2);
    cester_assert_equal(arg_value->value, NULL);
    cester_assert_equal(arg_value, NULL);
    cester_assert_equal(arg_value->index, 0);
)

CESTER_TEST(no_segfault, test_instance,
    AStruct* arg_value = malloc(sizeof(AStruct*));
    arg_value->index = 20;
    test_instance->arg = arg_value;
    cester_assert_equal(arg_value, NULL);
    cester_assert_equal(arg_value->value, NULL);
    cester_assert_equal(arg_value, NULL);
)

CESTER_TEST(this_should_notbe_affected, test_instance,
    cester_assert_equal(NULL, NULL);
)

CESTER_TEST(this_aftermath, test_instance,
    cester_assert_equal(1, 1);
)

CESTER_OPTIONS(
    //CESTER_VERBOSE();
)