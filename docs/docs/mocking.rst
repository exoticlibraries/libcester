
.. index::
	single: mocking

Mocking
=========

cester supports Mocking field, function and struct. If your test uses the mock feature it 
requires two level compilation to properly override a function. The first step is generating the 
expanded source into an intermediate file, then the next and final step is to compile the 
intermediate file to binary. 

Example: 

The following test mock a function that was defined in another source file.

**originals.c**

.. code:: c

    #include <exotic/cester.h>
    CESTER_MOCK_FIELD(name, "libcester")

    CESTER_TEST(mock_test, test_instance,
        cester_assert_equal(CESTER_MOCK_GET(name), "libcester");
        cester_assert_not_equal(_(name), "exoticlibs");
    )



.. code:: c

    h