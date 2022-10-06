
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


cester_assert_true_msg
-----------------------

Check if the argument, expression evaluates to true. It accepts one parameter which is the 
expression to evaluate. It prints out the the second arguments as expression in the output. 

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_true(2 > 1, "is 2 greater than 1?"); 
	)

**Parameters**

    x - the expression to check if true |br|
    y - the text to print in the output


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


cester_assert_false_msg
------------------------

Check if the argument, expression evaluates to false. It accepts one parameter which is the 
expression to evaluate. It prints out the the second arguments as expression in the output.

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_false(2 < 1); 
	)

**Parameters**

    x - the expression to check if false |br|
    y - the text to print in the output


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


cester_assert_cmp_char
-----------------------------

Compare two characters using the provided operator. This macro prints out the actual values of 
the two characters.

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_cmp_char('a', ==, 'a', "verify that a is same as a");
	)

**Parameters**

    w - a char |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - another char |br|
    z - the string formated for output |br|


cester_assert_char_eq
-----------------------------

Check if the two characters are the same. This macro prints out the actual values of the 
two characters.

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_char_eq('i', 'i');
	)

**Parameters**

	x - a char |br|
	y - another char |br|


cester_assert_char_ne
-----------------------------

Check if the two characters are not the same. This macro prints out the actual values of the 
two characters.

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_char_ne('i', 'j');
	)

**Parameters**

	x - a char |br|
	y - another char |br|


cester_assert_char_gt
-----------------------------

Check if the a char is greater than the other. This macro prints out the actual values of the 
two characters.

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_char_gt('z', 's');
	)

**Parameters**

	x - a char |br|
	y - another char |br|


cester_assert_char_ge
-----------------------------

Check if the a char is greater than or equal to the other. This macro prints out the actual 
values of the two characters.

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_char_ge('k', 'k');
	)

**Parameters**

	x - a char |br|
	y - another char |br|


cester_assert_char_lt
-----------------------------

Check if the a char is lesser than the other. This macro prints out the actual values of the 
two characters.

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_char_lt('r', 's');
	)

**Parameters**

	x - a char |br|
	y - another char |br|


cester_assert_char_le
-----------------------------

Check if the a char is lesser than or equal to the other. This macro prints out the actual 
values of the two characters.

.. code:: c

	#include <exotic/cester.h>

	CESTER_TEST(example_case, _,
		cester_assert_char_le('a', 'b');
	)

**Parameters**

	x - a char |br|
	y - another char |br|


cester_assert_cmp_uchar
-----------------------------

Compare two unsigned chars using the provided operator. This macro prints out the actual values of 
the two unsigned characters.

**Parameters**

    w - a unsigned char |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - another unsigned char |br|
    z - the string formated for output |br|


cester_assert_uchar_eq
-----------------------------

Check if the two unsigned characters are the same. This macro prints out the actual values of the 
two unsigned characters.

**Parameters**

	x - a unsigned char |br|
	y - another unsigned char |br|


cester_assert_uchar_ne
-----------------------------

Check if the two unsigned characters are not the same. This macro prints out the actual values of the 
two unsigned characters.

**Parameters**

	x - a unsigned char |br|
	y - another unsigned char |br|


cester_assert_uchar_gt
-----------------------------

Check if the a unsigned char is greater than the other. This macro prints out the actual values of the 
two unsigned characters.

**Parameters**

	x - a unsigned char |br|
	y - another unsigned char |br|


cester_assert_uchar_ge
-----------------------------

Check if the a unsigned char is greater than or equal to the other. This macro prints out the actual 
values of the two unsigned characters.

**Parameters**

	x - a unsigned char |br|
	y - another unsigned char |br|


cester_assert_uchar_lt
-----------------------------

Check if the a unsigned char is lesser than the other. This macro prints out the actual values of the 
two unsigned characters.

**Parameters**

	x - a unsigned char |br|
	y - another unsigned char |br|


cester_assert_uchar_le
-----------------------------

