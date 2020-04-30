//!gcc {0} -I. -I../include/ -o out; ./out

#include <exotic/cester.h>

CESTER_BODY(

typedef struct a_struct {
    int index ;
    char* value;
} AStruct;

)

CESTER_TEST(leak_pointer_bytes, test_instance,
    AStruct* arg_value = malloc(sizeof(AStruct*));
    cester_assert_not_equal(arg_value, NULL);
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
    free(str3);
    free(str4);
    free(str5);
    free(str6);
)

CESTER_TEST(leak_chars, test_instance,
    char* str = malloc(sizeof(char)* 3);
    char* str1 = malloc(sizeof(char)* 31);
    void* str2 = malloc(sizeof(void)* 3);
    char* str3 = malloc(sizeof(char)* 65);
    void* str4 = malloc(sizeof(void)* 12);
    cester_assert_not_equal(str, NULL);
    free(str2);
    free(str4);
)

CESTER_TEST(no_leak_here, test_instance,
    AStruct* arg_value;
)