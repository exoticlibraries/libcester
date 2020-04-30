//!gcc {0} -I. -I../include/ -o out; ./out

#include <stdio.h>
#include <stdlib.h>

void* my_malloc(size_t size, const char *file, int line, const char *func)
{

    void *p = malloc(size);
    printf ("Allocated = %s, %i, %s, %p[%li]\n", file, line, func, p, size);

    /*Link List functionality goes in here*/

    return p;
}

#define CESTER_TEST(x, y) void x() { y }

#define malloc(X) my_malloc( X, __FILE__, __LINE__, __FUNCTION__)

CESTER_TEST(test_one, 
    char* str = malloc(sizeof(char)* 3);
    str = "adewale";
    printf("RES: %s\n", str);
)

CESTER_TEST(test_two, 
    char* str = malloc(sizeof(char)* 3);
    str = "adewale";
    printf("RES: %s\n", str);
)

int main()
{
    test_one();
    test_two();
    return 0;
}