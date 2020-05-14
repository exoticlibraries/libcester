/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out */

#include <exotic/cester.h>

CESTER_BODY(

typedef struct a_struct {
    int index ;
    char* value;
} AStruct;

)

CESTER_TEST(definitely_crahses, test_instance,
    int *p = NULL;
    *p=0xdead;
)

CESTER_TEST(segfault_test_null_ptr, test_instance,
    int *p = NULL;
    AStruct* arg_value ;
    cester_assert_equal(arg_value->value, NULL);
    cester_assert_equal(arg_value->value[21], '~');
    *p=0xdead;
)

CESTER_TEST(no_segfault, test_instance,
    int *p = NULL;
    AStruct* arg_value = (AStruct*) malloc(sizeof(AStruct*));
    arg_value->index = 20;
    cester_assert_equal(arg_value, NULL);
    free(arg_value);
    *p=0xdead;
)

CESTER_TEST(this_should_notbe_affected, test_instance,
    cester_assert_equal(NULL, NULL);
)

CESTER_TEST(this_aftermath, test_instance,
    cester_assert_equal(1, 1);
)

CESTER_OPTIONS(
    CESTER_TEST_SHOULD_SEGFAULT(definitely_crahses);
    CESTER_TEST_SHOULD_SEGFAULT(segfault_test_null_ptr);
    CESTER_TEST_SHOULD_FAIL(no_segfault);
)
