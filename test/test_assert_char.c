/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

CESTER_BEFORE_ALL(test_instance,
    test_instance->arg = (void*) "libcester";
)

CESTER_TEST(test_assert_cmp_char, test_instance, 
    cester_assert_cmp_char('a', ==, 'a', "verify that a is same as a");
    cester_assert_cmp_char('b', !=, 'c', "check if b does not equal to c");
)

CESTER_TEST(test_char_assertion, test_instance, 
    cester_assert_cmp_char('a', <, 'b', "is a less than b?");
    cester_assert_cmp_char('d', >, 'c', "is d greater than c");
    cester_assert_cmp_char('e', <=, 'e', "validate that e is lesser than or equal to itself");
    cester_assert_cmp_char('f', >=, 'f', "check if f is also greater than or equal to itself");
    cester_assert_cmp_char('g', ==, 'g', "is g equal to itself?");
    cester_assert_cmp_char('h', !=, 'i', "am tired");
)

CESTER_TEST(test_char_assertion_literal, test_instance, 
    cester_assert_char_eq('i', ((char*)test_instance->arg)[1]);
    cester_assert_char_ne(((char*)test_instance->arg)[0], 'a');
    cester_assert_char_gt(((char*)test_instance->arg)[5], ((char*)test_instance->arg)[0]);
    cester_assert_char_ge(((char*)test_instance->arg)[2], ((char*)test_instance->arg)[2]);
    cester_assert_char_lt(((char*)test_instance->arg)[3], 'z');
    cester_assert_char_le('a', 'b');
)

CESTER_TEST(test_assert_cmp_uchar, test_instance, 
    cester_assert_cmp_uchar('a', ==, 'a', "verify that a is same as a");
    cester_assert_cmp_uchar('b', !=, 'c', "check if b does not equal to c");
)

CESTER_TEST(test_uchar_assertion, test_instance, 
    cester_assert_cmp_uchar('a', <, 'b', "is a less than b?");
    cester_assert_cmp_uchar('d', >, 'c', "is d greater than c");
    cester_assert_cmp_uchar('e', <=, 'e', "validate that e is lesser than or equal to itself");
    cester_assert_cmp_uchar('f', >=, 'f', "check if f is also greater than or equal to itself");
    cester_assert_cmp_uchar('g', ==, 'g', "is g equal to itself?");
    cester_assert_cmp_uchar('h', !=, 'i', "am tired");
)

CESTER_TEST(test_uchar_assertion_literal, test_instance, 
    cester_assert_uchar_eq('i', ((char*)test_instance->arg)[1]);
    cester_assert_uchar_ne(((char*)test_instance->arg)[0], 'a');
    cester_assert_uchar_gt(((char*)test_instance->arg)[5], ((char*)test_instance->arg)[0]);
    cester_assert_uchar_ge(((char*)test_instance->arg)[2], ((char*)test_instance->arg)[2]);
    cester_assert_uchar_lt(((char*)test_instance->arg)[3], 'z');
    cester_assert_uchar_le('a', 'b');
)

CESTER_OPTIONS(
    CESTER_NO_ISOLATION();
    CESTER_VERBOSE_LEVEL(3);
    CESTER_PRINT_ERROR_ONLY(1);
)
