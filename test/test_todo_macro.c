//!gcc {0} -I. -I../include/ -o out; ./out

#ifndef __BASE_FILE__
#define CESTER_NO_MAIN
#endif
#include <exotic/cester.h>

CESTER_TODO_TEST(a_test_to_implement, test_instance,
    
)

CESTER_TODO_TEST(write_test_after_implementation, test_instance,
    
)

#ifndef __BASE_FILE__
CESTER_BODY(
int main(int argc, char** argv) {
	CESTER_REGISTER_TODO_TEST(a_test_to_implement);
	CESTER_REGISTER_TODO_TEST(write_test_after_implementation);
	return CESTER_RUN_ALL_TESTS(argc, argv);
}
)
#endif
