
.. index::
	single: options

Cester Options
===============

cester accepts various options to tune it functionalities. Any command line parameter that 
starts with --cester- is treated as cester option otherwise it is ignored.

.. code:: text

	cester v0.4 by Adewale Azeez and other contributors.
	MIT License
	Usage: ./test_info [--FLAGS] [ARGS...]

	where --FLAGS include:
		--cester-verbose-level=[LEVEL]  change how much information is printed in the terminal
		--cester-minimal                print minimal info into the output stream
		--cester-verbose                print as much info as possible into the output stream
		--cester-nocolor                do not print info with coloring
		--cester-singleoutput           display cester version and exit
		--cester-nomemtest              disable memory leak detection in the tests
		--cester-nostreamcapture        disable stream capture and assertions in the tests
		--cester-noisolation            run all the test on a single process. Prevents recovery from crash.
		--cester-printversion           display cester version before running the tests
		--cester-dontformatname         leave the test case name as declared in the source file in the output
		--cester-test=Test1,...         run only selected tests. Seperate the test cases by comma
		--cester-output=[FORMAT]        change the format in which the test results are printed
		--cester-info=[IOPTIONS],[IOPTIONS...] print out all or specific information about the test executablle
		--cester-version                display cester version and exit
		--cester-help                   display this help info version and exit
	See https://exoticlibraries.github.io/libcester/docs/options.html for more details

	Supported output formats. [FORMAT]:
		text
		junitxml
		tap
		tapV13

	Supported info options. [IOPTIONS]:
		all
		options
		comments
		before_all
		before_each
		before*
		after_all
		after_each
		after*
		test
		test_skip
		test_todo
		test*

	Verbose levels. [LEVEL]:
		0 - No information alias of --cester-minimal
		1,2
		3 - Meaningful information
		4,5,6,7,8,9
		10 - Meaningful informations + garbage alias of --cester-verbose


--cester-nocolor
--------------------------

Disable colorfull output in the terminal. This option is useful when writing the test result to 
a file, it removes the color bytes that enable the color print in the terminal. This can also 
be set in the code within the CESTER_OPTIONS block with the macro CESTER_NOCOLOR().

--cester-singleoutput
--------------------------

Only print the assertion detail to the output. This is used within cester during 
isolation testing to capture the output from a single test case. This can also be set in the 
code within the CESTER_OPTIONS block with the macro CESTER_SINGLE_OUPUT_ONLY().

--cester-nomemtest
--------------------------

Disable memory leak detection and memory test. This option is available if the test source 
does not define the CESTER_NO_MEM_TEST macro.  If the macro CESTER_NO_MEM_TEST is defined in the 
test source memory leak detection is disabled at compile time and this option is not available 
at runtime. This can also be set within the code using the macro CESTER_NO_MEMTEST().

--cester-nostreamcapture
--------------------------

Disable stream capturing and assertions in tests. This option is available if the test source 
does not define the CESTER_NO_STREAM_CAPTURE macro.  If the macro CESTER_NO_STREAM_CAPTURE is defined in the 
test source stream capture features are disabled at compile time and this option is not available 
at runtime. This can also be set within the code using the macro CESTER_NOSTREAMCAPTURE().

--cester-noisolation
--------------------------

Instruct cester to run all the test in one single process. With this option signal will be used 
for crash reporting but if the test is compiled with the macro `CESTER_NO_SIGNAL` defined, 
cester will not be able to recover from critical crash therefore if a test case segfault the 
tests will terminate immediately. 

If the test is compiled for C version less than C99, isolated test is disabled, in such case 
the signal is used to recover from a critical test case crash. This can also be set within 
the code using the macro CESTER_NO_ISOLATION().

--cester-test=
--------------------------

Select which test case you want to run. Each of the selected test case mush be seperated with 
a comma, if any of the selected test case is not found in the test file it is ignored. E.g. for 
the test file below, this option can be used to run only one test case. 

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(test_assert_equal, inst, 
		cester_assert_equal(NULL, ((void*)0));
	)

	CESTER_TEST(test_assert_fail, inst, 
		cester_assert_not_equal(NULL, ((void*)0));
	)

.. code:: text 

	gcc test.c -I. -o test
	./test --cester-test=test_assert_equal
	
	+ (0.00s) test assert equal


	Ran 2 test(s) in 0.00 Seconds
	Synthesis: SUCCESS Tests: 2 | Passing: 1 | Failing: 0


The option is used to select which test to run. Above we selected the test case `test_assert_equal` 
to select the two test cases we can supply this option `--cester-test=test_assert_equal,test_assert_fail`.

--cester-output=?
--------------------------

Change the format in which the outpout is generated. Various format is supported, all the 
supported format can be viewed at `output_formats <./output_formats.html>`_. E.g. to print the 
output in JunitXML format you supply the option `--cester-output=junitxml`. 

--cester-info=?
---------------------

Specify which specific information is to be printed out, the supported information sections can be 
view at `test_information <./test_information.html>`_. With the combination of `--cester-output=?` flag 
The information can be printed out in different formats. E.g. to print out al the test information in 
junitxml format `--cester-info=all --cester-output=junitxml`

--cester-verbose-level=?
--------------------------

Change the verbose level of the output, the higher the velue the more the information 
printed into the terminal. 0 value means no output apart from the testcase's and value 
4 and above prints the full path to the test file. This can also be set within the code 
using the macro CESTER_VERBOSE_LEVEL(?).

The verbose level ranges from 0 to 10, zero being the lowest and 10 the highest. With 
verbose level of zero no information is printed in the terminal, with 10 all possible 
information is printed in the terminal. 3 is the best value to print out meaningful 
details. E.g. `--cester-verbose-level=3`

--cester-minimal
--------------------------

Display minimal information in the output, this option combined with --cester-verbose produces 
a fine output in the terminal. This can also be set within the code using the macro 
CESTER_MINIMAL().

This is equivaluent to setting the verbose level to the lowest value 
`--cester-verbose-level=0`. No information is printed into the terminal.

--cester-verbose
--------------------------

Display as much detail as possible in the output. This include expression and information of 
assertion macro that passed, only failed assertion is displayed if this option is not supplied. 
This can also be set within the code using the macro CESTER_VERBOSE().

This is equivaluent to setting the verbose level to the highest value 
`--cester-verbose-level=10`. All possible information is printed into the terminal with the 
full path of the test file.

--cester-dontformatname
--------------------------

Do not format the test case when displaying the output. E.g. the test case `test_assert_equal` in 
the output will be displayed as `test assert equal` but if this option is supplied it will be 
displayed as it declared in the source. This can also be set within the code using the macro 
CESTER_DONT_FORMAT_TESTNAME().

--cester-printversion
--------------------------

Display cester version and license before running the tests.

--cester-version
--------------------------

Display cester version and license and exit.

--cester-help
--------------------------

Display the help info version and exit.
