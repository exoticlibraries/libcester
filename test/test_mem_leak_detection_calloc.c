/*!gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out*/

/* #define CESTER_NO_MEM_TEST */
#include <exotic/cester.h>

CESTER_BODY(

typedef struct a_struct {
    int index ;
    char* value;
} AStruct;

)

CESTER_TEST(skip_mem_test, test_instance,
    AStruct* arg_value;
    CESTER_NO_MEMTEST();
    arg_value = (AStruct*) calloc(1, sizeof(AStruct));
    cester_assert_not_equal(arg_value, CESTER_NULL);
    CESTER_DO_MEMTEST();
)

CESTER_TEST(free_null_leak_byte, test_instance,
    char* str = (char*) calloc(3, sizeof(char));
    char* str1 = (char*)calloc(5, sizeof(char));
    char* str2 = (char*)calloc(51, sizeof(char));
    char* str3 = (char*)calloc(1, sizeof(char));
    char* str4 = (char*)calloc(40, sizeof(char));
    char* str5 = (char*)calloc(12, sizeof(char));
    char* str6 = (char*)calloc(21, sizeof(char));
    cester_assert_not_equal(str, CESTER_NULL);
    str = CESTER_NULL;
    free(str);
    free(str1);
    free(str2);
    free(str4);
    free(str5);
    free(str6);
)

CESTER_TEST(leak_chars_bytes, test_instance,
    char* str = (char*)calloc(3, sizeof(char));
    char* str1 = (char*)calloc(31, sizeof(char));
    void* str2 = (char*)calloc(1, sizeof(3));
    char* str3 = (char*)calloc(65, sizeof(char));
    void* str4 = (char*)calloc(1, sizeof(12));
    cester_assert_not_equal(str, CESTER_NULL);
    free(str2);
    free(str4);
)

CESTER_TEST(no_leak_here, test_instance,
    AStruct* arg_value;
)

CESTER_OPTIONS(
    CESTER_TEST_SHOULD_LEAK_MEMORY(free_null_leak_byte);
    CESTER_TEST_SHOULD_LEAK_MEMORY(leak_chars_bytes);
)
