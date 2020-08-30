/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose */

#ifndef __BASE_FILE__
#define CESTER_NO_MAIN
#endif
#include <exotic/cester.h>

CESTER_TEST(test_assert_false, test_instance, 
    cester_assert_not_null("NotNull");
)

CESTER_COMMENT(
    This is a multiline comment in \n
    the source code this text is printed out \n
    before any test cases is executed.
)

#ifndef __BASE_FILE__
CESTER_BODY(
int main(int argc, char** argv) {
	CESTER_REGISTER_TEST(test_assert_false);
	return CESTER_RUN_ALL_TESTS(argc, argv);
}
)
#endif
