/*!gcc {0} -ansi -pedantic-errors -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

CESTER_TEST(test_pointer_address, test_instance, 
    char* addr1;
    char* null_addr;
    cester_ptr_to_str(&addr1, test_instance);
    cester_ptr_to_str(&null_addr, CESTER_NULL);
    
    cester_assert_str_equal(addr1, addr1);
    cester_assert_str_not_equal(null_addr, addr1);
    
    free(addr1);
    free(null_addr);
)


CESTER_TEST(test_pointer, test_instance, 
    cester_assert_ptr_equal(test_instance, test_instance);
    cester_assert_ptr_not_equal(test_instance->arg, test_instance);
)
