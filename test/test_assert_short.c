/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose-level=2 */

#include <exotic/cester.h>

CESTER_BEFORE_EACH(test_instance, _t, _i,
    short number = 21;
    test_instance->arg = (void*) (uintptr_t)number;
)

CESTER_TEST(test_assert_cmp_short, test_instance, 
    cester_assert_cmp_short(1, ==, 1, "%d %s %d");
    cester_assert_cmp_short(2, !=, 3, "%d %s %d");
)

CESTER_TEST(test_short_assertion, test_instance, 
    cester_assert_cmp_short(4, <, 5, "%d %s %d");
    cester_assert_cmp_short(7, >, 6, "%d %s %d");
)

CESTER_TEST(test_short_assertion_literal, test_instance, 
    short number = ((uintptr_t)test_instance->arg);
    cester_assert_short_eq(21, number);
    cester_assert_short_ne(30, number);
    cester_assert_short_gt(number, 10);
    cester_assert_short_ge(number, 9);
    cester_assert_short_lt(20, number);
    cester_assert_short_le(number, number);
)

CESTER_TEST(test_assert_cmp_unsigned_short, test_instance, 
    cester_assert_cmp_ushort(1, ==, 1, "%d %s %d");
    cester_assert_cmp_ushort(2, !=, 3, "%d %s %d");
)

CESTER_TEST(test_unsigned_short_assertion, test_instance, 
    cester_assert_cmp_ushort(4, <, 5, "%d %s %d");
    cester_assert_cmp_ushort(7, >, 6, "%d %s %d");
)

CESTER_TEST(test_unsigned_short_assertion_literal, test_instance, 
    unsigned short number = 124;
    cester_assert_ushort_eq(124, number);
    cester_assert_ushort_ne(30, number);
    cester_assert_ushort_gt(number, 10);
    cester_assert_ushort_ge(number, 9);
    cester_assert_ushort_lt(20, number);
    cester_assert_ushort_le(number, number);
)

