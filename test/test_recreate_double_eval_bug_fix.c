/*!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

CESTER_BODY(

    int get_number(int *number) 
    {
        (*number)++;
        printf("Getting NUmber \n");
        return 20;
    }

)

CESTER_TEST(test_assert_cmp_int, test_instance,
    int number = 0;
    cester_assert_int_eq(get_number(&number), 20);
    cester_assert_int_eq(number, 1);
    cester_assert_int_ne(get_number(&number), 10);
    cester_assert_int_eq(number, 2);
)
