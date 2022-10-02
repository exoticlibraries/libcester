/*!cls; gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose-level=1 */

/*#define CESTER_NO_STREAM_CAPTURE*/
#include <exotic/cester.h>

CESTER_TEST(capture_release_stdin, inst, {
    CESTER_CAPTURE_STDIN();
    fprintf(stdin, "This suppose to terminate the program but it been captured \n");
    fprintf(stdin, "Ctrl+C wrong");
    CESTER_RELEASE_STDIN();
})

CESTER_TEST(capture_release_stdout, inst, {
    CESTER_CAPTURE_STDOUT();
    printf("This will not be shown in terminal\n");
    printf("Because it has been captured by libester\n");
    CESTER_RELEASE_STDOUT();
})

CESTER_TEST(capture_release_stderr, inst, {
    CESTER_CAPTURE_STDERR();
    fprintf(stderr, "This suppose to terminate the program but it been captured \n");
    fprintf(stderr, "Ctrl+C wrong");
    CESTER_RELEASE_STDERR();
})

