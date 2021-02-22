
.. index::
	single: testing_output_streams

Testing Output Streams
=======================

libcester allows the testing of file stream without any intrusion in the code. With this feature you can simply 
output any value using `printf`, `fprintf`, `puts` or any other stream method and validate the output without 
actually writing to those streams. An example is writing some ansi code into the trminal using printf but in 
your unit test you want to actually validate what is written to the terminal without actually outputing 
it into the terminal.

The following macros are used for testing file streams.

- `CESTER_CAPTURE_STREAM <./macros.html#cester-capture-stream>`_
- `CESTER_RELEASE_STREAM <./macros.html#cester-release-stream>`_
- `CESTER_RESET_STREAM <./macros.html#cester-reset-stream>`_
- `CESTER_CHANGE_STREAM_CAPTURE_TM_FOLDER <./macros.html#cester-change-stream-capture-tm-folder>`_

Ensure a stream that was captured is freed after the assertion or at the end of a test case, it bad 
practice to capture a stream outside a test case at it might be impossible to track the stream and ensure 
it properly released.

Stream assertion macros
-------------------------

Any of the following macros can be used to test the stream after it has been captured.

- `cester_assert_stream_content_equal <./assertions.html#cester-assert-stream-content-equal>`_
- `cester_assert_stream_content_contain <./assertions.html#cester-assert-stream-content-contain>`_
- `cester_assert_stream_content_not_equal <./assertions.html#cester-assert-stream-content-not-equal>`_
- `cester_assert_stream_content_not_contain <./assertions.html#cester-assert-stream-content-not-contain>`_
- `cester_assert_stdout_stream_content_equal <./assertions.html#cester-assert-stdout-stream-content-equal>`_
- `cester_assert_stdout_stream_content_contain <./assertions.html#cester-assert-stdout-stream-content-contain>`_
- `cester_assert_stdout_stream_content_not_equal <./assertions.html#cester-assert-stdout-stream-content-not-equal>`_
- `cester_assert_stdout_stream_content_not_contain <./assertions.html#cester-assert-stdout-stream-content-not-contain>`_
- `cester_assert_stderr_stream_content_equal <./assertions.html#cester-assert-stderr-stream-content-equal>`_
- `cester_assert_stderr_stream_content_contain <./assertions.html#cester-assert-stderr-stream-content-contain>`_
- `cester_assert_stderr_stream_content_not_equal <./assertions.html#cester-assert-stderr-stream-content-not-equal>`_
- `cester_assert_stderr_stream_content_not_contain <./assertions.html#cester-assert-stderr-stream-content-not-contain>`_
- `cester_assert_stdin_stream_content_equal <./assertions.html#cester-assert-stdin-stream-content-equal>`_
- `cester_assert_stdin_stream_content_contain <./assertions.html#cester-assert-stdin-stream-content-contain>`_
- `cester_assert_stdin_stream_content_not_equal <./assertions.html#cester-assert-stdin-stream-content-not-equal>`_
- `cester_assert_stdin_stream_content_not_contain <./assertions.html#cester-assert-stdin-stream-content-not-contain>`_

Standard streams helper macros
--------------------------------

There are helpers macros to quickly works on the standard streams `stdout`, `stderr`, `stdin`.

- `CESTER_CAPTURE_STDOUT <./macros.html#cester-capture-stdout>`_
- `CESTER_RELEASE_STDOUT <./macros.html#cester-release-stdout>`_
- `CESTER_RESET_STDOUT <./macros.html#cester-reset-stdout>`_
- `CESTER_CAPTURE_STDERR <./macros.html#cester-capture-stderr>`_
- `CESTER_RELEASE_STDERR <./macros.html#cester-release-stderr>`_
- `CESTER_RESET_STDERR <./macros.html#cester-reset-stderr>`_
- `CESTER_CAPTURE_STDIN <./macros.html#cester-capture-stdin>`_
- `CESTER_RELEASE_STDIN <./macros.html#cester-release-stdin>`_
- `CESTER_RESET_STDIN <./macros.html#cester-reset-stdin>`_

Testing stdout stream
----------------------

The stdout stream is where data written to printf, puts is sent to by default, the data sent can be validated 
using the stream assertion functions.

The example below tests the data written to stdout

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(test_stdout, test_inst, 
		CESTER_CAPTURE_STDOUT();

		printf("This will not be shown in terminal\n");
		puts("Because it has been captured by libester");
		cester_assert_stdout_stream_content_equal("This will not be shown in terminal\nBecause it has been captured by libester\n");
		cester_assert_stdout_stream_content_contain("terminal");

		CESTER_RESET_STDOUT();
		puts("Hello World");
		cester_assert_stdout_stream_content_equal("Hello World\n");
		
		CESTER_RELEASE_STDOUT();
	)

Compiling the test above will give the following output

.. code:: c

		
	+ (0.02s) test stdout


	Ran 1 test(s) in 0.02 Seconds
	Synthesis: SUCCESS Tests: 1 | Passing: 1 | Failing: 0

In the above test as seen in the code printf is used as it will be used in regular programs but because 
it been captured cester. the test case is able to make some assertion on the data written, 
the data will not be written to the terminal as stdout is not itself at that point.

.. note::

	- CESTER_CAPTURE_STDOUT() is alias for `CESTER_CAPTURE_STREAM(stdout)`
	- CESTER_RESET_STDOUT() is alias for `CESTER_RESET_STREAM(stdout)`
	- CESTER_RELEASE_STDOUT() is alias for `CESTER_RELEASE_STREAM(stdout)`

	It required to be explicit with the stream to capture if no helper macro is provider by cester.

Also the stream was reset with the macro `CESTER_RESET_STDOUT` so the old data is completely removed and fresh 
data can be written to the stream, else if the stream is not reset the new data will simply be appended to the 
existing data.

.. warning:: 

	if the system the test case is executed on does not have a file system, has very limited file system or
	does not allow read and/or write to the /tmp folder, libcester will not be able to capture the stream 
	and the stream assertions will fail, and it even possible for the test case to segfault.