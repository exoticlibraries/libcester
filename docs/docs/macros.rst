
.. index::
	single: macros


Helper Macros
==============

All macros in the library starts with `CESTER_`.

#define CESTER_NO_MOCK
-----------------------

Define the macro CESTER_NO_MOCK to prevent mocking functions in the test. Even if mocked 
function are defined. This is not a predefined macro it has to be defined in the test source before including cester.h.

CESTER_MOCK_SIMPLE_FUNCTION
----------------------------

Mock a function that simply return a value. The macro accepts three parameters, the function 
identifier and parameters, the return type and the value to return when the function is 
invoked. For example mocking a function that return an integer:

.. code:: c

    int multiply_by() {
        return 2;
    }


To function above returns 2, the macro CESTER_MOCK_SIMPLE_FUNCTION can mock this function to 
return 5 instead of two:

.. code:: c

    CESTER_MOCK_SIMPLE_FUNCTION(multiply_by(), int, 5)


The macro above expands to the following code 

.. code:: c

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

.. code:: c

    int power_of(int* num1, int num2) {
        return *num1 * num2;
    }


We then mock the function in the snippet below to properly calculate the power of an integer:

.. code:: c

    CESTER_MOCK_FUNCTION(power_of(int* num1, int num2), int, 
        int return_val = *num1;
        while (num2-->1) {
            return_val *= *num1;
        }
        return return_val;
    )


The macro above expands to the following code 

.. code:: c

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

Always define before including cester.h

CESTER_BODY
---------------

This macro wraps codes in test file to prevent generating the codes more than once. 
Any code block not in one of the test macros should be placed in this macro. Putting 
code in the file without wraping it with CESTER_BODY will cause issues during compilation.

The following code will cause compilation issues.

.. code:: c

    #include <exotic/cester.h>
    
    int an_integer = 20;

The solution is to wrap the statement in CESTER_BODY

.. code:: c

    #include <exotic/cester.h>
    
    CESTER_BODY(
    int an_integer = 20;
    )

Another good example is defining the entry point for the test instead of relying on cester 
main function. After defining the `CESTER_NO_MAIN` your main function must be wrapped 
inside *CESTER_BODY* macro to avoid error. 

.. code:: c

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

.. code:: 

    CESTER_BEFORE_ALL(test_instance,
        FILE* output = fopen("./result.txt", "w+");
        CESTER_CHANGE_STREAM(output);
    )

The result of the test will be written into the file 'result.txt'. The ouput stream changes 
at which point the macro is used, hence output written before changing the stream will 
remain and the new output will be written to the new stream.

CESTER_NOCOLOR
--------------

.. code:: c

    CESTER_NO_COLOR()

Prevent displaying the output with colors. This option can prevent writing extra bytes into 
an output file in place of the color values. The option can also be set from the cli using 
`--cester-nocolor`. 

CESTER_MINIMAL
---------------

.. code:: c

    CESTER_MINIMAL()

Print minimal info into the output stream. With this option set the expression evaluated 
will not be printed in the result output. The option can also be set from the cli using 
`--cester-minimal`.

CESTER_VERBOSE
---------------

.. code:: c

    CESTER_VERBOSE()

Print as much info as possible into the output stream. With this option set both passed 
and failed expression evaluated will be printed in the result. The option can also be set 
from the cli using `--cester-verbose`. 

CESTER_PRINT_VERSION
---------------------

.. code:: c

    CESTER_PRINT_VERSION()

Print cester version before running any test. The option can also be set from the cli 
using `--cester-printversion`.

CESTER_SINGLE_OUPUT_ONLY
-------------------------

.. code:: c

    CESTER_SINGLE_OUPUT_ONLY()

Display test for a single test case only, skip syntesis and summary. This option can also be 
set from the command line with `--cester-singleoutput`

CESTER_NO_ISOLATION
---------------------

.. code:: c

    CESTER_NO_ISOLATION()

Do not isolate the tests, run each of the test cases in a single process. The drawback is 
if a test case causes segfault or crash the entire test crashes and no summary is displayed. 
No isolation causes a crash one crash all scenerio.
    
This option can also be set from the command line with `--cester-noisolation`

CESTER_NO_MEMTEST
---------------------

.. code:: c

    CESTER_NO_MEMTEST()

Disable memory leak detection test. This option can also be set from the command line 
with `--cester-nomemtest`

CESTER_DO_MEMTEST
---------------------

.. code:: c

    CESTER_SINGLE_OUPUT_ONLY()

Enable memory allocation. The combination of CESTER_NO_MEMTEST() and  CESTER_DO_MEMTEST() 
is valid only in non isolated tests. 

This togle combined with `CESTER_NO_MEMTEST()` can be used to selectively test memory 
allocation in a test e.g. Calling CESTER_NO_MEMTEST() before a test case will prevent memory 
test from the beginning of that function and calling CESTER_DO_MEMTEST() at the end of the 
test case will ensure memory allocation will be validated in all the other test case that follows.

CESTER_OUTPUT_TEXT
---------------------

.. code:: c

    CESTER_OUTPUT_TEXT()

Change the output format to text. This option can also be set from the command line 
with `--cester-format=text`


CESTER_OUTPUT_JUNITXML
-----------------------

.. code:: c

    CESTER_OUTPUT_JUNITXML()

Change the output format to junitxml. This option can also be set from the command line 
with `--cester-format=junitxml`


CESTER_OUTPUT_TAP
-----------------------

.. code:: c

    CESTER_OUTPUT_TAP()

Change the output format to TAP (Test Anything Protocol). This option can also be set from 
the command line with `--cester-format=tap`


CESTER_OUTPUT_TAPV13
-----------------------

.. code:: c

    CESTER_OUTPUT_TAPV13()

Change the output format to TAP (Test Anything Protocol) Version 13. This option can also 
be set from the command line with `--cester-format=tapV13`


CESTER_FORMAT_TESTNAME
-----------------------

.. code:: c

    CESTER_FORMAT_TESTNAME()

Format the test case name for output. E.g the test name  `modify_test_instance` becomes 
`modify test instance`. This does not apply to junitxml as the test name remain the way it declared in the test 
source.


CESTER_DONT_FORMAT_TESTNAME
-----------------------------

.. code:: c

    CESTER_DONT_FORMAT_TESTNAME()

Do not format the test case name, it remain the way it declared in the test source. 
This option can also be set from the command line with `--cester-dontformatname`


CESTER_VERSION
---------------

.. code:: c

    printf("v%s", CESTER_VERSION);

Current cester version 

CESTER_LICENSE
---------------

.. code:: c

    printf("%s", CESTER_LICENSE);

cester licence **GNU General Public License v3.0**
