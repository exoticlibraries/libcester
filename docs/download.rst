
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

	& $([scriptblock]::Create((New-Object Net.WebClient).DownloadString("https://exoticlibraries.github.io/magic/install.ps1"))) libcester

If you have one of the following compilers in your system the library will be installed for each 
of them 

- GCC
- Clang
- Visual C++

For other compilers the files cester.h will be downloaded into the current working directory 
and can be moved into your include path or used directly in your project.

Linux
^^^^^^^^

Use the remote installation script to install libcester with bash. 
If the command is executes with super user priviledge (sudo) it will be 
installed in the folder /usr/include else it will be installed in the 
folder /usr/local/include. Or you can specify where to install it using 
the option `--installfolder=./`

.. code:: bash 

	bash <(curl -s https://exoticlibraries.github.io/magic/install.sh) libcester


The command above also works for installing libcester on Android using the Termux application.


Other Platforms
^^^^^^^^^^^^^^^^^

You can simply download the header file `cester.h` from the repo into your project source 
folder and include it in your project. Download the file from 
https://github.com/exoticlibraries/libcester/releases. The you can include it in your project
relatively like `#include "cester.h"`.


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