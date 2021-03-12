
.. index::
	single: known_issues

Known Unfixed Issues
========================

There are some issues detected that cannot or has not not been fixed in the framework, and some 
features that is close to impossible to implements, these two group of farts are highlighted here:

C++ Dynamic Deallocation
-------------------------------------------

In C++ it impossible to use the shared test instance variable to share objects that are automatically 
deallocated when they fall out of scope. For example if a **std::vector** object is to be used to 
share data across multiple test case and the data is added to the vector object in one of the 
fixture function (CESTER_BEFORE_ALL, CESTER_BEFORE_EACH), all the test cases relying on the data 
will fail as the vector object will call it deallocator at the end of the fixture function, hence 
it will be null in all the test cases.

The solution in this case is to use the global scope for such object and not the `shared_instance->arg` 
variable, the `shared_instance->ar` will work fine for dynamically allocated objects. 

Instead of 

.. code:: c

	//...
	CESTER_BEFORE_ALL(inst,  
		std::vector<int> setup;
		inst->arg = & setup;
	)

	CESTER_TEST(vector_push_back, inst, {
		std::vector<int> setup = *(std::vector<int> *)(inst->arg);
		setup.push_back(20);
	})
	//...

Define in global scope instead

.. code:: c

	//...
	CESTER_BODY(
		std::vector<int> setup;
	)

	CESTER_TEST(vector_push_back, inst, {
		setup.push_back(20);
	})
	//...

This isssue was reported `MarcelInTO <https://github.com/MarcelInTO>`_ in issue 
`50 <https://github.com/exoticlibraries/libcester/issues/50>`_.


