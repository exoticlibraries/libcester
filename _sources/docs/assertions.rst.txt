
.. index::
	single: assertions

.. |br| raw:: html

	<br />

Assertion Macros
=================

All assertion macros are in lowercase and starts with `cester_assert_` 


cester_assert_nothing
-----------------------

Does nothing just an empty placeholder. Can be used in the CESTER_SKIP_TEST and 
CESTER_TODO_TEST when compiling with -ansi and -pedantic-errors flag

.. code:: c

	#include <exotic/cester.h>

	CESTER_TODO_TEST(example_case, _,
		cester_assert_nothing();
	)


cester_assert_cmp_msg
-----------------------

Compare two values using the specified operator. The custom msg value is printed in output 
after the evaluation. The operator determines if the asserion fails or passes. 

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_cmp_msg(10, >, 2, "is 10 greater than 2");
	)

**Parameters**

    w - a value to compare to y |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - a value to compare to w |br|
    z - the expression to print in output |br|


cester_assert_cmp
-----------------------

Compare two argument using the provided operator. Prints the expression as in the source code

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_cmp(NULL, ==, ((void*)0));
	)

**Parameters**

    x - a value to compare to z |br|
    y - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    z - a value to compare to x


cester_assert_true
-----------------------

Check if the argument, expression evaluates to true. It accepts one parameter which is the 
expression to evaluate. It prints out the expression as it in the source code no formating 
is applied. 

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_true(2 > 1); 
	)

**Parameters**

    x - the expression to check if true


cester_assert_false
-----------------------

Check if the argument, expression evaluates to false. It accepts one parameter which is the 
expression to evaluate. It prints out the expression as it in the source code no formating 
is applied. 

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_false(2 < 1); 
	)

**Parameters**

    x - the expression to check if false


cester_assert_null
-----------------------

Check if the expression or argument is NULL. Pass if argument is NULL otherwise it fails. 
It prints out the expression as it in the source code no formating is applied. 

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_null(NULL);
	)

**Parameters**

    x - the expression to check if it NULL.


cester_assert_not_null
-----------------------

Check if the expression or argument is not NULL. Pass if argument is NULL otherwise it passes. 
It prints out the expression as it in the source code no formating is applied. 

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_not_null("NotNull");
	)

**Parameters**

    x - the expression to check if it not NULL.


cester_assert_equal
-----------------------

Passed if the two parameters value is the same, a simple `==` equal operation is performed 
between the two parameters therefore this function will fail for values of different types. e.g. 
the follwoing expression `cester_assert_equal(1, "Test");` C compiler will warning on 
comparison between integer and char* while in C++ compiler it will fail to compile at all. Only 
data of possibly same type that can be compared with `==` operator should be used with this macro 
else use the designated assertion macro for the types.

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_equal(NULL, ((void*)0));
	)

**Parameters**

    x - the first expression to compare |br|
    y - the second expression to compare to the first expression |br|


cester_assert_not_equal
--------------------------

Passed if the two parameters are different. The two parameters are compared with the operator 
`!=`, therefore there can be compile time warning or error on comparison between two very 
different type. 

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_not_equal(NULL, "NotEqual");
	)

**Parameters**

    x - the first expression to compare |br|
    y - the second expression to compare to the first expression |br|


cester_assert_str_equal
--------------------------

Compare two strings. If the comparison passes the test case is marked as failed. The advantage 
of this macro is that it display the actual values of the two strings.

.. code:: c

	#include <exotic/cester.h>

	CESTER_BEFORE_ALL(test_instance, 
		test_instance->arg = (void*) "exoticlibs";
	)

	CESTER_TEST(example_case, test_instance,
		cester_assert_str_equal((char*)test_instance->arg, "exoticlibs");
	)

**Parameters**

	x - a string to compare |br|
	y - another string to compare with the first string |br|


cester_assert_str_not_equal
-----------------------------

Compare two strings. If the comparison passes the test case is marked as failed. The advantage 
of this macro is that it display the actual values of the two strings.

.. code:: c

	#include <exotic/cester.h>

	CESTER_BEFORE_ALL(test_instance, 
		test_instance->arg = (void*) "exoticlibs";
	)

	CESTER_TEST(example_case, test_instance,
		cester_assert_str_not_equal((char*)test_instance->arg, NULL);
	)

**Parameters**

	x - a string to compare |br|
	y - another string to compare with the first string |br|


cester_assert_ptr_equal
-----------------------------

Compare two pointers. If the comparison fails the test case is marked as failed. The advantage 
of this macro is that it display the actual values of the two pointers.

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, test_instance,
		cester_assert_ptr_equal(test_instance, test_instance);
	)

**Parameters**

	x - a pointer to compare |br|
	y - another pointer to compare with the first pointer |br|


cester_assert_ptr_not_equal
-----------------------------

Compare two pointers. If the comparison passes the test case is marked as failed. The advantage 
of this macro is that it display the actual values of the two pointers.

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, test_instance,
		cester_assert_ptr_not_equal(test_instance->arg, test_instance);
	)

**Parameters**

	x - a pointer to compare |br|
	y - another pointer to compare with the first pointer |br|
	