Check if the a unsigned char is lesser than or equal to the other. This macro prints out the actual 
values of the two unsigned characters.

**Parameters**

	x - a unsigned char |br|
	y - another unsigned char |br|


cester_assert_cmp_short
-----------------------------

Compare two short using the provided operator. This macro prints out the actual values of 
the two shorts.

**Parameters**

    w - a short |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - another short |br|
    z - the string formated for output |br|


cester_assert_short_eq
-----------------------------

Check if the two short are the same. This macro prints out the actual values of the 
two shorts.

**Parameters**

	x - a short |br|
	y - another short |br|


cester_assert_short_ne
-----------------------------

Check if the two shorts are not the same. This macro prints out the actual values of the 
two shorts.

**Parameters**

	x - a short |br|
	y - another short |br|


cester_assert_short_gt
-----------------------------

Check if the a short is greater than the other. This macro prints out the actual values of the 
two shorts.

**Parameters**

	x - a short |br|
	y - another short |br|


cester_assert_short_ge
-----------------------------

Check if the a short is greater than or equal to the other. This macro prints out the actual 
values of the two shorts.

**Parameters**

	x - a short |br|
	y - another short |br|


cester_assert_short_lt
-----------------------------

Check if the a short is lesser than the other. This macro prints out the actual values of the 
two shorts.

**Parameters**

	x - a short |br|
	y - another short |br|


cester_assert_short_le
-----------------------------

Check if the a short is lesser than or equal to the other. This macro prints out the actual 
values of the two shorts.

**Parameters**

	x - a short |br|
	y - another short |br|


cester_assert_cmp_ushort
-----------------------------

Compare two unsigned shorts using the provided operator. This macro prints out the actual values of 
the two unsigned shorts.

**Parameters**

    w - a unsigned short |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - another unsigned short |br|
    z - the string formated for output |br|


cester_assert_ushort_eq
-----------------------------

Check if the two unsigned shorts are the same. This macro prints out the actual values of the 
two unsigned short.

**Parameters**

	x - a unsigned short |br|
	y - another unsigned short |br|


cester_assert_ushort_ne
-----------------------------

Check if the two unsigned shorts are not the same. This macro prints out the actual values of the 
two unsigned shorts.

**Parameters**

	x - a unsigned short |br|
	y - another unsigned short |br|


cester_assert_ushort_gt
-----------------------------

Check if the a unsigned short is greater than the other. This macro prints out the actual values of the 
two unsigned shorts.

**Parameters**

	x - a unsigned short |br|
	y - another unsigned short |br|


cester_assert_ushort_ge
-----------------------------

Check if the a unsigned short is greater than or equal to the other. This macro prints out the actual 
values of the two unsigned shorts.

**Parameters**

	x - a unsigned short |br|
	y - another unsigned short |br|


cester_assert_ushort_lt
-----------------------------

Check if the a unsigned short is lesser than the other. This macro prints out the actual values of the 
two unsigned shorts.

**Parameters**

	x - a unsigned short |br|
	y - another unsigned short |br|


cester_assert_ushort_le
-----------------------------

Check if the a unsigned short is lesser than or equal to the other. This macro prints out the actual 
values of the two unsigned shorts.

**Parameters**

	x - a unsigned short |br|
	y - another unsigned short |br|


cester_assert_cmp_int
-----------------------------

Compare two int using the provided operator. This macro prints out the actual values of 
the two ints.

**Parameters**

    w - a int |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - another int |br|
    z - the string formated for output |br|


cester_assert_int_eq
-----------------------------

Check if the two int are the same. This macro prints out the actual values of the 
two ints.

**Parameters**

	x - a int |br|
	y - another int |br|


cester_assert_int_ne
-----------------------------

Check if the two ints are not the same. This macro prints out the actual values of the 
two ints.

**Parameters**

	x - a int |br|
	y - another int |br|


cester_assert_int_gt
-----------------------------

Check if the a int is greater than the other. This macro prints out the actual values of the 
two ints.

