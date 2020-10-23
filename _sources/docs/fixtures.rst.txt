
.. index::
	single: fixtures

Test Fixtures
==============

In writing code for tests it time consuming setting up the test fixtures before running the 
test cases and dissposing the fixtures after the test completes.

cester supports sharing the fixture mangement code between test cases. The following macros 
can be used in seting up and destroying objects used for test.

- `CESTER_BEFORE_ALL <./macros.html#cester-before-all>`_
- `CESTER_BEFORE_EACH <./macros.html#cester-before-each>`_
- `CESTER_AFTER_EACH <./macros.html#cester-after-each>`_
- `CESTER_AFTER_ALL <./macros.html#cester-after-all>`_


Test Instance Object
----------------------

Each test case accept a second parameter after the name, the second parameter is the 
test_instance object that can be used to share datas and objects between test cases without 
the need of using global variable. The structure of the test case is shown below.

.. code:: c

	typedef struct test_instance {
		unsigned argc;
		char **argv;
		void *arg;
	} TestInstance;

The `argc` value is the length of the command line arguments, `argv` is the array of command 
line arguments. `arg` is a pointer that can hold any extra data which all the test cases can 
have access to.

The following example shows how a string is shared between the test cases using the 
test_instance object instead of a global variable.

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(assign_arg, test_instance, 
		cester_assert_not_equal(test_instance->arg, "beforeall");
		test_instance->arg = "beforeall";
	)

	CESTER_TEST(check_arg, test_instance, 
		cester_assert_str_equal(test_instance->arg, "beforeall");
	)


Output

.. code:: text
	
	+ (0.00s) assign arg
	+ (0.00s) check arg

	Passed crash_test.c:6: in 'assign_arg' => not expecting 'test_instance->arg', received '"beforeall"'
	Passed crash_test.c:11: in 'check_arg' => expected 'beforeall', received 'beforeall'

	Ran 2 test(s) in 0.00 Seconds
	Synthesis: SUCCESS Tests: 2 | Passing: 2 | Failing: 0


CESTER_BEFORE_ALL and CESTER_AFTER_ALL
----------------------------------------

Before any test case is run the codes in the macro `CESTER_BEFORE_ALL` is executed. 
CESTER_BEFORE_ALL is where the objects to be used in the test is created. Once all the test 
cases has finished running, whether the test passed or failed, the codes in the macro 
`CESTER_AFTER_ALL` is executed. CESTER_AFTER_ALL is where the objects used in the test is 
destroyed.

The example below uses the `CESTER_BEFORE_ALL` and `CESTER_AFTER_ALL` to manage objects 
used in a test.

.. code:: c

	#include <exotic/cester.h>
	#include <exotic/array.h>

	CESTER_BEFORE_ALL(test_instance,
		Array* array;
		enum x_stat status;
		status = array_new(&array);
		array_add(array, "Hello");
		array_add(array, "World");
		
		test_instance->arg = array;
	)

	CESTER_TEST(check_initial_value_at_1, test_instance,
		Array* array = (Array *) test_instance->arg;
		void *out;
		
		array_get_at(array, 1, &out);
		cester_assert_str_not_equal("Hello", (char*)out);
		cester_assert_str_equal("World", (char*)out);
		array_add_at(array, "Hello World", 1);
	)

	CESTER_TEST(check_modified_value_at_1, test_instance,
		Array* array = (Array *) test_instance->arg;
		void *out;
		
		array_get_at(array, 1, &out);
		cester_assert_str_not_equal("World", (char*)out);
		cester_assert_str_equal("Hello World", (char*)out);
	)

	CESTER_AFTER_ALL(test_instance,
		Array* array = (Array *) test_instance->arg;
		array_destroy(array);
	)


Output

.. code:: text

	+ (0.00s) check initial value at 1
	+ (0.00s) check modified value at 1

	Passed test_array.c:21: in 'check_initial_value_at_1' => not expecting 'Hello', received 'World'
	Passed test_array.c:22: in 'check_initial_value_at_1' => expected 'World', received 'World'
	Passed test_array.c:31: in 'check_modified_value_at_1' => not expecting 'World', received 'Hello World'
	Passed test_array.c:32: in 'check_modified_value_at_1' => expected 'Hello World', received 'Hello World'

	Ran 2 test(s) in 0.00 Seconds
	Synthesis: SUCCESS Tests: 2 | Passing: 2 | Failing: 0


In the test above an array object is created in the CESTER_BEFORE_ALL macro and destroyed in 
the CESTER_AFTER_ALL macro. The two test cases are able to share the same array object created.

It not a must to use the macros CESTER_AFTER_ALL and CESTER_BEFORE_ALL in one test code, 
the objects that needs cleanup like a database object opened in CESTER_BEFORE_ALL can then be 
closed in CESTER_AFTER_ALL. Only one of the two macro or a mix of both can be in a test.

CESTER_BEFORE_EACH and CESTER_AFTER_EACH 
-----------------------------------------

In a scenerio whereby an object needs to be changed according to the active test case the macro 
CESTER_BEFORE_EACH and CESTER_AFTER_EACH come into the picture. Both macro accepts three 
parameters the first is the Test instead object, the second is the current test case name that 
is been executed and the last argument is the index of the active test case.

The example below set the shared argument to the name of the active text case:

.. code:: c

	#include <exotic/cester.h>

	CESTER_BEFORE_EACH(test_instance, name, index,
		printf("Before TestCase '%s', at index '%d'\n", name, index);
		test_instance->arg = name;
	)

	CESTER_TEST(first_test_case, test_instance, 
		cester_assert_str_equal((char *)test_instance->arg, "first_test_case");
	)

	CESTER_TEST(second_test_case, test_instance, 
		cester_assert_str_equal((char *)test_instance->arg, "second_test_case");
	)

	CESTER_AFTER_EACH(test_instance, name, index,
		printf("After TestCase '%s', at index '%d'\n", name, index);
	)

Output

.. code:: text

	Before TestCase 'first_test_case', at index '1'
	After TestCase 'first_test_case', at index '1'
	Before TestCase 'second_test_case', at index '2'
	After TestCase 'second_test_case', at index '2'

	+ (0.00s) first test case
	+ (0.01s) second test case

	Passed crash_test.c:11: in 'first_test_case' => expected 'first_test_case', received 'first_test_case'
	Passed crash_test.c:15: in 'second_test_case' => expected 'second_test_case', received 'second_test_case'

	Ran 2 test(s) in 0.01 Seconds
	Synthesis: SUCCESS Tests: 2 | Passing: 2 | Failing: 0

It not a must to use the macros CESTER_AFTER_EACH and CESTER_BEFORE_EACH in one test code. 
Only one of the two macro or a mix of both can be in a test.

.. note::

	using any of the macro CESTER_BEFORE_ALL, CESTER_AFTER_EACH, CESTER_AFTER_EACH, 
	CESTER_BEFORE_ALL will disable running each of the test cases on different process, 
	so that the shared data is preserved between the test cases. signal.h will be used to 
	catch and recover from crashes test cases.