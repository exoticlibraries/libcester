
.. index::
	single: assertions

Assertion Macros
=================

All assertion macros are in lowercase and starts with `cester_assert_` 


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
