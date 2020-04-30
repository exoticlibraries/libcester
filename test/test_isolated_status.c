//!gcc {0} -I. -I../include/ -o out; ./out

#include <exotic/cester.h>

CESTER_BODY(

typedef struct a_struct {
    int index ;
    char* value;
} AStruct;

)

CESTER_TEST(segfault_test, test_instance,
    AStruct* arg_value ;
    cester_assert_equal(arg_value->value, NULL);
    cester_assert_equal(arg_value->value[21], '~');
)

CESTER_TEST(test_killed_by_user, test_instance,
    while (1) {
        cester_assert_true(1);
    }
)
