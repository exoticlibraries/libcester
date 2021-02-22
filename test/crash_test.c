/*!gcc {0} -I. -I../include/ -o out; ./out --cester-verbose */

#include <exotic/cester.h>

CESTER_TEST(test_stdout, test_inst, 
    CESTER_CAPTURE_STDOUT();

    printf("This will not be shown in terminal\n");
		puts("Because it has been captured by libester");
    cester_assert_stdout_stream_content_equal("This will not be shown in terminal\nBecause it has been captured by libester\n");
    cester_assert_stdout_stream_content_contain("terminal");

    CESTER_RELEASE_STDOUT();
)
