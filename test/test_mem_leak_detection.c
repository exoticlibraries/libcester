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
    arg_value = malloc(sizeof(AStruct*));
    cester_assert_not_equal(arg_value, NULL);
    CESTER_DO_MEMTEST();
)

CESTER_TEST(free_null_leak_byte, test_instance,
    char* str = malloc(sizeof(char)* 3);
    char* str1 = malloc(sizeof(char)* 5);
    char* str2 = malloc(sizeof(char)* 51);
    char* str3 = malloc(sizeof(char)* 1);
    char* str4 = malloc(sizeof(char)* 40);
    char* str5 = malloc(sizeof(char)* 12);
    char* str6 = malloc(sizeof(char)* 21);
    cester_assert_not_equal(str, NULL);
    str = NULL;
    free(str);
    free(str1);
    free(str2);
    free(str4);
    free(str5);
    free(str6);
)

CESTER_TEST(leak_chars_bytes, test_instance,
    char* str = malloc(sizeof(char)* 3);
    char* str1 = malloc(sizeof(char)* 31);
    void* str2 = malloc(sizeof(3));
    char* str3 = malloc(sizeof(char)* 65);
    void* str4 = malloc(sizeof(12));
    cester_assert_not_equal(str, NULL);
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