
.. index::
	single: manual_test_registration

Manual Tests Registration
==========================

Test cases can be manually registered, if any test is manually registered the automatically  
detected test cases will be ignored. The macro CESTER_REGISTER_TEST and it variant is used for 
test registration. The following macros are used for test registration:

- `CESTER_REGISTER_TEST <./macros.html#cester-register-test>`_
- `CESTER_REGISTER_SKIP_TEST <./macros.html#cester-register-skip-test>`_
- `CESTER_REGISTER_TODO_TEST <./macros.html#cester-register-todo-test>`_
- `CESTER_REGISTER_BEFORE_ALL <./macros.html#cester-register-before-all>`_
- `CESTER_REGISTER_BEFORE_EACH <./macros.html#cester-register-before-each>`_
- `CESTER_REGISTER_AFTER_ALL <./macros.html#cester-register-after-all>`_
- `CESTER_REGISTER_AFTER_EACH <./macros.html#cester-register-after-each>`_
- `CESTER_REGISTER_OPTIONS <./macros.html#cester-register-options>`_

The main use of manual test registration is for compiler or platform that does not have the 
__BASE_FILE__ macro defined. The test cases had to be registered in the main method before the 
call to start running the test cases. 

Any code outside the test cases should be put in a CESTER_BODY to prevent double dump.

Example 1
'''''''''''

The following test manually register the test cases incase the compiler does not have the 
__BASE_FILE__ defined. 

.. code:: c

	// test.c
	#define CESTER_NO_MAIN
	#include <exotic/cester.h>

	CESTER_TEST(test1, test_instance,
		cester_assert_equal(NULL, NULL);
	)

	CESTER_BODY(
	int main(int argc, char** argv) {
		CESTER_REGISTER_TEST(test1);
		return CESTER_RUN_ALL_TESTS(argc, argv);
	}
	)

.. code:: text 

	gcc test.c -I. -o test
	./test --cester-minimal
		
	+ (0.01s) test1


	Ran 1 test(s) in 0.01 Seconds
	Synthesis: SUCCESS Tests: 1 | Passing: 1 | Failing: 0


Example 2
'''''''''''

The setup and teardown macros also have to be manually registered also. The test below manually 
register the CESTER_BEFORE and CESTER_AFTER macros

.. code:: c

	// test.c
	#define CESTER_NO_MAIN
	#include <exotic/cester.h>


	CESTER_BEFORE_ALL(test_instance,
		printf("Before All\n");
	)

	CESTER_BEFORE_EACH(test_instance, test_name, index,
		printf("Before Each %s\n", test_name);
	)

	CESTER_TEST(test1, test_instance,
		cester_assert_equal(NULL, NULL);
	)

	CESTER_TEST(test2, test_instance,
		cester_assert_not_equal(NULL, NULL);
	)

	CESTER_AFTER_EACH(test_instance, test_name, index,
		printf("After Each %s\n", test_name);
	)

	CESTER_AFTER_ALL(test_instance,
		printf("After All\n");
	)

	CESTER_OPTIONS(
		CESTER_NOCOLOR();
	)

	CESTER_BODY(
	int main(int argc, char** argv) {
		CESTER_REGISTER_BEFORE_ALL();
		CESTER_REGISTER_OPTIONS();
		CESTER_REGISTER_BEFORE_EACH();
		CESTER_REGISTER_TEST(test1);
		CESTER_REGISTER_TEST(test2);
		CESTER_REGISTER_AFTER_ALL();
		CESTER_REGISTER_AFTER_EACH();
		CESTER_TEST_SHOULD_FAIL(test2);
		return CESTER_RUN_ALL_TESTS(argc, argv);
	}
	)

.. code:: text

	gcc test.c -I. -o test
	./test --cester-minimal

	Before All
	After All

	+ (0.01s) test1
	+ (0.00s) test2

	Before Each test1
	After Each test1
	Before Each test2
	After Each test2
	AssertionError test.c:20: in 'test2' => not expecting 'NULL', received 'NULL'

	Ran 2 test(s) in 0.01 Seconds
	Synthesis: SUCCESS Tests: 2 | Passing: 2 | Failing: 0