
.. toctree::
   :hidden:
   :maxdepth: 1
   :caption: Main
   :name: main-nav

   /download
   /how_it_works


.. toctree::
   :hidden:
   :glob:
   :maxdepth: 1
   :caption: Documentation
   :name: docs-nav

   /docs/*
   

libcester
==========

cester is a header only automated testing framework for the C programming language, 
with support for objects mocking. It requires no dependency and can be downloaded and used in a project 
immediately. cester allows shared instance `test_instance` in which each test cases can use to 
share data and access the command line arguments. It works on a wide range of platforms including embedded and 
with different compilers. 

It automatically register test cases so developer can concentrate more on writing and validating 
the tests. Can output to JUnit XML. 

.. code:: c

    #include <exotic/cester.h>

    CESTER_BEFORE_ALL(test_instance,
        test_instance->arg = "Hello World";
    )

    CESTER_TEST(check_shared_arg, test_instance,
        cester_assert_equal(test_instance->arg, "Hello World");
        cester_assert_not_equal(2, 1);
    )

It follows the original C language specification, ISO/IEC 9899:1990, and the first POSIX 
specification, IEEE Std 1003.1-1988, to the letter avoiding newer features of C compilers as 
much a possible. The project includes only stdlib.h, time.h, stdio.h and windows.h on WIndows 
to color output. Some function are manually implemented in the library to ensure it works in 
embedded systems and even in the most isolated systems.

The project is designed for C, but also works with C++ but be ready for waves of warnings.