**Parameters**

	x - a int |br|
	y - another int |br|


cester_assert_int_ge
-----------------------------

Check if the a int is greater than or equal to the other. This macro prints out the actual 
values of the two ints.

**Parameters**

	x - a int |br|
	y - another int |br|


cester_assert_int_lt
-----------------------------

Check if the a int is lesser than the other. This macro prints out the actual values of the 
two ints.

**Parameters**

	x - a int |br|
	y - another int |br|


cester_assert_int_le
-----------------------------

Check if the a int is lesser than or equal to the other. This macro prints out the actual 
values of the two ints.

**Parameters**

	x - a int |br|
	y - another int |br|


cester_assert_cmp_uint
-----------------------------

Compare two unsigned ints using the provided operator. This macro prints out the actual values of 
the two unsigned ints.

**Parameters**

    w - a unsigned int |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - another unsigned int |br|
    z - the string formated for output |br|


cester_assert_uint_eq
-----------------------------

Check if the two unsigned ints are the same. This macro prints out the actual values of the 
two unsigned int.

**Parameters**

	x - a unsigned int |br|
	y - another unsigned int |br|


cester_assert_uint_ne
-----------------------------

Check if the two unsigned ints are not the same. This macro prints out the actual values of the 
two unsigned ints.

**Parameters**

	x - a unsigned int |br|
	y - another unsigned int |br|


cester_assert_uint_gt
-----------------------------

Check if the a unsigned int is greater than the other. This macro prints out the actual values of the 
two unsigned ints.

**Parameters**

	x - a unsigned int |br|
	y - another unsigned int |br|


cester_assert_uint_ge
-----------------------------

Check if the a unsigned int is greater than or equal to the other. This macro prints out the actual 
values of the two unsigned ints.

**Parameters**

	x - a unsigned int |br|
	y - another unsigned int |br|


cester_assert_uint_lt
-----------------------------

Check if the a unsigned int is lesser than the other. This macro prints out the actual values of the 
two unsigned ints.

**Parameters**

	x - a unsigned int |br|
	y - another unsigned int |br|


cester_assert_uint_le
-----------------------------

Check if the a unsigned int is lesser than or equal to the other. This macro prints out the actual 
values of the two unsigned ints.

**Parameters**

	x - a unsigned int |br|
	y - another unsigned int |br|


cester_assert_cmp_long
-----------------------------

Compare two long using the provided operator. This macro prints out the actual values of 
the two longs.

**Parameters**

    w - a long |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - another long |br|
    z - the string formated for output |br|


cester_assert_long_eq
-----------------------------

Check if the two long are the same. This macro prints out the actual values of the 
two longs.

**Parameters**

	x - a long |br|
	y - another long |br|


cester_assert_long_ne
-----------------------------

Check if the two longs are not the same. This macro prints out the actual values of the 
two longs.

**Parameters**

	x - a long |br|
	y - another long |br|


cester_assert_long_gt
-----------------------------

Check if the a long is greater than the other. This macro prints out the actual values of the 
two longs.

**Parameters**

	x - a long |br|
	y - another long |br|


cester_assert_long_ge
-----------------------------

Check if the a long is greater than or equal to the other. This macro prints out the actual 
values of the two longs.

**Parameters**

	x - a long |br|
	y - another long |br|


cester_assert_long_lt
-----------------------------

Check if the a long is lesser than the other. This macro prints out the actual values of the 
two longs.

**Parameters**

	x - a long |br|
	y - another long |br|


cester_assert_long_le
-----------------------------

Check if the a long is lesser than or equal to the other. This macro prints out the actual 
values of the two longs.

**Parameters**

	x - a long |br|
	y - another long |br|


cester_assert_cmp_ulong
-----------------------------

Compare two unsigned longs using the provided operator. This macro prints out the actual values of 
the two unsigned longs.

**Parameters**

    w - a unsigned long |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - another unsigned long |br|
    z - the string formated for output |br|


cester_assert_ulong_eq
-----------------------------

