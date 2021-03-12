/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose --cester-minimal */

#include <exotic/cester.h>

#ifndef __CESTER_STDC_VERSION__
    #define CESTER_ASSERT_ULLONG(type) cester_assert_llong_##type
    #define CESTER_ASSERT_ULLONG_CMP cester_assert_cmp_long
#else 
    #define CESTER_ASSERT_ULLONG(type) cester_assert_ullong_##type
    #define CESTER_ASSERT_ULLONG_CMP cester_assert_cmp_ulong
#endif

CESTER_BEFORE_EACH(test_instance, _t, _i,
    __CESTER_LONG_LONG__ number = 214734234;
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
    __CESTER_LONG_LONG__ number = *((__CESTER_LONG_LONG__*)test_instance->arg);
    cester_assert_llong_eq(214734234, number);
    cester_assert_llong_ne(30, number);
    cester_assert_llong_gt(number, 10);
    cester_assert_llong_ge(number, 9);
    cester_assert_llong_lt(20, number);
    cester_assert_llong_le(number, number);
)

CESTER_TEST(test_assert_cmp_unsigned_long, test_instance, 
    CESTER_ASSERT_ULLONG_CMP(1, ==, 1, "%d %s %d");
    CESTER_ASSERT_ULLONG_CMP(2, !=, 3, "%d %s %d");
)

CESTER_TEST(test_unsigned_llong_assertion, test_instance, 
    CESTER_ASSERT_ULLONG_CMP(4, <, 5, "%d %s %d");
    CESTER_ASSERT_ULLONG_CMP(7, >, 6, "%d %s %d");
)

CESTER_TEST(test_unsigned_llong_assertion_literal, test_instance, 
    unsigned __CESTER_LONG_LONG__ number = *((unsigned __CESTER_LONG_LONG__*)test_instance->arg);
    CESTER_ASSERT_ULLONG(eq)(214734234, number);
    CESTER_ASSERT_ULLONG(ne)(30, number);
    CESTER_ASSERT_ULLONG(gt)(number, 10);
    CESTER_ASSERT_ULLONG(ge)(number, 9);
    CESTER_ASSERT_ULLONG(lt)(20, number);
    CESTER_ASSERT_ULLONG(le)(number, number);
)
