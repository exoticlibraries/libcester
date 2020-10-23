
.. index::
	single: output_formats

Output Formats
================

The option `--cester-output=` is used to specify which format to print the output, the value 
after = must be a valid output format in cester. The following output format are currently 
supported.

- `Text`_
- `JunitXML`_
- `Tap`_
- `Tap Version 13`_

.. warning::

	If the output of the tests is directed to a file on a unix, linux variant OS the color 
	bytes will be written into the file along with the test outputs. Use the flag 
	**--cester-nocolor** to disable colored output. Colored output can also be disabled from 
	within the source using the macro **CESTER_NOCOLOR()**.

Various output format can be generated for the snippet below.

.. code:: c

	//test.c
	#include <exotic/cester.h>

	CESTER_TEST(test_assert_equal, inst, 
		cester_assert_equal(NULL, ((void*)0));
	)

	CESTER_TEST(test_assert_fail, inst, 
		cester_assert_not_equal(NULL, ((void*)0));
	)

	CESTER_TEST(segfault_test, inst, 
		int *p = NULL;
		*p=0xdead;
	)

	CESTER_TODO_TEST(to_do_later, inst, 
		
	)

	CESTER_SKIP_TEST(skip_this_test, inst,
		int *p = NULL;
		*p=0xdead;
	)

	CESTER_TEST(test_assert_not_equal, inst, 
		cester_assert_not_equal(NULL, "NotEqual");
	)


Compile the test with the command below:

.. code:: bash

	gcc test.c -I. -o test


Instead of printing to the terminal the output can be redirected to a file using the redirection 
character **>** or changing the output stream using the macro CESTER_CHANGE_STREAM before the 
test cases start running. E.g.

.. code:: c

	//...
	CESTER_BEFORE_ALL(inst,
		FILE* output = fopen("./result.txt", "w+");
		CESTER_CHANGE_STREAM(output);
	)
	//...


Text
------

By default plain text format is generated but with colorful output, the command line option 
`--cester-nocolor` is used to disable colored output. The option **--cester-ouput=text** can 
also be specified to print output as text. This can be set in the code before the test cases start 
running with CESTER_OUTPUT_TEXT();

To generate a text output for the snippet above 

.. code:: text
	
	./test --cester-verbose --cester-minimal --cester-output=text
		
	+ (0.01s) test assert equal
	- (0.01s) test assert fail
	- (0.00s) segfault test
	o (0.00s) to do later TODO
	o (0.00s) skip this test SKIP
	+ (0.00s) test assert not equal

	Passed crash_test.c:6: in 'test_assert_equal' => expected 'NULL', received '((void*)0)'
	AssertionError crash_test.c:10: in 'test_assert_fail' => not expecting 'NULL', received '((void*)0)'
	SegfaultError crash_test.c:13: Segmentation fault in 'segfault_test'
	Passed crash_test.c:28: in 'test_assert_not_equal' => not expecting 'NULL', received '"NotEqual"'

	Ran 6 test(s) in 0.02 Seconds
	Synthesis: FAILURE Tests: 6 | Passing: 2 | Failing: 2 | Skipped: 1 | Todo: 1


JUnitXML
---------

The project can also generate the test report in a valid JunitXML format. The file is considered 
the test suite and each test case the xml test cases. The generated JunitXML is compatible with 
Jenkins and hudson, a sample trend graph and stacktrace generated from jenkins can be seen in 
the `screenshots`_ section. 

The option **--cester-output=junitxml** generates the output as JunitXML. The generated output 
can be validated with the npm package `verify-junit-xml`_. This can be set in the code before 
the test cases start running with CESTER_OUTPUT_JUNITXML();

To generate a JunitXML output for the snippet above 

.. code:: text
	
	./test --cester-verbose --cester-minimal --cester-output=junitxml

	<?xml version="1.0" encoding="UTF-8" ?>
	<testsuite tests="6" failures="2" name="crash_test" errors="0" skipped="2" time="0.02">
		<testcase classname="crash_test" name="test_assert_equal" time="0.00"/>
		<testcase classname="crash_test" name="test_assert_fail" time="0.00">
			<failure message="the test case failed" type="TestFailed">AssertionError crash_test.c:10: in 'test_assert_fail' => not expecting 'NULL', received '((void*)0)'
			</failure>
		</testcase>
		<testcase classname="crash_test" name="segfault_test" time="0.01">
			<failure message="the test case crashed" type="SegmentationFault">SegfaultError crash_test.c:13: Segmentation fault in 'segfault_test'
			</failure>
		</testcase>
		<testcase classname="crash_test" name="test_assert_not_equal" time="0.01"/>
	</testsuite>

TAP
----------------------------

The Test Anything Protocol (TAP) is Perl’s simple text-based interface between testing modules.
Cester support the TAP output format using the commandline option **--cester-output=tap**.
See the specification for TAP at `tap-spec`_.

To generate a TAP output for the snippet above. This can be set in the code before the test cases 
start running with CESTER_OUTPUT_TAP();

.. code:: text
	
	./test --cester-verbose --cester-minimal --cester-output=tap

	1..6
	ok 1 - test assert equal, Passed
	# Passed crash_test.c:6: in 'test_assert_equal' => expected 'NULL', received '((void*)0)'
	not ok 2 - test assert fail, Failed
	# AssertionError crash_test.c:10: in 'test_assert_fail' => not expecting 'NULL', received '((void*)0)'
	not ok 3 - segfault test, Failed: Segmentation fault
	ok 4 - # TODO to do later,
	ok 5 - # SKIP skip this test,
	ok 6 - test assert not equal, Passed
	# Passed crash_test.c:28: in 'test_assert_not_equal' => not expecting 'NULL', received '"NotEqual"'
	# Failed 2 of 6 tests
	# Time 0.02 Seconds

TAP Version 13
----------------------------------------

The Test Anything Protocol (TAP) Version 13 is an extended version of the Test Anything Protocol 
it allow detail information to be attached to the output in the form of YAML block. The option 
**--cester-output=tapV13** prints the test result in TAP Version 13 format. 
See the specification for TAP at `tap-13-spec`_.

To generate a TAP Version 13 output for the snippet above. This can be set in the code before the test cases 
start running with CESTER_OUTPUT_TAPV13();

.. code:: text
	
	./test --cester-verbose --cester-minimal --cester-output=tapV13

	TAP version 13
	1..6
	ok 1 - test assert equal
	not ok 2 - test assert fail
	---
	at:
		file: crash_test.c
		test_case: test_assert_fail
		line: 9
		column: 1
	outputs:
		- AssertionError crash_test.c:10: in 'test_assert_fail' => not expecting 'NULL', received '((void*)0)'
	message: test assert fail failed
	time: 0.00
	...
	not ok 3 - segfault test
	---
	at:
		file: crash_test.c
		test_case: segfault_test
		line: 13
		column: 1
	outputs:
	message: segfault test failed: Segmentation fault
	time: 0.00
	...
	ok 4 - # TODO to do later
	ok 5 - # SKIP skip this test
	ok 6 - test assert not equal
	# Failed 2 of 6 tests
	# Time 0.02 Seconds	

.. _screenshots: ../screenshots.html
.. _verify-junit-xml: https://www.npmjs.com/package/verify-junit-xml
.. _tap-spec: https://testanything.org/tap-specification.html
.. _tap-13-spec: https://testanything.org/tap-version-13-specification.html
