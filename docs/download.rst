
.. index::
	single: download

Download
=========

Using installation scripts
---------------------------

Windows
^^^^^^^^

Install the library using powershell. It auto detect your insalled C and C++ compilers 
include directory and install libcester into the include folder. Execute the command in 
powershell as admin to install cester for compiler like Visual C++.

.. code:: powershell

	Set-ExecutionPolicy Bypass -Scope Process -Force; iex ((New-Object System.Net.WebClient).DownloadString('https://exoticlibraries.github.io/libcester/cester.ps1'))

If you have one of the following compilers in your system the library will be installed for each 
of them 

- GCC
- Clang
- Visual C++

For other compilers the files cester.h will be downloaded into the current working directory 
and can be moved into your include path or used directly in your project.

Linux
^^^^^^^^

Use the remote installation script to install libcester with bash. Before running this 
command ensure you are root `su` so it can move cester.h to the /usr/include/ folder. 

.. code:: bash 

	bash <(curl -s https://exoticlibraries.github.io/libcester/cester.sh)


The command above also works for installing libcester on Android using the Termux application.


Other Platforms
^^^^^^^^^^^^^^^^^

You can simply download the header file `cester.h` from the repo into your project source 
folder and include it in your project. Download the file from 
https://github.com/exoticlibraries/libcester/releases. The you can include it in your project
relatively like `#include "cester.h"`.

Using irorun
-------------

Install irorun from https://exoticlibraries.github.io/irorun 

Installing directly from the repo

.. code::  

	irorun install libcester --github=https://github.com/exoticlibraries/libcester

Installing from vcpkg directory

.. code::  

	irorun install libcester

The library will be installed for the following compilers and others installed compilers recognized by irorun.

- GCC
- CMAKE
- Visual C++


Using Microsoft vcpkg
-----------------------

.. code::  

	irorun install libcester

To use the library after installation with vcpkg with your build system, 
continue with `vcpkg documentation <https://github.com/microsoft/vcpkg/blob/master/docs/index.md>`_ and 
`integration with build systems <https://github.com/microsoft/vcpkg/blob/master/docs/users/integration.md>`_


.. note::

	If you are compiling with a compiler with the macro __BASE_FILE__ defined always add the 
	option **-I.** so it can detect the base file where the test case are declared. 