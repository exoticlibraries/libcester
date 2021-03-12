/*!cls; g++ -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose-level=2 */

#include <exotic/cester.h>

CESTER_TEST(stdin_assertions, inst, {
    CESTER_CAPTURE_STDIN();

    fprintf(stdin, "This suppose to terminate the program but it been captured \n");
    cester_assert_stdin_stream_content_equal("This suppose to terminate the program but it been captured \n");
    cester_assert_stdin_stream_content_contain("\n");

    CESTER_RESET_STDIN();
    cester_assert_stdin_stream_content_not_equal("This suppose to terminate the program but it been captured \n");
    cester_assert_stdin_stream_content_not_contain("\n");

    CESTER_RELEASE_STDIN();
})

CESTER_TEST(stdout_assertions, inst, {
    CESTER_CAPTURE_STDOUT();

    printf("This will not be shown in terminal\n");
    printf("Because it has been captured by libester\n");
    cester_assert_stdout_stream_content_equal("This will not be shown in terminal\nBecause it has been captured by libester\n");
    cester_assert_printf_equal("This will not be shown in terminal\nBecause it has been captured by libester\n");
    cester_assert_stdout_stream_content_contain("terminal");
    cester_assert_printf_contain("captured by libester");
    
    CESTER_RESET_STDOUT();
    cester_assert_stdout_stream_content_not_equal("This will not be shown in terminal\nBecause it has been captured by libester\n");
    cester_assert_printf_not_equal("This will not be shown in terminal\nBecause it has been captured by libester\n");
    cester_assert_stdout_stream_content_not_contain("terminal");
    cester_assert_printf_not_contain("captured by libester");

    CESTER_RELEASE_STDOUT();
})

CESTER_TEST(stderr_assertions, inst, {
    CESTER_CAPTURE_STDERR();

    fprintf(stderr, "This hidden from view\n");
    fprintf(stderr, "Because it captured by libester");
    cester_assert_stderr_stream_content_equal("This hidden from view\nBecause it captured by libester");
    cester_assert_stderr_stream_content_contain("Because it captured by libester");

    CESTER_RESET_STDERR();
    cester_assert_stderr_stream_content_not_equal("This hidden from view\nBecause it captured by libester");
    cester_assert_stderr_stream_content_not_contain("Because it captured by libester");

    CESTER_RELEASE_STDERR();
})

CESTER_TEST(stream_assertions, inst, {
    CESTER_CAPTURE_STREAM(stdout);

    fprintf(stdout, "This suppose to terminate the program but it been captured \n");
    cester_assert_stream_content_equal(stdout, "This suppose to terminate the program but it been captured \n");
    cester_assert_stream_content_contain(stdout, "\n");

    CESTER_RESET_STREAM(stdout);
    cester_assert_stream_content_not_equal(stdout, "This suppose to terminate the program but it been captured \n");
    cester_assert_stream_content_not_contain(stdout, "\n");

    puts("Even for put ");
    putchar('A');
    cester_assert_printf_equal("Even for put \nA");
    cester_assert_printf_contain("A");

    CESTER_RELEASE_STREAM(stdout);
})

CESTER_OPTIONS(
    CESTER_NO_ISOLATION();
    CESTER_VERBOSE_LEVEL(2);
    /*CESTER_CHANGE_STREAM_CAPTURE_TM_FOLDER("./build/");*/
)
