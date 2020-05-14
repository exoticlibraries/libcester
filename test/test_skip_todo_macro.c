/*!gcc {0} -I. -I../include/ -o out; ./out*/

#ifndef __BASE_FILE__
#define CESTER_NO_MAIN
#endif
#include <exotic/cester.h>

CESTER_SKIP_TEST(skip_this_test_it_fails, test_instance,
    cester_assert_true(1 == 2);
)

CESTER_TODO_TEST(a_test_to_implement, test_instance,
    cester_assert_nothing();
)

CESTER_TEST(test_assert_false, test_instance, 
    cester_assert_not_null("NotNull");
)

CESTER_TODO_TEST(write_test_after_implementation, test_instance,
    cester_assert_nothing();
)

CESTER_SKIP_TEST(skip_this_test_it_breaks, test_instance,
    cester_assert_true('a' == 'b');
)

#ifndef __BASE_FILE__
CESTER_BODY(
int main(int argc, char** argv) {
	CESTER_REGISTER_TEST(test_assert_false);
	CESTER_REGISTER_SKIP_TEST(skip_this_test_it_breaks);
	CESTER_REGISTER_SKIP_TEST(skip_this_test_it_fails);
    CESTER_REGISTER_TODO_TEST(a_test_to_implement);
	CESTER_REGISTER_TODO_TEST(write_test_after_implementation);
	return CESTER_RUN_ALL_TESTS(argc, argv);
}
)
#endif
