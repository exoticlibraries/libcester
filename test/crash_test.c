//!gcc {0} -I. -I../include/ -o out; ./out

#define CESTER_NO_MAIN
#include <exotic/cester.h>

CESTER_TEST(test1, test_instance,
	cester_assert_equal(NULL, NULL);
)

CESTER_TEST(test2, test_instance,
	cester_assert_not_equal(NULL, NULL);
)

CESTER_BODY(
int main(int argc, char** argv) {
	CESTER_REGISTER_TEST(test1);
	CESTER_REGISTER_TEST(test2);
	return CESTER_RUN_ALL_TESTS(argc, argv);
}
)