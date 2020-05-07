//!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose

#include <exotic/cester.h>

CESTER_BEFORE_EACH(test_instance, _t, _i,
    long long number = 214748364734234;
    test_instance->arg = &number;
)

CESTER_TEST(test_assert_cmp_long, test_instance, 
    cester_assert_cmp_long(1, ==, 1, "%d %s %d");
    cester_assert_cmp_long(2, !=, 3, "%d %s %d");
)

CESTER_TEST(test_llong_assertion, test_instance, 
    cester_assert_cmp_long(4, <, 5, "%d %s %d");
    cester_assert_cmp_long(7, >, 6, "%d %s %d");
)

CESTER_TEST(test_llong_assertion_literal, test_instance, 
    long long number = *((long long*)test_instance->arg);
    cester_assert_llong_eq(214748364734234, number);
    cester_assert_llong_ne(30, number);
    cester_assert_llong_gt(number, 10);
    cester_assert_llong_ge(number, 9);
    cester_assert_llong_lt(20, number);
    cester_assert_llong_le(number, number);
)

CESTER_TEST(test_assert_cmp_unsigned_long, test_instance, 
    cester_assert_cmp_ulong(1, ==, 1, "%d %s %d");
    cester_assert_cmp_ulong(2, !=, 3, "%d %s %d");
)

CESTER_TEST(test_unsigned_llong_assertion, test_instance, 
    cester_assert_cmp_ulong(4, <, 5, "%d %s %d");
    cester_assert_cmp_ulong(7, >, 6, "%d %s %d");
)

CESTER_TEST(test_unsigned_llong_assertion_literal, test_instance, 
    unsigned long long number = *((unsigned long long*)test_instance->arg);
    cester_assert_ullong_eq(214748364734234, number);
    cester_assert_ullong_ne(30, number);
    cester_assert_ullong_gt(number, 10);
    cester_assert_ullong_ge(number, 9);
    cester_assert_ullong_lt(20, number);
    cester_assert_ullong_le(number, number);
)