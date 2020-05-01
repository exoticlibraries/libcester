
.. index::
	single: assertions

Assertion Macros
=================

All assertion macros are in lowercese and starts with `cester_assert_` 

cester_assert_true
--------------------

Check if the argument, expression evaluates to true. It accepts one parameter which is the 
expression to evaluate. It prints out the expression as it in the source code no formating 
is applied. 

.. code:: c

	cester_assert_true(2 > 1);