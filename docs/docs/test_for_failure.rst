
.. index::
	single: test_for_failure

Testing for failures
======================

In a scenerio where a test case is expected to fail. The cester CESTER_TEST_SHOULD macro and 
it variant can be used to set the expected result of a test case. The following macros are used 
to set a test case result: 

- `CESTER_TEST_SHOULD <./macros.html#cester-test-should>`_
- `CESTER_TEST_SHOULD_SEGFAULT <./macros.html#cester-test-should-segfault>`_
- `CESTER_TEST_SHOULD_FAIL <./macros.html#cester-test-should-fail>`_
- `CESTER_TEST_SHOULD_BE_TERMINATED <./macros.html#cester-test-should-be-terminated>`_
- `CESTER_TEST_SHOULD_LEAK_MEMORY <./macros.html#cester-test-should-leak-memory>`_
- `CESTER_REPORT_SUCCESS_REGARDLESS <./macros.html#cester-report-success-regardless>`_
- `CESTER_REPORT_FAILURE_REGARDLESS <./macros.html#cester-report-failure-regardless>`_
- `CESTER_TEST_SHOULD_NOT_RELEASE_STREAM <./macros.html#cester-test-should-not-release-stream>`_

The macro CESTER_TEST_SHOULD accepts the test case name as the first parameter and the expected 
result as the second parameter. By default the expected result for the test cases is 
**CESTER_RESULT_SUCCESS**. The expected test case must be set before the test case is executed, 
it can be set in the CESTER_OPTIONS or inside the main method.

The following are the possible expected result value: 

- CESTER_RESULT_SUCCESS
- CESTER_RESULT_FAILURE
- CESTER_RESULT_TERMINATED
- CESTER_RESULT_SEGFAULT
- CESTER_RESULT_MEMORY_LEAK
- CESTER_RESULT_UNRELEASED_STREAM

Example 1
'''''''''' 

One of test case below will case a segfault but the test will pass because segmentation fault is 
the expected result of the test case. 

.. code:: c

	//test.c
	#include <exotic/cester>

	CESTER_TEST(definitely_crahses, inst,
		int *p = NULL;
		*p=0xdead;
	)

	CESTER_OPTIONS(
		CESTER_TEST_SHOULD_SEGFAULT(definitely_crahses);
	)

.. code:: bash

	gcc test.c -I. -o test
	./test --cester-minimal
		
		+ (0.01s) definitely crahses

	Passed crash_test.c:5: in 'definitely_crahses' => Segfault as expected

	Ran 1 test(s) in 0.01 Seconds
	Synthesis: SUCCESS Tests: 1 | Passing: 1 | Failing: 0


In the example above without changing the expected test case result to CESTER_RESULT_SEGFAULT 
the test will fail. The line `CESTER_TEST_SHOULD_SEGFAULT(definitely_crahses);` can also be 
explicitly re written as `CESTER_TEST_SHOULD(definitely_crahses, CESTER_RESULT_SEGFAULT)`.

Example 2
''''''''''

The following test cases fails for different reason but the test is marked as passed because they 
are expected to fail.  

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(this_should_segfault, test_instance,
		cester_assert_char_eq(((char*)test_instance->arg)[12], ((char*)test_instance->arg)[2109]);
	)

	CESTER_TEST(this_should_fail, test_instance,
		cester_assert_not_equal(NULL, ((void*)0));
	)

	CESTER_TEST(this_should_pass, test_instance,
		cester_assert_equal(NULL, ((void*)0));
	)

	CESTER_TEST(this_should_segfault_also_fail, test_instance,
		cester_assert_char_eq(((char*)test_instance->arg)[12], ((char*)test_instance->arg)[2109]);
	)

	CESTER_TEST(this_should_leak_memory, test_instance,
		char* str = malloc(sizeof(char) * 12);
	)

	CESTER_TEST(test_stream_capture, test_instance, 
		CESTER_CAPTURE_STREAM(stdout);
	)

	CESTER_OPTIONS(
		CESTER_TEST_SHOULD_SEGFAULT(this_should_segfault);
		CESTER_TEST_SHOULD_FAIL(this_should_fail);
		CESTER_TEST_SHOULD_LEAK_MEMORY(this_should_leak_memory);
		CESTER_TEST_SHOULD(this_should_segfault_also_fail, CESTER_RESULT_FAILURE);
		CESTER_TEST_SHOULD_NOT_RELEASE_STREAM(test_stream_capture);
	)

