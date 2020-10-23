
.. index::
	single: options

How the mocking works
=======================

The macro CESTER_MOCK_FUNCTION declares a weak reference of the function to mock, 
declares a __real_ function signature and at the last expansion stage declares and initialize 
a __weak_ wrapper function.

The following example mock a function 

.. code:: text 

	CESTER_MOCK_FUNCTION(power_of(int* num1, int num2), int, 
		int return_val = *num1;
		while (num2-->1) {
			return_val *= *num1;
		}
		return return_val;
	)

First macro expansion we have 

.. code:: text 

	__attribute__((weak)) int power_of(int* num1, int num2); 
	extern int __real_power_of(int* num1, int num2);


In the final expansion 

.. code:: text 

	int __real_power_of(int* num1, int num2) {
		int return_val = *num1;
		while (num2-->1) {
			return_val *= *num1;
		}
		return return_val;
	}


At the end of the macro expansion we have 

.. code:: text

	__attribute__((weak)) int power_of(int* num1, int num2); 
	extern int __real_power_of(int* num1, int num2);

	int __real_power_of(int* num1, int num2) {
		int return_val = *num1;
		while (num2-->1) {
			return_val *= *num1;
		}
		return return_val;
	}

The function **power_of** will then be mocked if compiled with the `-Wl,--wrap=power_of` 
option. 

The same logic applies to CESTER_MOCK_SIMPLE_FUNCTION macro except it returns the last 
parameter. 