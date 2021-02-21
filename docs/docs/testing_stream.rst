
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
- `CESTER_RESET_STREAM <./macros.html#cester-reset-function>`_

You cannot capture a stream outside a test case
it uses the folder in the working directory ./build/libcester/captured_streams/ for captured streams
