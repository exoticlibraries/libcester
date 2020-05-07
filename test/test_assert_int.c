//!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose

#include <exotic/cester.h>

CESTER_BEFORE_EACH(test_instance, _t, _i,
    int number = 21;
    test_instance->arg = &number;
)

CESTER_TEST(test_assert_cmp_int, test_instance, 
    cester_assert_cmp_int(1, ==, 1, "1 should be equal to 1");
    cester_assert_cmp_int(2, !=, 3, "three should not be than 3");
)

CESTER_TEST(test_int_assertion, test_instance, 
    cester_assert_cmp_int(4, <, 5, "4 should be less than 5");
    cester_assert_cmp_int(7, >, 6, "check if 7 is for sure greater than 6");
)

CESTER_TEST(test_int_assertion_literal, test_instance, 
    int number = *((int*)test_instance->arg);
    cester_assert_int_eq(21, number);
    cester_assert_int_ne(30, number);
    cester_assert_int_gt(number, 10);
    cester_assert_int_ge(number, 9);
    cester_assert_int_lt(20, number);
    cester_assert_int_le(number, number);
)

CESTER_TEST(test_assert_cmp_unsigned_int, test_instance, 
    cester_assert_cmp_uint(1, ==, 1, "%d %s %d");
    cester_assert_cmp_uint(2, !=, 3, "%d %s %d");
)

CESTER_TEST(test_unsigned_int_assertion, test_instance, 
    cester_assert_cmp_uint(4, <, 5, "%d %s %d");
    cester_assert_cmp_uint(7, >, 6, "%d %s %d");
)

CESTER_TEST(test_unsigned_int_assertion_literal, test_instance, 
    unsigned int number = *((unsigned int*)test_instance->arg);
    cester_assert_uint_eq(21, number);
    cester_assert_uint_ne(30, number);
    cester_assert_uint_gt(number, 10);
    cester_assert_uint_ge(number, 9);
    cester_assert_uint_lt(20, number);
    cester_assert_uint_le(number, number);
)