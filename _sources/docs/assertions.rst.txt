
.. index::
	single: assertions

.. |br| raw:: html

	<br />

Assertion Macros
=================

All assertion macros are in lowercase and starts with `cester_assert_` 


cester_assert_cmp_msg
-----------------------

.. code:: c

	#define cester_assert_cmp_msg(w,x,y,z) 

Compare two values using the specified operator. The custom msg value is printed in output 
after the evaluation. The operator determines if the asserion fails or passes. 

**Parameters**

    w - a value to compare to y |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - a value to compare to w |br|
    z - the expression to print in output |br|

cester_assert_true
--------------------

Check if the argument, expression evaluates to true. It accepts one parameter which is the 
expression to evaluate. It prints out the expression as it in the source code no formating 
is applied. 

.. code:: c

	cester_assert_true(2 > 1);


cester_assert_false
--------------------

Check if the argument, expression evaluates to false. It accepts one parameter which is the 
expression to evaluate. It prints out the expression as it in the source code no formating 
is applied. 

.. code:: c

	cester_assert_false(2 < 1);

	
cester_assert_null
-------------------
	
Check if the expression or argument is NULL. Pass if argument is NULL otherwise it fails. 
It prints out the expression as it in the source code no formating is applied. 

.. code:: c

	cester_assert_null(NULL);

	
cester_assert_not_null
------------------------
	
Check if the expression or argument is not NULL. Pass if argument is not NULL otherwise it fails.
It prints out the expression as it in the source code no formating is applied. 

.. code:: c

	cester_assert_not_null("NotNull");


cester_assert_equal
--------------------

Passed if the two parameters value is the same, a simple `==` equal operation is performed 
between the two parameters therefore this function will fail for values of different types. e.g. 
the follwoing expression `cester_assert_equal(1, "Test");` C compiler will warning on 
comparison between integer and char* while in C++ compiler it will fail to compile at all. Only 
data of possibly same type that can be compared with `==` operator should be used with this macro 
else use the designated assertion macro for the types.

.. code:: c

	cester_assert_equal(NULL, ((void*)0));


cester_assert_not_equal
------------------------

Passed if the two parameters are different. The two parameters are compared with the operator 
`!=`, therefore there can be compile time warning or error on comparison between two very 
different type. 

.. code:: c

	cester_assert_not_equal(NULL, "NotEqual");

