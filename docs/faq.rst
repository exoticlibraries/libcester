
.. index::
	single: faq

FAQ
=========

Q: No test detected why?
--------------------------

If no test was ran or your test cases were not detected, in most cases it because your compiler 
did not define the __BASE_FILE__ macro. If you are using the Visual studio IDE you should define 
the macro in `Properties -> C/C++ -> Preprocessor -> Preprocessor Definition` 
as `__BASE_FILE__="%(Filename)%(Extension)"`. 

Or you can define the macro at compile time as argument to your compiler using the macro option. 
e.g. in gcc 

.. code:: bash
	
	gcc -D__BASE_FILE__=\"/the/path/to/yout/testfile.c\" testfile.c -I.

You can also define the __BASE_FILE__ at the beginning of your test file with the absolute 
path to the test file. E.g for the test file test.c:

.. code:: c
	
	#define __BASE_FILE__ "/path/to/test.c"
	#include <exotic/cester.h>

	CESTER_TEST(test1, test_instance,
		cester_assert_equal(NULL, NULL);
	)

Alternatively the test cases should be manually registered in the main method, you will have to disable cester main function by defining the macro CESTER_NO_MAIN. 

.. code:: c

	#include <exotic/cester.h>

	#define CESTER_NO_MAIN

	CESTER_TEST(test1, test_instance,
		cester_assert_equal(NULL, NULL);
	)

	CESTER_BODY(
	int main(int argc, char** argv) {
		CESTER_REGISTER_TEST(test1);
		return CESTER_RUN_ALL_TESTS(argc, argv);
	}
	)

Visit this link `Manual test registration`_ for more detail on manual test registration.

Q: What is the best practice for test detection
------------------------------------------------

Include the guide for __BASE_FILE__ 

.. code:: c

	#ifndef __BASE_FILE__
	#define CESTER_NO_MAIN
	#endif
	#include <exotic/cester.h>

	//your test cases here

	#ifndef __BASE_FILE__
	CESTER_BODY(
	int main(int argc, char** argv) {
		// register your test cases here 
		return CESTER_RUN_ALL_TESTS(argc, argv);
	}
	)
	#endif

This ensure that if the directive __BASE_FILE__ is not defined by the compiler the test case will be registered 
manually.

Q: Why is test_instance->arg value not changing
------------------------------------------------

In isolated tests the test_instance object is not preserved between the test cases, each test case 
has a new copy of the test_instance object the same applied to CESTER_BEFORE_EACH and CESTER_AFTER_EACH. 
changes made in each test cases, the CESTER_BEFORE_EACH and CESTER_AFTER_EACH does not reflect 
in each test case as each test case is ran on a new process, the solution is to declare shared datas 
in CESTER_BEFORE_ALL and CESTER_AFTER_ALL functions. Or add the `--cester-noisolation` to run the 
tests on a single process this way all data are shared. *argv* and *argc* values of the 
test_instance is shared between each test process in isolated test only *arg* data is not shared.


.. note::

	Using the `--cester-noisolation` cester will rely on signal to recover from critical 
	crash.

The example below recreates the problem and provides a solution.

.. code:: c

	#include <exotic/cester.h>

	CESTER_BEFORE_EACH(test_instance, test_name, index,
		if (test_name == "test_one") {
			test_instance->arg = "Hello World";
		}
	)

	CESTER_TEST(test_one, test_instance,
		cester_assert_equal(test_instance->arg, "Hello World");
	)

	CESTER_TEST(test_two, test_instance,
		cester_assert_equal(test_instance->arg, "Yahoo");
	)

	CESTER_AFTER_EACH(test_instance, test_name, index,
		test_instance->arg = "Yahoo";
	)

Compiling and running test on seperate process.

.. code:: bash 

	gcc ./crash_test.c -I. -o out
	./out 

	+ (0.01) test_one
	- (0.00) test_two

	AssertionError crash_test.c:14: in test case 'test_two' => expected "Yahoo", found test_instance->arg

	Ran 2 test(s) in 0.01 Seconds
	Synthesis: FAILURE Tested: 2 | Passing: 1 | Failing: 1 | Skipped: 0

The test above wil fail because for test case **test_two** because the test_instance->arg value 
will still be `"Hello World"` as the CESTER_AFTER_EACH executed for **test_one** will be exclusive 
to test_one process only. The solution is to applly the option `--cester-noisolation` to the test 
to use a single process for all the tests.

.. code:: bash 

	gcc ./crash_test.c -I. -o out
	./out --cester-noisolation
	
	+ (0.00) test_one
	+ (0.00) test_two


	Ran 2 test(s) in 0.00 Seconds
	Synthesis: SUCCESS Tested: 2 | Passing: 2 | Failing: 0 | Skipped: 0



.. _Manual test registration: ./docs/manual_test_registration.html