Check if the two unsigned longs are the same. This macro prints out the actual values of the 
two unsigned long.

**Parameters**

	x - a unsigned long |br|
	y - another unsigned long |br|


cester_assert_ulong_ne
-----------------------------

Check if the two unsigned longs are not the same. This macro prints out the actual values of the 
two unsigned longs.

**Parameters**

	x - a unsigned long |br|
	y - another unsigned long |br|


cester_assert_ulong_gt
-----------------------------

Check if the a unsigned long is greater than the other. This macro prints out the actual values of the 
two unsigned longs.

**Parameters**

	x - a unsigned long |br|
	y - another unsigned long |br|


cester_assert_ulong_ge
-----------------------------

Check if the a unsigned long is greater than or equal to the other. This macro prints out the actual 
values of the two unsigned longs.

**Parameters**

	x - a unsigned long |br|
	y - another unsigned long |br|


cester_assert_ulong_lt
-----------------------------

Check if the a unsigned long is lesser than the other. This macro prints out the actual values of the 
two unsigned longs.

**Parameters**

	x - a unsigned long |br|
	y - another unsigned long |br|


cester_assert_ulong_le
-----------------------------

Check if the a unsigned long is lesser than or equal to the other. This macro prints out the actual 
values of the two unsigned longs.

**Parameters**

	x - a unsigned long |br|
	y - another unsigned long |br|


cester_assert_cmp_llong
-----------------------------

Compare two long long using the provided operator. This macro prints out the actual values of 
the two long long.

**Parameters**

    w - a long long |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - another long long |br|
    z - the string formated for output |br|


cester_assert_llong_eq
-----------------------------

Check if the two long long are the same. This macro prints out the actual values of the 
two long long.

**Parameters**

	x - a long long |br|
	y - another long long |br|


cester_assert_llong_ne
-----------------------------

Check if the two long long are not the same. This macro prints out the actual values of the 
two long long.

**Parameters**

	x - a long long |br|
	y - another long long |br|


cester_assert_llong_gt
-----------------------------

Check if the a long long is greater than the other. This macro prints out the actual values of the 
two long long.

**Parameters**

	x - a long long |br|
	y - another long long |br|


cester_assert_llong_ge
-----------------------------

Check if the a long long is greater than or equal to the other. This macro prints out the actual 
values of the two long long.

**Parameters**

	x - a long long |br|
	y - another long long |br|


cester_assert_llong_lt
-----------------------------

Check if the a long long is lesser than the other. This macro prints out the actual values of the 
two long long.

**Parameters**

	x - a long long |br|
	y - another long long |br|


cester_assert_llong_le
-----------------------------

Check if the a long long is lesser than or equal to the other. This macro prints out the actual 
values of the two long long.

**Parameters**

	x - a long long |br|
	y - another long long |br|


cester_assert_cmp_ullong
-----------------------------

Compare two unsigned long long using the provided operator. This macro prints out the actual values of 
the two unsigned long long.

**Parameters**

    w - a unsigned long long |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - another unsigned long long |br|
    z - the string formated for output |br|


cester_assert_ullong_eq
-----------------------------

Check if the two unsigned long long are the same. This macro prints out the actual values of the 
two unsigned long long.

**Parameters**

	x - a unsigned long long |br|
	y - another unsigned long long |br|


cester_assert_ullong_ne
-----------------------------

Check if the two unsigned long long are not the same. This macro prints out the actual values of the 
two unsigned long long.

**Parameters**

	x - a unsigned long long |br|
	y - another unsigned long long |br|


cester_assert_ullong_gt
-----------------------------

Check if the a unsigned long long is greater than the other. This macro prints out the actual values of the 
two unsigned long long.

**Parameters**

	x - a unsigned long long |br|
	y - another unsigned long long |br|


cester_assert_ullong_ge
-----------------------------

Check if the a unsigned long long is greater than or equal to the other. This macro prints out the actual 
values of the two unsigned long long.

**Parameters**

	x - a unsigned long long |br|
	y - another unsigned long long |br|


