/*!g++ {0} -I. -I../include/ -o out; ./out --cester-verbose*/

/* #define CESTER_NO_SIGNAL */
#include <exotic/cester.h>

CESTER_BODY(

typedef struct a_struct {
    int index ;
    char* value;
} AStruct;

)

/*CESTER_BEFORE_ALL(test_instance, 
    printf("Press Ctrl+C to kill -> 'test_killed_by_user'\n");
)*/

CESTER_TEST(segfault_test, test_instance,
    AStruct* arg_value ;
    cester_assert_equal(arg_value->value, CESTER_NULL);
    cester_assert_equal(arg_value->value[21], '~');
)

/* uncomment for manual testing */
/*CESTER_TEST(test_killed_by_user, test_instance,
    while (1) {
        
    }
)*/

CESTER_TEST(last_test, test_instance,
    cester_assert_equal(((void*)0), CESTER_NULL);
)

CESTER_TEST(segfault_test_2, test_instance,
    AStruct* arg_value ;
    int *p = CESTER_NULL;
    cester_assert_equal(arg_value->value, CESTER_NULL);
    cester_assert_equal(arg_value->value[21], '~');
    *p=0xdead;
)

CESTER_TEST(last_test_2, test_instance,
    cester_assert_equal(((void*)0), CESTER_NULL);
)

CESTER_TEST(last_test_3, test_instance,
    cester_assert_equal(((void*)0), CESTER_NULL);
)


CESTER_TEST(last_test_7, test_instance,
    cester_assert_equal(((void*)0), CESTER_NULL);
)

CESTER_TEST(segfault_test_3, test_instance,
    AStruct* arg_value ;
    int *p = CESTER_NULL;
    cester_assert_equal(arg_value->value, CESTER_NULL);
    cester_assert_equal(arg_value->value[21], '~');
    *p=0xdead;
)


CESTER_TEST(segfault_test_4, test_instance,
    AStruct* arg_value ;
    int *p = CESTER_NULL;
    cester_assert_equal(arg_value->value, CESTER_NULL);
    cester_assert_equal(arg_value->value[21], '~');
    *p=0xdead;
)

CESTER_TEST(segfault_test_5, test_instance,
    AStruct* arg_value ;
    int *p = CESTER_NULL;
    cester_assert_equal(arg_value->value, CESTER_NULL);
    cester_assert_equal(arg_value->value[21], '~');
    *p=0xdead;
)

CESTER_OPTIONS(
    CESTER_TEST_SHOULD_FAIL(segfault_test);
    CESTER_TEST_SHOULD_SEGFAULT(segfault_test_2);
    CESTER_TEST_SHOULD_SEGFAULT(segfault_test_3);
    CESTER_TEST_SHOULD_SEGFAULT(segfault_test_4);
    CESTER_TEST_SHOULD_SEGFAULT(segfault_test_5);
)
