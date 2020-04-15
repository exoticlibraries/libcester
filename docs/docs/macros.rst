
.. index::
	single: macros


Macros
===========

All macros in the library starts with `CESTER_`.

CESTER_NO_MOCK
---------------

CESTER_MOCK_SIMPLE_FUNCTION
----------------------------

CESTER_MOCK_FUNCTION
--------------------

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

    #include <exotic/cester.h>
    #define CESTER_NO_MAIN

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