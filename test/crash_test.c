/*!gcc {0} -I. -I../include/ -o out; ./out */

#include <exotic/cester.h>

CESTER_TEST(test_one, inst,
	cester_assert_equal(NULL, ((void*)0));	
)

CESTER_TEST(test_two, inst,
	cester_assert_ptr_equal(inst, NULL);	
)