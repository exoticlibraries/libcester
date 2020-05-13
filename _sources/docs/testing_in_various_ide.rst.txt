
.. index::
	single: testing_in_various_ide

Testing in various IDE
======================

Terminal and any text editor
-----------------------------

Visual Studio
---------------

File: TestLibCester.cpp

.. code:: cpp

	#ifndef __BASE_FILE__
	#define CESTER_NO_MAIN
	#endif
	#include <exotic/cester.h>
	#include <iostream>

	CESTER_TEST(test_std_string, inst, {
		std::string str = "This is the string";
		cester_assert_not_equal(str.c_str(), "This is the string");
		cester_assert_str_equal(str.c_str(), "This is the string");
		cester_assert_str_not_equal(str.c_str(), "Not");
	})

	#ifndef __BASE_FILE__
	int main(int argc, char** argv) {
		CESTER_VERBOSE();
		CESTER_MINIMAL();
		CESTER_REGISTER_TEST(test_std_string);
		return CESTER_RUN_ALL_TESTS(argc, argv);
	}
	#endif

Eclipse
----------