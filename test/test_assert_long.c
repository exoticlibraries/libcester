/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

CESTER_BEFORE_EACH(test_instance, _t, _i,
    long number = 2147483647;
    test_instance->arg = &number;
)

CESTER_TEST(test_assert_cmp_long, test_instance, 
    cester_assert_cmp_long(1, ==, 1, "%li %s %li");
    cester_assert_cmp_long(2147483647, !=, 3, "%li %s %li");
)

CESTER_TEST(test_long_assertion, test_instance, 
    cester_assert_cmp_long(4, <, 5, "%li %s %li");
    cester_assert_cmp_long(7, >, 6, "%li %s %li");
)

CESTER_TEST(test_long_assertion_literal, test_instance, 
    long number = *((long*)test_instance->arg);
    cester_assert_long_eq(2147483647, number);
    cester_assert_long_ne(30, number);
    cester_assert_long_gt(number, 10);
    cester_assert_long_ge(number, 9);
    cester_assert_long_lt(20, number);
    cester_assert_long_le(number, number);
)

CESTER_TEST(test_assert_cmp_unsigned_long, test_instance, 
    cester_assert_cmp_ulong(1, ==, 1, "%lu %s %lu");
    cester_assert_cmp_ulong(2, !=, 3, "%lu %s %lu");
)

CESTER_TEST(test_unsigned_long_assertion, test_instance, 
    cester_assert_cmp_ulong(4, <, 5, "%lu %s %lu");
    cester_assert_cmp_ulong(7, >, 6, "%lu %s %lu");
)

CESTER_TEST(test_unsigned_long_assertion_literal, test_instance, 
    unsigned long number = *((unsigned long*)test_instance->arg);
    cester_assert_ulong_eq(2147483647, number);
    cester_assert_ulong_ne(30, number);
    cester_assert_ulong_gt(number, 10);
    cester_assert_ulong_ge(number, 9);
    cester_assert_ulong_lt(20, number);
    cester_assert_ulong_le(number, number);
)