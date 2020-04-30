//!gcc {0} -I. -I../include/ -o out; ./out

#include <exotic/cester.h>

#define CESTER_NO_MAIN

CESTER_BEFORE_ALL(test_instance,
    printf("Before All\n");
)

CESTER_BEFORE_EACH(test_instance, test_name, index,
    printf("Before Each %s\n", test_name);
)

CESTER_TEST(test1, test_instance,
	cester_assert_equal(NULL, NULL);
)

CESTER_TEST(test2, test_instance,
	cester_assert_not_equal(NULL, NULL);
)

CESTER_AFTER_EACH(test_instance, test_name, index,
    printf("After Each %s\n", test_name);
)

CESTER_AFTER_ALL(test_instance,
    printf("After All\n");
)

CESTER_OPTIONS(
    CESTER_NOCOLOR();
)

CESTER_BODY(
int main(int argc, char** argv) {
	CESTER_REGISTER_BEFORE_ALL();
	CESTER_REGISTER_OPTIONS();
	CESTER_REGISTER_BEFORE_EACH();
	CESTER_REGISTER_TEST(test1);
	CESTER_REGISTER_TEST(test2);
	CESTER_REGISTER_AFTER_ALL();
	CESTER_REGISTER_AFTER_EACH();
	return CESTER_RUN_ALL_TESTS(argc, argv);
}
)