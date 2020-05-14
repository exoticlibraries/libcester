/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out*/

#ifndef __BASE_FILE__
#define CESTER_NO_MAIN
#endif
#include <exotic/cester.h>

CESTER_TEST(test1, test_instance,
	cester_assert_equal(NULL, NULL);
)

#ifndef __BASE_FILE__
CESTER_BODY(
int main(int argc, char** argv) {
	CESTER_REGISTER_TEST(test1);
	return CESTER_RUN_ALL_TESTS(argc, argv);
}
)
#endif
