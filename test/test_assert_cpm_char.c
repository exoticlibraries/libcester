//!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose

#include <exotic/cester.h>

CESTER_BEFORE_ALL(test_instance,
    test_instance->arg = "libcester";
)

CESTER_TEST(test_assert_cmp_char, test_instance, 
    cester_assert_cmp_char('a', ==, 'a');
    cester_assert_cmp_char('b', !=, 'c');
)

CESTER_TEST(test_char_assertion, test_instance, 
    cester_assert_cmp_char('a', <, 'b');
    cester_assert_cmp_char('d', >, 'c');
    cester_assert_cmp_char('e', <=, 'e');
    cester_assert_cmp_char('f', >=, 'f');
    cester_assert_cmp_char('g', ==, 'g');
    cester_assert_cmp_char('h', !=, 'i');
)

CESTER_TEST(test_char_assertion_literal, test_instance, 
    cester_assert_char_eq('i', ((char*)test_instance->arg)[1]);
    cester_assert_char_ne(((char*)test_instance->arg)[0], 'a');
    cester_assert_char_gt(((char*)test_instance->arg)[5], ((char*)test_instance->arg)[0]);
    cester_assert_char_ge(((char*)test_instance->arg)[2], ((char*)test_instance->arg)[2]);
    cester_assert_char_lt(((char*)test_instance->arg)[3], 'z');
    cester_assert_char_le('a', 'b');
)