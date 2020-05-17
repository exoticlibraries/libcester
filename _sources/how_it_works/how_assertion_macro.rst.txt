
.. index::
	single: how_assertion_macro

How the assertion macros works
================================

.. note::

	This describe internal working of some of the APIs only

The CESTER_CONCAT is used to combine various function with the same parameter signature 
enabling re-use of same code.

The macro **__internal_cester_assert_cmp** is used to create the parameter signature for the 
compare asert functions. For the sample macro below

.. code:: text

	__internal_cester_assert_cmp(1,==,2,"Check if 1 is equal to 2")
	//expands to
	(1 == 2, "Check if 1 is equal to 2", 1, 2, "==", __FILE__, __LINE__)

The parameter signature above is then concatenated with the proper assert function e.g to 
assert if 1 equal to 2 the function `cester_compare_int` is concatenated with the macro 
above.

.. code:: text 

	CESTER_CONCAT(cester_compare_int, __internal_cester_assert_cmp(1,==,2,"Check if 1 is equal to 2"))
	//expands to the function call
	cester_compare_int (1 == 2, "Check if 1 is equal to 2", 1, 2, "==", __FILE__, __LINE__)


The combination of the __internal_cester_assert_cmp with various type assert function reduces 
repeated code.

The macro `__internal_cester_assert_eq` is used to generate the parameter signature and 
formated string for assertion. It accept the two values, the operator and the values 
format specifiers.

.. code:: text

	__internal_cester_assert_eq(1,2,%d)
	//expands to 
	(1 == 2, "expected %d,%s received %d", 1, 2, "", __FILE__, __LINE__)


Hence concating the parameter signature with the function name cester_compare_int result is 

.. code:: text 

	CESTER_CONCAT(cester_compare_int, __internal_cester_assert_eq(1,2,%d))
	//expands to the function call
	cester_compare_int (1 == 2, "expected %d,%s received %d", 1, 2, "", __FILE__, __LINE__)

	CESTER_CONCAT(cester_compare_char, __internal_cester_assert_eq('a','a',%c))
	//expands to the function call
	cester_compare_char ('a' == 'a', "expected %c,%s received %c", 'a', 'b', "", __FILE__, __LINE__)


The macros __internal_cester_assert_ne, __internal_cester_assert_gt, __internal_cester_assert_ge, 
__internal_cester_assert_lt, and __internal_cester_assert_le works just like 
__internal_cester_assert_eq.

.. code:: text 

	cester_assert_int_gt(3,4)
	//expands to 
	CESTER_CONCAT(cester_compare_int, __internal_cester_assert_gt(3,4,%d))
	//expands to the function call
	cester_compare_int (3 > 4, "expected value to be greater than %d,%s received %d", 3, 4, "", __FILE__, __LINE__)




