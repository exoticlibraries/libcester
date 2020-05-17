
.. index::
	single: macros

.. |br| raw:: html

	<br />

Helper Macros
==============

All macros in the library starts with `CESTER_`.

CESTER_TEST
------------

The macro for creating a test case. The macro takes care of initialization and declaration 
of the function and also takes care of the test case registration. The first parameter is the 
name of the test case, the second parameter is the TestInstance object to share data and 
command line arguments and the third is the test case body.

During the compile time code generation process the first time the macro is expanded it 
declare the test case function, in the second expansion it registered the test case function 
in the static array and in the final expansion the test case function is initialized. 

For the test case below:

.. code:: text

    CESTER_TEST(test_case_name, test_instance, 
        cester_assert_nothing();
    )

First Expansion 

.. code:: text

    static void cester_test_test_case_name(TestInstance* test_instance);

Second Expansion 

.. code:: text

    static TestCase cester_test_cases[] = {
        { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", 
        (char*) "test_case_name", (cester_test_test_case_name), NULL, NULL, CESTER_NORMAL_TEST }
    }

Final Expansion 

.. code:: text

    static void cester_test_test_case_name(TestInstance* test_instance) {
        cester_assert_nothing();
    }


Therefore after the final expansion the source code will have transformed to this

.. code:: text

    static void cester_test_test_case_name(TestInstance* test_instance);

    static TestCase cester_test_cases[] = {
        { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", 
        (char*) #x, (cester_test_test_case_name), NULL, NULL, CESTER_NORMAL_TEST }
    }

    static void cester_test_test_case_name(TestInstance* test_instance) {
        cester_assert_nothing();
    }


CESTER_TODO_TEST
-----------------

Work the same as the CESTER_TEST macro but the test type is CESTER_NORMAL_TODO_TEST. 
Test case declared with this macro is not executed but it reported as todo test.

.. code:: text

    CESTER_TODO_TEST(a_test_to_implement, test_instance,

    )

This macro is most useful for Test Driven Development (TDD). It create test cases for 
ops that has not been implemented yet.


CESTER_SKIP_TEST
-----------------

Work the same as the CESTER_TEST macro but the test type is CESTER_NORMAL_SKIP_TEST. 
Test case declared with this macro is not executed but it reported as skipped test.

.. code:: text

    CESTER_SKIP_TEST(a_test_to_implement, test_instance,
        
    )

There are various reason to creat a test with this macro, an example is running the test 
file in an environment where the resources needed by the test case is not available.

CESTER_BEFORE_ALL
-------------------

The function to setup the test resources before running the test case. It accepts the 
TestInstance object as the first parameter. The TestInstance parameter can be used to share
data and object between the test cases.

.. code:: text

    CESTER_BEFORE_ALL(test_instance,
        test_instance->arg = "beforeall";
    )

    CESTER_TEST(test_case, test_instance,
        cester_assert_str_equal((char*)(test_instance->arg), "beforeall");
    )

.. note:: 

    If you have any of CESTER_BEFORE_ALL, CESTER_BEFORE_EACH, CESTER_AFTER_ALL and 
    CESTER_AFTER_EACH. Your test cases will be executed on a single process to allow 
    shared objects. 

CESTER_BEFORE_EACH
-------------------

Use the macro to create a function that is invoked before each test case is executed. 
It accepts the TestInstance object as the first parameter, the current test name as the 
second parameter, the test case index as the third parameter.

.. code:: text

    CESTER_BEFORE_EACH(test_instance, test_name, index,
        if (test_name == "test_xml") {
            test_instance->arg = (void*) fopen("./result.xml", "r");

        } else if (test_name == "test_json") {
            test_instance->arg = (void*) fopen("./result.json", "r");
        }
    )

This macro can be used to setup resources according to the test case.

.. note:: 

    If you have any of CESTER_BEFORE_ALL, CESTER_BEFORE_EACH, CESTER_AFTER_ALL and 
    CESTER_AFTER_EACH. Your test cases will be executed on a single process to allow 
    shared objects. 

CESTER_AFTER_EACH
-------------------

Use the macro to create a function that is invoked after each test case is executed. 
It accepts the TestInstance object as the first parameter, the current test name as the 
second parameter, the test case index as the third parameter.

.. code:: text

    CESTER_AFTER_EACH(test_instance, test_name, index,
        if (test_name == "test_xml" || test_name == "test_json") {
            fclose((FILE*)(test_instance->arg));
        }
    )

This macro can be used to tear down resources according to the test case.

.. note:: 

    If you have any of CESTER_BEFORE_ALL, CESTER_BEFORE_EACH, CESTER_AFTER_ALL and 
    CESTER_AFTER_EACH. Your test cases will be executed on a single process to allow 
    shared objects. 

CESTER_AFTER_ALL
-------------------

The function to tear down the test resources after running the test case. It accepts the 
TestInstance object as the first parameter. This macro should be used to clean up shared 
object and close opened resources.

.. code:: text

    CESTER_AFTER_ALL(test_instance,
        free(test_instance->arg);
    )

.. note:: 

    If you have any of CESTER_BEFORE_ALL, CESTER_BEFORE_EACH, CESTER_AFTER_ALL and 
    CESTER_AFTER_EACH. Your test cases will be executed on a single process to allow 
    shared objects. 


CESTER_OPTIONS
---------------

This macro should be used to set the options accepted by cester. The function is executed 
before any of the setup functions and the test case. 

.. code:: text

    CESTER_OPTIONS(
        CESTER_NOCOLOR();
        CESTER_NO_ISOLATION();
        CESTER_OUTPUT_JUNITXML();
    )


CESTER_REGISTER_TEST
----------------------

Manually register a test case. For a compiler that does not have the __BASE_FILE__ macro 
defined the test case won't be registered at compile time, the test cases can be registered 
at runtime using this macro. 

.. code:: text

    CESTER_TEST(test_case_name, test_instance, 
        cester_assert_nothing();
    )

    CESTER_BODY(
    int main(int argc, char** argv) {
        CESTER_REGISTER_TEST(test_case_name);
        return CESTER_RUN_ALL_TESTS(argc, argv);
    }
    )


CESTER_REGISTER_SKIP_TEST
--------------------------

Manually register a test case as a skip test which cases the test case not to run but it 
will be reported in result and logged under skipped tests.

.. code:: text

    CESTER_SKIP_TEST(test_case_name, test_instance, 
        cester_assert_nothing();
    )

    CESTER_BODY(
    int main(int argc, char** argv) {
        CESTER_REGISTER_SKIP_TEST(test_case_name);
        return CESTER_RUN_ALL_TESTS(argc, argv);
    }
    )


CESTER_REGISTER_TODO_TEST
--------------------------

Manually register a test case that is yet to be implemented so it will be skipped but it 
will be reported in result and logged under todo tests.

.. code:: text

    CESTER_TODO_TEST(test_case_name, test_instance, 
        cester_assert_nothing();
    )

    CESTER_BODY(
    int main(int argc, char** argv) {
        CESTER_REGISTER_TODO_TEST(test_case_name);
        return CESTER_RUN_ALL_TESTS(argc, argv);
    }
    )


CESTER_REGISTER_BEFORE_ALL
---------------------------

Manually notify cester to execute the CESTER_BEFORE_ALL function before all the test 
case are run. 

.. code:: text

    CESTER_BODY(
    int main(int argc, char** argv) {
        CESTER_REGISTER_BEFORE_ALL();
        return CESTER_RUN_ALL_TESTS(argc, argv);
    }
    )

.. warning::

    The test cases registered at compile time are ignored if at least one test case 
    is registered at run time with this macro. 


CESTER_REGISTER_AFTER_ALL
---------------------------

Manually notify cester to execute the CESTER_AFTER_ALL function after all the test 
case are run. 

.. code:: text

    CESTER_BODY(
    int main(int argc, char** argv) {
        CESTER_REGISTER_AFTER_ALL();
        return CESTER_RUN_ALL_TESTS(argc, argv);
    }
    )

.. warning::

    The test cases registered at compile time are ignored if at least one test case 
    is registered at run time with this macro. 


CESTER_REGISTER_BEFORE_EACH
----------------------------

Manually notify cester to execute the CESTER_BEFORE_EACH function before each of the test 
case are run. 

.. code:: text

    CESTER_BODY(
    int main(int argc, char** argv) {
        CESTER_REGISTER_BEFORE_EACH();
        return CESTER_RUN_ALL_TESTS(argc, argv);
    }
    )

.. warning::

    The test cases registered at compile time are ignored if at least one test case 
    is registered at run time with this macro. 


CESTER_REGISTER_AFTER_EACH
----------------------------

Manually notify cester to execute the CESTER_AFTER_EACH function after each of the test 
case are run. 

.. code:: text

    CESTER_BODY(
    int main(int argc, char** argv) {
        CESTER_REGISTER_AFTER_EACH();
        return CESTER_RUN_ALL_TESTS(argc, argv);
    }
    )

.. warning::

    The test cases registered at compile time are ignored if at least one test case 
    is registered at run time with this macro. 


CESTER_REGISTER_OPTIONS
----------------------------

Manually notify cester to execute the CESTER_OPTIONS function before running any test cases.

.. code:: text

    CESTER_BODY(
    int main(int argc, char** argv) {
        CESTER_REGISTER_OPTIONS();
        return CESTER_RUN_ALL_TESTS(argc, argv);
    }
    )

.. warning::

    The test cases registered at compile time are ignored if at least one test case 
    is registered at run time with this macro. 


CESTER_TEST_SHOULD
-------------------

Set the expected result of a test case.  It accept the test case name as the first paramater, 
it accepts the expected result as the second parameter. The expected result mush be one of the 
enum types 

- CESTER_RESULT_SUCCESS
- CESTER_RESULT_FAILURE
- CESTER_RESULT_TERMINATED
- CESTER_RESULT_SEGFAULT
- CESTER_RESULT_MEMORY_LEAK

.. code:: text 

    CESTER_TEST(test_case_name, test_instance, 
        
    )

    CESTER_OPTIONS(
        CESTER_TEST_SHOULD(test_case_name, CESTER_RESULT_SUCCESS);
    )


CESTER_TEST_SHOULD_SEGFAULT
-----------------------------

Change the expected result of a test case to Segfault. If the test segfault then it passes. 
If it does not segfault it is marked as failed. It accept the test case name as paramater.

.. code:: text 

    CESTER_TEST(test_case_name, test_instance, 
        int *p = NULL;
        *p=0xdead;
    )

    CESTER_OPTIONS(
        CESTER_TEST_SHOULD_SEGFAULT(test_case_name);
    )


CESTER_TEST_SHOULD_FAIL
-------------------------

Change the expected result of a test case to failure. If the test case passed then it marked 
as failure. If it failed then it consider as passed. It accept the test case name as paramater. 

.. code:: text 

    CESTER_TEST(test_case_name, test_instance, 
        cester_assert_not_equal(NULL, ((void*)0));
    )

    CESTER_OPTIONS(
        CESTER_TEST_SHOULD_FAIL(test_case_name);
    )


CESTER_TEST_SHOULD_BE_TERMINATED
---------------------------------

Change the expected test case result. If the test case is terminated by user or another 
program then it passes ortherwise it fails. It accept the test case name as paramater.

.. code:: text 

    CESTER_TEST(test_case_name, test_instance, 
        while (1) {
            
        }
    )

    CESTER_OPTIONS(
        CESTER_TEST_SHOULD_BE_TERMINATED(test_case_name);
    )


CESTER_TEST_SHOULD_LEAK_MEMORY
---------------------------------

Change the expected test case result. If the test case does not leak any memory then the 
test case is marked as failure. It accept the test case name as paramater.

.. code:: text 

    CESTER_TEST(test_case_name, test_instance, 
        char* str = (char*) malloc(sizeof(char) * 12);
    )

    CESTER_OPTIONS(
        CESTER_TEST_SHOULD_LEAK_MEMORY(test_case_name);
    )

.. note:: 
    
    This macro is not available if the macro CESTER_NO_MEM_TEST is defined


#define CESTER_NO_MOCK
-----------------------

Define the macro CESTER_NO_MOCK to prevent mocking functions in the test. Even if mocked 
function are defined. This is not a predefined macro it has to be defined in the test source before including cester.h.

CESTER_MOCK_SIMPLE_FUNCTION
----------------------------

Mock a function that simply return a value. The macro accepts three parameters, the function 
identifier and parameters, the return type and the value to return when the function is 
invoked. For example mocking a function that return an integer:

.. code:: text

    int multiply_by() {
        return 2;
    }


To function above returns 2, the macro CESTER_MOCK_SIMPLE_FUNCTION can mock this function to 
return 5 instead of two:

.. code:: text

    CESTER_MOCK_SIMPLE_FUNCTION(multiply_by(), int, 5)


The macro above expands to the following code 

.. code:: text

    //...
    __attribute__((weak)) int multiply_by(); int __real_multiply_by();
    //...
    int __wrap_multiply_by() { return 5; }


CESTER_MOCK_FUNCTION
--------------------

This macro is similar to the CESTER_MOCK_SIMPLE_FUNCTION macro but instead of return a single 
value it accepts function body as the third argument. It accepts three parameters, the first is 
the function name and parameters, the second is the return type and the thrid is the function 
body. For example the function below does not return the correct power of value of an integer:

.. code:: text

    int power_of(int* num1, int num2) {
        return *num1 * num2;
    }


We then mock the function in the snippet below to properly calculate the power of an integer:

.. code:: text

    CESTER_MOCK_FUNCTION(power_of(int* num1, int num2), int, 
        int return_val = *num1;
        while (num2-->1) {
            return_val *= *num1;
        }
        return return_val;
    )


The macro above expands to the following code 

.. code:: text

    //...
    __attribute__((weak)) int power_of(int* num1, int num2); int __real_power_of(int* num1, int num2);
    //...
    int __wrap_power_of(int* num1, int num2) { 
        int return_val = *num1;
        while (num2-->1) {
            return_val *= *num1;
        }
        return return_val;
    }

#define CESTER_NO_MAIN
-----------------------

Define this macro before including cester.h to use your own custom main function. This still 
requires you to put your main function in the CESTER_BODY macro. To run the tests invoke the 
macro `CESTER_RUN_ALL_TESTS(argc, argv)` with the two main function parameter. 

CESTER_BODY
---------------

This macro wraps codes in test file to prevent generating the codes more than once. 
Any code block not in one of the test macros should be placed in this macro. Putting 
code in the file without wraping it with CESTER_BODY will cause issues during compilation.

The following code will cause compilation issues.

.. code:: text

    #include <exotic/cester.h>
    
    int an_integer = 20;

The solution is to wrap the statement in CESTER_BODY

.. code:: text

    #include <exotic/cester.h>
    
    CESTER_BODY(
    int an_integer = 20;
    )

Another good example is defining the entry point for the test instead of relying on cester 
main function. After defining the `CESTER_NO_MAIN` your main function must be wrapped 
inside *CESTER_BODY* macro to avoid error. 

.. code:: text

    #define CESTER_NO_MAIN
    #include <exotic/cester.h>

    CESTER_BEFORE_ALL(test_instance,
        cester_assert_equal(1, 1);
    )

    CESTER_BODY(
    int main(int argc, char **argv) {
        return CESTER_RUN_ALL_TESTS(argc, argv);
    }
    )

Any code written inside the *CESTER_BODY* macro will be dumb in the file global scope. This macro 
should not contain other `CESTER_` macros.



#define CESTER_NO_MEM_TEST
---------------------------

Define the macro CESTER_NO_MEM_TEST to disable cester memory allocation test at compile time. 
The option `--cester-nomemtest` can be applied to the command line to stop mem test at runtime. 
This is not a predefined macro it has to be defined in the test source before including cester.h.


#define CESTER_NO_SIGNAL
--------------------------

Disable error handling with signal.h


CESTER_CHANGE_STREAM
---------------------

Change the stream where the ouput is written to, the default value is the standard output 
`stdout`, the macro accepts one argument which is the stream to use. The example below shows 
how to write the test result to a file 'result.txt':

.. code:: text

    CESTER_BEFORE_ALL(test_instance,
        FILE* output = fopen("./result.txt", "w+");
        CESTER_CHANGE_STREAM(output);
    )

The result of the test will be written into the file 'result.txt'. The ouput stream changes 
at which point the macro is used, hence output written before changing the stream will 
remain and the new output will be written to the new stream.

CESTER_NOCOLOR
--------------

.. code:: text

    CESTER_NO_COLOR()

Prevent displaying the output with colors. This option can prevent writing extra bytes into 
an output file in place of the color values. The option can also be set from the cli using 
`--cester-nocolor`. 

CESTER_MINIMAL
---------------

.. code:: text

    CESTER_MINIMAL()

Print minimal info into the output stream. With this option set the expression evaluated 
will not be printed in the result output. The option can also be set from the cli using 
`--cester-minimal`.

CESTER_VERBOSE
---------------

.. code:: text

    CESTER_VERBOSE()

Print as much info as possible into the output stream. With this option set both passed 
and failed expression evaluated will be printed in the result. The option can also be set 
from the cli using `--cester-verbose`. 

CESTER_PRINT_VERSION
---------------------

.. code:: text

    CESTER_PRINT_VERSION()

Print cester version before running any test. The option can also be set from the cli 
using `--cester-printversion`.

CESTER_SINGLE_OUPUT_ONLY
-------------------------

.. code:: text

    CESTER_SINGLE_OUPUT_ONLY()

Display test for a single test case only, skip syntesis and summary. This option can also be 
set from the command line with `--cester-singleoutput`

CESTER_NO_ISOLATION
---------------------

.. code:: text

    CESTER_NO_ISOLATION()

Do not isolate the tests, run each of the test cases in a single process. The drawback is 
if a test case causes segfault or crash the entire test crashes and no summary is displayed. 
No isolation causes a crash one crash all scenerio.
    
This option can also be set from the command line with `--cester-noisolation`

CESTER_NO_MEMTEST
---------------------

.. code:: text

    CESTER_NO_MEMTEST()

Disable memory leak detection test. This option can also be set from the command line 
with `--cester-nomemtest`

CESTER_DO_MEMTEST
---------------------

.. code:: text

    CESTER_SINGLE_OUPUT_ONLY()

Enable memory allocation. The combination of CESTER_NO_MEMTEST() and  CESTER_DO_MEMTEST() 
is valid only in non isolated tests. 

This togle combined with `CESTER_NO_MEMTEST()` can be used to selectively test memory 
allocation in a test e.g. Calling CESTER_NO_MEMTEST() before a test case will prevent memory 
test from the beginning of that function and calling CESTER_DO_MEMTEST() at the end of the 
test case will ensure memory allocation will be validated in all the other test case that follows.

CESTER_OUTPUT_TEXT
---------------------

.. code:: text

    CESTER_OUTPUT_TEXT()

Change the output format to text. This option can also be set from the command line 
with `--cester-format=text`


CESTER_OUTPUT_JUNITXML
-----------------------

.. code:: text

    CESTER_OUTPUT_JUNITXML()

Change the output format to junitxml. This option can also be set from the command line 
with `--cester-format=junitxml`


CESTER_OUTPUT_TAP
-----------------------

.. code:: text

    CESTER_OUTPUT_TAP()

Change the output format to TAP (Test Anything Protocol). This option can also be set from 
the command line with `--cester-format=tap`


CESTER_OUTPUT_TAPV13
-----------------------

.. code:: text

    CESTER_OUTPUT_TAPV13()

Change the output format to TAP (Test Anything Protocol) Version 13. This option can also 
be set from the command line with `--cester-format=tapV13`


CESTER_FORMAT_TESTNAME
-----------------------

.. code:: text

    CESTER_FORMAT_TESTNAME()

Format the test case name for output. E.g the test name  `modify_test_instance` becomes 
`modify test instance`. This does not apply to junitxml as the test name remain the way it declared in the test 
source.


CESTER_DONT_FORMAT_TESTNAME
-----------------------------

.. code:: text

    CESTER_DONT_FORMAT_TESTNAME()

Do not format the test case name, it remain the way it declared in the test source. 
This option can also be set from the command line with `--cester-dontformatname`


CESTER_TOTAL_TESTS_COUNT
-------------------------

.. code:: text

    printf("Current Total Test %d", CESTER_TOTAL_TESTS_COUNT);

The total number of test that is registered at the time.


CESTER_TOTAL_FAILED_TESTS_COUNT
---------------------------------

.. code:: text

    printf("Failed Test %d", CESTER_TOTAL_FAILED_TESTS_COUNT);

The total number of test cases that fails from the total number of test cases at the time. 


CESTER_TOTAL_TESTS_SKIPPED
---------------------------

.. code:: text

    printf("Skipped %d tests\n", CESTER_TOTAL_TESTS_SKIPPED);

The number of test cases that was skipped at the time.


CESTER_TOTAL_PASSED_TESTS_COUNT
---------------------------------

.. code:: text

    printf("%d test are passing \n", CESTER_TOTAL_PASSED_TESTS_COUNT);

The total number of test cases that passed from the total number of test cases at the time. 


CESTER_TOTAL_TODO_TESTS
---------------------------------

.. code:: text

    printf("%d todo tests are skipped \n", CESTER_TOTAL_TODO_TESTS);

The total number of todo test case skipped at the time. 


CESTER_VERSION
---------------

.. code:: text

    printf("v%s", CESTER_VERSION);

Current cester version 


CESTER_VERSION_NUM
--------------------

.. code:: text

    printf("v%f", CESTER_VERSION_NUM);

Current cester version in float format


CESTER_LICENSE
---------------

.. code:: text

    printf("%s", CESTER_LICENSE);

cester licence **GNU General Public License v3.0**