cester_assert_ullong_lt
-----------------------------

Check if the a unsigned long long is lesser than the other. This macro prints out the actual values of the 
two unsigned long long.

**Parameters**

	x - a unsigned long long |br|
	y - another unsigned long long |br|


cester_assert_ullong_le
-----------------------------

Check if the a unsigned long long is lesser than or equal to the other. This macro prints out the actual 
values of the two unsigned long long.

**Parameters**

	x - a unsigned long long |br|
	y - another unsigned long long |br|


cester_assert_cmp_float
-----------------------------

Compare two float using the provided operator. This macro prints out the actual values of 
the two double.

**Parameters**

    w - a float |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - another float |br|
    z - the string formated for output |br|


cester_assert_float_eq
-----------------------------

Check if the two float are the same. This macro prints out the actual values of the 
two double.

**Parameters**

	x - a float |br|
	y - another float |br|


cester_assert_float_ne
-----------------------------

Check if the two double are not the same. This macro prints out the actual values of the 
two double.

**Parameters**

	x - a float |br|
	y - another float |br|


cester_assert_float_gt
-----------------------------

Check if the a float is greater than the other. This macro prints out the actual values of the 
two double.

**Parameters**

	x - a float |br|
	y - another float |br|


cester_assert_float_ge
-----------------------------

Check if the a float is greater than or equal to the other. This macro prints out the actual 
values of the two double.

**Parameters**

	x - a float |br|
	y - another float |br|


cester_assert_float_lt
-----------------------------

Check if the a float is lesser than the other. This macro prints out the actual values of the 
two double.

**Parameters**

	x - a float |br|
	y - another float |br|


cester_assert_float_le
-----------------------------

Check if the a float is lesser than or equal to the other. This macro prints out the actual 
values of the two double.

**Parameters**

	x - a float |br|
	y - another float |br|


cester_assert_cmp_double
-----------------------------

Compare two double using the provided operator. This macro prints out the actual values of 
the two double.

**Parameters**

    w - a double |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - another double |br|
    z - the string formated for output |br|


cester_assert_double_eq
-----------------------------

Check if the two double are the same. This macro prints out the actual values of the 
two double.

**Parameters**

	x - a double |br|
	y - another double |br|


cester_assert_double_ne
-----------------------------

Check if the two double are not the same. This macro prints out the actual values of the 
two double.

**Parameters**

	x - a double |br|
	y - another double |br|


cester_assert_double_gt
-----------------------------

Check if the a double is greater than the other. This macro prints out the actual values of the 
two double.

**Parameters**

	x - a double |br|
	y - another double |br|


cester_assert_double_ge
-----------------------------

Check if the a double is greater than or equal to the other. This macro prints out the actual 
values of the two double.

**Parameters**

	x - a double |br|
	y - another double |br|


cester_assert_double_lt
-----------------------------

Check if the a double is lesser than the other. This macro prints out the actual values of the 
two double.

**Parameters**

	x - a double |br|
	y - another double |br|


cester_assert_double_le
-----------------------------

Check if the a double is lesser than or equal to the other. This macro prints out the actual 
values of the two double.

**Parameters**

	x - a double |br|
	y - another double |br|


cester_assert_cmp_ldouble
-----------------------------

Compare two long double using the provided operator. This macro prints out the actual values of 
the two double.

**Parameters**

    w - a long double |br|
    x - the operator to use for the comparison. One of `==, !=, <, >, <=, >=` |br|
    y - another long double |br|
    z - the string formated for output |br|


cester_assert_ldouble_eq
-----------------------------

Check if the two long double are the same. This macro prints out the actual values of the 
two double.

**Parameters**

	x - a long double |br|
	y - another long double |br|


cester_assert_ldouble_ne
-----------------------------

Check if the two long double are not the same. This macro prints out the actual values of the 
two long double.

**Parameters**

	x - a long double |br|
	y - another long double |br|


cester_assert_ldouble_gt
-----------------------------

