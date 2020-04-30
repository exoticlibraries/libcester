
.. index::
	single: faq

FAQ
=========

Q: Best practice for test detection
---------------------------------------

Include the guide for __BASE_FILE__ 

.. code:: c

	#ifndef __BASE_FILE__
	#define CESTER_NO_MAIN
	#endif
	#include <exotic/cester.h>

	//your test cases here

	#ifndef __BASE_FILE__
	CESTER_BODY(
		int main(int argc, char** argv) {
		// register your test cases here 
		return CESTER_RUN_ALL_TESTS(argc, argv);
	}
	)
	#endif

This ensure that if the directive __BASE_FILE__ is not defined by the compiler the test case will be registered 
manually.