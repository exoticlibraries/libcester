
.. index::
	single: how_test_registration_works

How test registration works
=============================

Cester generates some code at compile time by re including the main test file more than once. 
In the second iteration all the cester test cases macro are expanded to a static TestCase
object and added to the static array **cester_test_cases**.

The example below shows the procedure for the compile time test registration. 

.. code:: text 

	CESTER_TEST(do_nothing, inst, 
		cester_assert_nothing();
	)

At the second iteration the macro above expands to 

.. code:: text 

	{ CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", 
	  (char*) "do_nothing", (cester_test_do_nothing), NULL, NULL, CESTER_NORMAL_TEST },

In the source of cester.h the second include takes place inside the static array hence the 
macro above will be expanded into the array 

.. code:: text

	// in cester.h
	static TestCase cester_test_cases[] = {
	#ifdef __BASE_FILE__
		#include __BASE_FILE__
	#endif
	{ CESTER_RESULT_UNKNOWN, 0, CESTER_RESULT_SUCCESS, 0.000, 0.000, NULL, NULL, NULL, NULL, NULL, CESTER_TESTS_TERMINATOR }
	};

Expands to 

.. code:: text

	static TestCase cester_test_cases[] = {
	{ CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", 
	   (char*) "do_nothing", (cester_test_do_nothing), NULL, NULL, CESTER_NORMAL_TEST },
	{ CESTER_RESULT_UNKNOWN, 0, CESTER_RESULT_SUCCESS, 0.000, 0.000, NULL, NULL, NULL, NULL, NULL, CESTER_TESTS_TERMINATOR }
	};

At runtime the array **cester_test_cases** is then iterated to get and run the test cases.