/*!cls; gcc -ansi -pedantic-errors {0} -I. -I../include/ -o out; ./out --cester-verbose-level=1 */

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

CESTER_TEST(get_stdin_content, inst, {
    CESTER_CAPTURE_STDIN();

    fprintf(stdin, "This is the content 1\n");
    fprintf(stdin, "Second line no nl ending");
    cester_assert_str_equal(CESTER_STDIN_CONTENT(), "This is the content 1\nSecond line no nl ending");

    CESTER_RELEASE_STDIN();
})

CESTER_TEST(get_stdout_content, inst, {
    CESTER_CAPTURE_STDOUT();

    printf("Hello World\r\b\n");
    printf("\tThis is libcester from Exotic libraries \n\ng");
    cester_assert_str_equal(CESTER_STDOUT_CONTENT(), "Hello World\r\b\n\tThis is libcester from Exotic libraries \n\ng");

    CESTER_RELEASE_STDOUT();
})

CESTER_TEST(get_stderr_content, inst, {
    CESTER_CAPTURE_STDERR();

    fprintf(stderr, "This is the std err \nstream");
    cester_assert_str_equal(CESTER_STDERR_CONTENT(), "This is the std err \nstream");

    CESTER_RELEASE_STDERR();
})

CESTER_TEST(reset_get_stdin_content, inst, {
    CESTER_CAPTURE_STDIN();

    fprintf(stdin, "This is the content 1\n");
    fprintf(stdin, "Second line no nl ending");
    cester_assert_str_equal(CESTER_STDIN_CONTENT(), "This is the content 1\nSecond line no nl ending");
    CESTER_RESET_STDIN();
    cester_assert_str_not_equal(CESTER_STDIN_CONTENT(), "This is the content 1\nSecond line no nl ending");

    CESTER_RELEASE_STDIN();
})

CESTER_TEST(reset_get_stdout_content, inst, {
    CESTER_CAPTURE_STDOUT();

    printf("Hello World\r\b\n");
    printf("\tThis is libcester from Exotic libraries \n\ng");
    cester_assert_str_equal(CESTER_STDOUT_CONTENT(), "Hello World\r\b\n\tThis is libcester from Exotic libraries \n\ng");
    CESTER_RESET_STDOUT();
    cester_assert_str_not_equal(CESTER_STDOUT_CONTENT(), "Hello World\r\b\n\tThis is libcester from Exotic libraries \n\ng");

    CESTER_RELEASE_STDOUT();
})

CESTER_TEST(reset_get_stderr_content, inst, {
    CESTER_CAPTURE_STDERR();

    fprintf(stderr, "This is the std err \nstream");
    cester_assert_str_equal(CESTER_STDERR_CONTENT(), "This is the std err \nstream");
    CESTER_RESET_STDERR();
    cester_assert_str_not_equal(CESTER_STDERR_CONTENT(), "This is the std err \nstream");

    CESTER_RELEASE_STDERR();
})

CESTER_TEST(fail_unrelease_captured_stream, inst, {
    CESTER_CAPTURE_STDIN();
    CESTER_CAPTURE_STDOUT();
    CESTER_CAPTURE_STDERR();

    fprintf(stdin, "This suppose to terminate the program but it been captured \n");
    fprintf(stdin, "Ctrl+C wrong");

    fprintf(stdout, "This will not be shown in terminal\n");
    fprintf(stdout, "Because it has been captured by libester\n");

    fprintf(stderr, "This will not be shown in terminal for stderr\n");
    fprintf(stderr, "Because it has been captured by libester\n");
})

CESTER_OPTIONS(
    CESTER_TEST_SHOULD_NOT_RELEASE_STREAM(fail_unrelease_captured_stream);
    /*CESTER_CHANGE_STREAM_CAPTURE_TM_FOLDER("./build/");*/
)

