
.. index::
	single: selective_compilation

Selective Modular Features
=============================

libcester is build in a very modular manner such that most of the component can be removed and 
the main feature which is running and reporting test still take place. By excluding some features 
the generated binary will be smaller compare to when all the features are left to 
be compiled, by excluding some features libcester is guaranteed to work on various platforms even 
with very minimal resources.


Do not Include windows.h
-------------------------

Including the **windows.h** header causes problem in some test, so it important to provide 
solution in such case. By defining the macro `CESTER_EXCLUDE_WINDOWS_H` the windows.h file will 
not be included in the test. 

The main reason for including the windows.h in libcester is just for printing the text output format with 
color as the windows terminal by default does not recognize the ASI escape code without changing 
the mode. So this means that on windows terminal with the old mode the raw ansi code will be written 
into the terminal else the option is set to no color. This will also disable the execution of test 
case in independent processes and will rely on signal for recovery from critical error on windows.

The issue related to this was first reported by `MarcelInTO <https://github.com/MarcelInTO>`_ in the pr 
`47 <https://github.com/exoticlibraries/libcester/pull/47>`_.

Exclude time report
------------------------

Time keeping causes problem for test which are built for execution on a platform that does not have 
a proper time keeping mechanism or does not support floating point data types, example of such platform 
is the PlayStation 1. 

By defining the macro `CESTER_NO_TIME` before including cester.h all the time keeping feature will be 
disabled, this also reduce the generated binary by 3kb on Windows 10 64 bit compiled with GCC version 10
with one test case. This feature was introduced by `nicolasnoble <https://github.com/nicolasnoble>`_ in 
the pr `14 <https://github.com/exoticlibraries/libcester/pull/14>`_.

By removing this feature all time related feature such as keeping record of how long a test case 
execution take, specifying how long a test case should run will be disabled.

Remove recovery with signal.h
-------------------------------

On a platform that does not support running test case on their seperate processes, libcester rely on 
signal.h to recover from critical faulure such as segfault. But in a situation when you are sure 
any of the test case will not crash you can disable signal.h recovery by defining the macro 
`CESTER_NO_SIGNAL`.

By disabling signal revovery method the generated binary size reduce by 1kb on Windows 10 64 bit 
compiled with GCC version 10 with one test case.

Disable memory test
---------------------

The framework has a very minimal memory test feature that track the amount of memory allocated, 
it lifecycle and report failure for the test case if it leak any memory, try to use freed memory or 
trying to free an already freed memory. 

This feature is optional as it might cause issues on some platform, this can also be diabled by 
defining the macro `CESTER_NO_MEM_TEST` before including cester.h this reduces the generated binary 
size reduce by 2kb on Windows 10 64 bit compiled with GCC version 10 with one test case.

Select Reporter To Compile
----------------------------
WIP

Exclude JunitXml Report
''''''''''''''''''''''''
WIP

Exclude Text Report
'''''''''''''''''''''
WIP

Exclude Tap Report
''''''''''''''''''''
WIP

Exclude TapV13 Report
'''''''''''''''''''''
WIP
