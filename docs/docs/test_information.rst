
.. index::
	single: test_information

Test Information
=================

The test information can be printed out in various output format. This feature is most 
useful for test managers and for test debugging. By passing the flag `--cester-info=` 
along with it value, the specified information section will be printed. 

The supported sections are

- all
- options
- comments
- before_all
- before_each
- before*
- after_all
- after_each
- after*
- test
- test_skip
- test_todo
- test*

.. warning::

	If the test is compiled with the macro CESTER_NO_PRINT_INFO defined before including 
	libcester, the information printing feature will be disabled

Various Section data can be generated for the snippet below.

.. code:: text

	//test_info.c
	CESTER_MOCK_SIMPLE_FUNCTION(multiply_by(), int, 5)

	CESTER_MOCK_FUNCTION(power_of(int* num1, int num2), int, 
		int return_val = *num1;
		while (num2-->1) {
			return_val *= *num1;
		}
		return return_val;
	)

	CESTER_BODY(
		static int index__ = 500;
	)

	CESTER_COMMENT(
		This is a multiline comment in \n
		the source code this text is printed out \n
		before any test cases is executed.
	)

	CESTER_BEFORE_ALL(test_instance, 
		test_instance->arg = (void*) "exoticlibs";
	)

	CESTER_BEFORE_EACH(test_instance, test_name, index,
		printf("Before Each test, Test %s, index %d\n", test_name, index);
	)

	CESTER_TEST(test_string, test_instance, 
		cester_assert_str_equal((char*)test_instance->arg, "exoticlibs");
		cester_assert_str_not_equal((char*)test_instance->arg, CESTER_NULL);
	)

	CESTER_TEST(test_string_alias, test_instance, 
		cester_assert_str_eq((char*)test_instance->arg, "exoticlibs");
		cester_assert_str_ne((char*)test_instance->arg, CESTER_NULL);
	)

	CESTER_TODO_TEST(write_test_after_implementation, test_instance,
		void *p = CESTER_NULL;
	)

	CESTER_SKIP_TEST(this_test_will_fail, test_instance,
		void *p = CESTER_NULL;
	)

	CESTER_SKIP_TEST(works_only_on_linux, test_instance,
		void *p = CESTER_NULL;
	)

	CESTER_AFTER_EACH(test_instance, test_name, index,
		printf("After Each test, Test %s, index %d\n", test_name, index);
		printf("==============================================================\n");
	)

	CESTER_AFTER_ALL(test_instance, 
		test_instance->arg = CESTER_NULL;
	)

	CESTER_OPTIONS(
		CESTER_NO_ISOLATION();
	)

	CESTER_BODY(
	int main(int argc, char** argv) {
		CESTER_REGISTER_OPTIONS();
		CESTER_REGISTER_BEFORE_ALL();
		CESTER_REGISTER_BEFORE_EACH();
		CESTER_REGISTER_TEST(test_string);
		CESTER_REGISTER_TEST(test_string_alias);
		CESTER_REGISTER_SKIP_TEST(this_test_will_fail);
		CESTER_REGISTER_SKIP_TEST(works_only_on_linux);
		CESTER_REGISTER_TODO_TEST(write_test_after_implementation);
		CESTER_REGISTER_AFTER_ALL();
		CESTER_REGISTER_AFTER_EACH();
		return CESTER_RUN_ALL_TESTS(argc, argv);
	}
	)


Compile the test with the command below:

.. code:: bash

	gcc test_info.c -I. -o test


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

To print all the sections, add the flag `--cester-info=all`

.. code:: text
	
	./test --cester-info=all

	Options and Comments
	- cester_test_file_comment_function
	- cester_options_before_main
	Fixture - Before
	- cester_before_all_test
	- cester_before_each_test

	Fixture - After
	- cester_after_each_test
	- cester_after_all_test

	Tests
	- test_string
	- test_string_alias

	Skip Tests
	- this_test_will_fail
	- works_only_on_linux

	Todo Tests
	- write_test_after_implementation

To print only the tests section, add the flag `--cester-info=test`

.. code:: text
	
	./test --cester-info=test

	test_string
	test_string_alias

Combining the --cester-info flag with --cester-output flag will print out the information in the 
selected output format. If an output format has not been implemented it defaults to the text output 
fornat, to see the currently implemented formats see `issue 58 <https://github.com/exoticlibraries/libcester/issues/58>`_

To print all the sections with junitxml format, add the flags `--cester-info=all --cester-output=junitxml`

.. code:: xml
	
	./test --cester-info=all --cester-output=junitxml

	<?xml version="1.0" encoding="UTF-8" ?>
	<testinfo file_name="test_info" file_path="test_info.c">
		<options_and_comments>
			<function name="cester_test_file_comment_function" line_number="22" type="CESTER_TEST_FILE_COMMENT"/>
			<function name="cester_options_before_main" line_number="67" type="CESTER_OPTIONS_FUNCTION"/>
		</options_and_comments>
		<fixture_before>
			<function name="cester_before_all_test" line_number="28" type="CESTER_BEFORE_ALL_TEST"/>
			<function name="cester_before_each_test" line_number="32" type="CESTER_BEFORE_EACH_TEST"/>
		</fixture_before>
		<fixture_after>
			<function name="cester_after_each_test" line_number="58" type="CESTER_AFTER_EACH_TEST"/>
			<function name="cester_after_all_test" line_number="63" type="CESTER_AFTER_ALL_TEST"/>
		</fixture_after>
		<tests>
			<function name="test_string" line_number="36" type="CESTER_NORMAL_TEST"/>
			<function name="test_string_alias" line_number="41" type="CESTER_NORMAL_TEST"/>
		</tests>
		<skip_tests>
			<function name="this_test_will_fail" line_number="50" type="CESTER_NORMAL_SKIP_TEST"/>
			<function name="works_only_on_linux" line_number="54" type="CESTER_NORMAL_SKIP_TEST"/>
		</skip_tests>
		<todo_tests>
			<function name="write_test_after_implementation" line_number="46" type="CESTER_NORMAL_TODO_TEST"/>
		</todo_tests>
	</testinfo>

To print only the tests, todo_test, skip_test section with junitxml format, add the flags `--cester-info=test --cester-output=junitxml`

.. code:: xml
	
	./test --cester-info=test --cester-output=junitxml

	<?xml version="1.0" encoding="UTF-8" ?>
	<testinfo file_name="test_info" file_path="test_info.c">
		<function name="test_string" line_number="36" type="CESTER_NORMAL_TEST"/>
		<function name="test_string_alias" line_number="41" type="CESTER_NORMAL_TEST"/>
		<function name="write_test_after_implementation" line_number="46" type="CESTER_NORMAL_TODO_TEST"/>
		<function name="this_test_will_fail" line_number="50" type="CESTER_NORMAL_SKIP_TEST"/>
		<function name="works_only_on_linux" line_number="54" type="CESTER_NORMAL_SKIP_TEST"/>
	</testinfo>