Check if the a long double is greater than the other. This macro prints out the actual values of the 
two long double.

**Parameters**

	x - a long double |br|
	y - another long double |br|


cester_assert_ldouble_ge
-----------------------------

Check if the a long double is greater than or equal to the other. This macro prints out the actual 
values of the two double.

**Parameters**

	x - a long double |br|
	y - another long double |br|


cester_assert_ldouble_lt
-----------------------------

Check if the a long double is lesser than the other. This macro prints out the actual values of the 
two double.

**Parameters**

	x - a long double |br|
	y - another long double |br|


cester_assert_ldouble_le
-----------------------------

Check if the a long double is lesser than or equal to the other. This macro prints out the actual 
values of the two double.

**Parameters**

	x - a long double |br|
	y - another long double |br|


cester_assert_stream_content_equal
------------------------------------

Check whether the content of a stream equals a value

**Parameters**

	x - the captured stream |br|
	y - the string to check if it same as the stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stream_content_contain
----------------------------------------

Check whether the content of a stream contains a value

**Parameters**

	x - the captured stream |br|
	y - the string to check if it same as the stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stream_content_not_equal
---------------------------------------

Check whether the content of a stream does not equal a value

**Parameters**

	x - the captured stream |br|
	y - the string to check if it same as the stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stream_content_not_contain
------------------------------------------

Check whether the content of a stream does not contains a value

**Parameters**

	x - the captured stream |br|
	y - the string to check if it same as the stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stdout_stream_content_equal
-----------------------------------------

Check whether the content of stdout stream equals a value

**Parameters**

	x - the captured stdout stream |br|
	y - the string to check if it same as the stdout stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stdout_stream_content_contain
--------------------------------------------

Check whether the content of stdout stream contains a value

**Parameters**

	x - the captured stdout stream |br|
	y - the string to check if it same as the stdout stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stdout_stream_content_not_equal
-----------------------------------------------

Check whether the content of stdout stream does not equals a value

**Parameters**

	x - the captured stdout stream |br|
	y - the string to check if it same as the stdout stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stdout_stream_content_not_contain
------------------------------------------------

Check whether the content of stdout stream does not contains a value

**Parameters**

	x - the captured stdout stream |br|
	y - the string to check if it same as the stdout stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stderr_stream_content_equal
-----------------------------------------

Check whether the content of stderr stream equals a value

**Parameters**

	x - the captured stderr stream |br|
	y - the string to check if it same as the stderr stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stderr_stream_content_contain
--------------------------------------------

Check whether the content of stderr stream contains a value

**Parameters**

	x - the captured stderr stream |br|
	y - the string to check if it same as the stderr stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stderr_stream_content_not_equal
-----------------------------------------------

Check whether the content of stderr stream does not equals a value

**Parameters**

	x - the captured stderr stream |br|
	y - the string to check if it same as the stderr stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stderr_stream_content_not_contain
------------------------------------------------

Check whether the content of stderr stream does not contains a value

**Parameters**

	x - the captured stderr stream |br|
	y - the string to check if it same as the stderr stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stdin_stream_content_equal
-----------------------------------------

Check whether the content of stdin stream equals a value

**Parameters**

	x - the captured stdin stream |br|
	y - the string to check if it same as the stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stdin_stream_content_contain
--------------------------------------------

Check whether the content of stdin stream contains a value

**Parameters**

	x - the captured stdin stream |br|
	y - the string to check if it same as the stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stdin_stream_content_not_equal
-----------------------------------------------

Check whether the content of stdin stream does not equals a value

**Parameters**

	x - the captured stdin stream |br|
	y - the string to check if it same as the stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


cester_assert_stdin_stream_content_not_contain
------------------------------------------------

Check whether the content of stdin stream does not contains a value

**Parameters**

	x - the captured stdin stream |br|
	y - the string to check if it same as the stream content |br|

.. note:: 
    
    This macro is not available if the macro CESTER_NO_STREAM_CAPTURE is defined


	