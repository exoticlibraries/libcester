/*!gcc {0} -I. -I../include/ -o out; ./out --cester-noisolation*/

#include <exotic/cester.h>

CESTER_BODY(
typedef struct arg {
    int number;
} Arg;
)

CESTER_BEFORE_ALL(test_instance,
    Arg *arg = (Arg *) malloc(sizeof(Arg));
    arg->number = 21;
    test_instance->arg = arg;
)

CESTER_TEST(test_int_assertion_literal, test_instance, 
    int number = ((Arg*)(test_instance->arg))->number;
    cester_assert_int_eq(21, number);
    cester_assert_int_ne(30, number);
    cester_assert_int_gt(number, 10);
    cester_assert_int_ge(number, 9);
    cester_assert_int_lt(20, number);
    cester_assert_int_le(number, number);
)

CESTER_AFTER_ALL(test_instance,
    free(test_instance->arg);
)

CESTER_TEST(test_unsigned_int_assertion_literal, test_instance, 
    unsigned int number = ((Arg*)(test_instance->arg))->number;
    cester_assert_uint_eq(21, number);
    cester_assert_uint_ne(30, number);
    cester_assert_uint_gt(number, 10);
    cester_assert_uint_ge(number, 9);
    cester_assert_uint_lt(20, number);
    cester_assert_uint_le(number, number);
)
