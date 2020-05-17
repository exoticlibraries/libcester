/*!gcc {0} -I. -o out; ./out */

#include <exotic/cester.h>

CESTER_TEST(test_case_name, test_instance, 
    char* str = (char*) malloc(sizeof(char) * 12);
)

CESTER_OPTIONS(
    CESTER_TEST_SHOULD_LEAK_MEMORY(test_case_name);
)