.. code:: bash

	gcc test.c -I. -o test
	./test --cester-minimal
	
		+ (0.00s) this should segfault
		+ (0.00s) this should fail
		+ (0.00s) this should pass
		+ (0.00s) this should segfault also fail
		+ (0.01s) this should leak memory
		+ (0.00s) test stream capture

	Passed crash_test.c:5: in 'this_should_segfault' => Segfault as expected
	AssertionError crash_test.c:10: in 'this_should_fail' => not expecting 'NULL', received '((void*)0)'
	Passed crash_test.c:9: in 'this_should_fail' => Failed as expected
	Passed crash_test.c:17: in 'this_should_segfault_also_fail' => Failed as expected
	MemoryLeakError crash_test.c:22: in 'this_should_leak_memory' => Memory allocated in line '22' not freed. Leaking '12' Bytes
	Passed crash_test.c:21: in 'this_should_leak_memory' => Leaked memory as expected
	Passed crash_test.c:25: in 'test_stream_capture' => Have unreleased stream as expected

	Ran 5 test(s) in 0.02 Seconds
	Synthesis: SUCCESS Tests: 5 | Passing: 5 | Failing: 0


Example 3
'''''''''' 

The test case in the example below will fail and memory error will be reported. But the test 
will still be reported as success since the option CESTER_REPORT_SUCCESS_REGARDLESS() is specified.

.. code:: c

	//test.c
	#include <exotic/cester.h>

	CESTER_BEFORE_ALL(test_instance,
		char *str = (char *) malloc(20);
	)

	CESTER_TEST(test_assert_true, test_instance, 
		cester_assert_false(2 > 1); 
		cester_assert_false(test_instance != NULL); 
		cester_assert_false(test_instance->argc > 0);
	)

	CESTER_OPTIONS(
		CESTER_REPORT_SUCCESS_REGARDLESS();
	)


.. code:: bash

	gcc test.c -I. -o test
	./test --cester-minimal
		
		- (0.00s) test assert true

	EvaluationError test_always_success.c:10: in 'test_assert_true' expr => '(2 > 1)'
	EvaluationError test_always_success.c:11: in 'test_assert_true' expr => '(test_instance != NULL)'
	EvaluationError test_always_success.c:12: in 'test_assert_true' expr => '(test_instance->argc > 0)'
	MemoryLeakError test_always_success.c:6: in 'CESTER_BEFORE_ALL' => Memory allocated in line '6' not freed. Leaking '20' Bytes

	Ran 1 test(s) in 0.00 Seconds
	Synthesis: SUCCESS Tests: 1 | Passing: 0 | Failing: 1 | Errors: 1

	echo $?
	0


Example 4
'''''''''' 

The test case in the example below will pass with no error . But the test be reported as failure 
since the option CESTER_REPORT_FAILURE_REGARDLESS() is specified.

.. code:: c

	//test.c
	#include <exotic/cester.h>

	CESTER_TEST(test_assert_true, test_instance, 
		cester_assert_true(2 > 1); 
		cester_assert_true(test_instance != NULL); 
		cester_assert_true(test_instance->argc > 0);
	)

	CESTER_OPTIONS(
		CESTER_REPORT_FAILURE_REGARDLESS();
	)


.. code:: bash

	gcc test.c -I. -o test
	./test --cester-minimal
		
		+ (0.00s) test assert true


	Ran 1 test(s) in 0.00 Seconds
	Synthesis: FAILURE Tests: 1 | Passing: 1 | Failing: 0

	echo $?
	1

