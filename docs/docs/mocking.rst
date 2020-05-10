
.. index::
	single: mocking

Mocking
=========

cester supports mocking function. The mock feature currently works on GCC compiler only because 
of the use of the `--wrap` option which is not supported on MAC OSX and might not be available in other compilers.

The following macros are use for mocking

- `CESTER_NO_MOCK <./macros.html#define-cester-no-mock>`_
- `CESTER_MOCK_SIMPLE_FUNCTION <./macros.html#cester-mock-simple-function>`_
- `CESTER_MOCK_FUNCTION <./macros.html#cester-mock-function>`_

Mocking a simple function
--------------------------

The macro CESTER_MOCK_SIMPLE_FUNCTION can be used to mock a function to return a value. 
The macro simply wrap the function to return the third parameter when invoked.

Example: 

The following test mock a function that accepts no parameter and return a value.

**originals.c**

.. code:: c

    int multiply_by() {
        return 2;
    }

    int multiply_a_number(int a) {
        return a * multiply_by() ;
    }

**test_mock.c**

.. code:: c

    #include <exotic/cester.h>
    #include "originals.c"

    CESTER_MOCK_SIMPLE_FUNCTION(multiply_by(), int, 5)

    CESTER_TEST(check_mocked_function, test_instance,
        cester_assert_equal(multiply_a_number(2), 10);
    )


Compile your test file with the --wrap option e.g. in the example above the function 
`multiply_by` was mocked so the option *-Wl,--wrap=multiply_by* is supplied during 
compilation. 

.. code:: bash

    gcc test_mock.c -I. -Wl,--wrap=multiply_by -o test_mock
    ./test_mock
        
    + (0.00s) check mocked function

    Ran 1 test(s) in 0.00 Seconds
    Synthesis: SUCCESS Tests: 1 | Passing: 1 | Failing: 0


In the example above the function `multiply_by` was mocked to return 5 instead of 2, without 
mocking it the test will fail because `multiply_a_number(2)` will return 4 instead of 10.

Mocking a function
--------------------------

The macro CESTER_MOCK_FUNCTION can be used to mock a function to with a body. Compare to the 
CESTER_MOCK_SIMPLE_FUNCTION macro this macro can wrap a function that returns or does not 
return a value. 

Example: 

The following test mock a function that accepts 2 parameters a pointer to integer and another 
integer, then return the power of the first parameter. 

**originals.c**

.. code:: c

    int power_of(int* num1, int num2) {
        return *num1 * num2;
    }

In the function above the returned value is not correct as it does not return the actual power 
of the num1 pointer. in our test we will mock the function to properly calculates the power of 
the num1 pointer.

**test_mock.c**

.. code:: c

    #include <exotic/cester.h>
    #include "originals.c"

    CESTER_MOCK_FUNCTION(power_of(int* num1, int num2), int, 
        int return_val = *num1;
        while (num2-->1) {
            return_val *= *num1;
        }
        return return_val;
    )

    CESTER_TEST(check_mocked_function, test_instance,
        int num = 2;
        cester_assert_equal(power_of(&num, 3), 8);
    )

Compile your test file with the --wrap option e.g. in the example above the function 
`power_of` was mocked so the option *-Wl,--wrap=power_of* is supplied during 
compilation. 

.. code:: bash

    gcc test_mock.c -I. -Wl,--wrap=power_of -o test_mock
    ./test_mock

    + (0.00s) check mocked function

    Ran 1 test(s) in 0.001000 Seconds
    Synthesis: SUCCESS Tested: 1 | Passing: 1 | Failing: 0


To disable mocking in a test without deleting your mock code you can chose not to compile 
the test with the -Wl,--wrap option or you can define `CESTER_NO_MOCK` anywhere in the code. 


.. warning::

    Static functions cannot be mocked in cester.