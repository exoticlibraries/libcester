
![](https://github.com/exoticlibraries/libcester/raw/master/docs/cester.png)

# libcester

A robust header only unit testing framework for C programming language. Support function mocking, memory leak detection, crash report. 

___

cester is a header only automated testing framework for the C programming language, it requires no dependency and can be downloaded and used in a project immediately. cester supports function mocking and allows shared instance `test_instance` in which each test cases can use to share data and access the command line arguments. 

```c
//!gcc {0} -I. -o test; ./test
#include <exotic/cester.h>

CESTER_BEFORE_ALL(test_instance,
    test_instance->arg = "Hello World";
)

CESTER_TEST(check_shared_arg, test_instance,
    cester_assert_string_equal(test_instance->arg, "Hello World");
    cester_assert_not_equal(2, 1);
)
```

The test results can be outputed as JUnit XML format by specifying the cli option `--cester-junitxml`.
___

## Table of content
- [Portability](#portability)
- [Installation](#installation)
	- [Install](#install)
		- [Windows](#windows)
		- [Linux](#linux)
		- [Other platforms](#other-platforms)
- [Documentation](#documentation)
- [Mocking](#mocking)
- [Usage](#usage)
    - [Writing and Running test](#writing-test)
    - [Cester options](#cester-options)
	- [Macros](#macros)
- [FAQ](#faq)
	- [No test case detected](#no-test-case-detected)
- [How it works](#how-it-works)
- [Contributing](#contributing)
- [Useful Links](#useful-links)
- [License](#license)

## Portability

cester follows the original C language specification, ISO/IEC 9899:1990, and the first POSIX specification, IEEE Std 1003.1-1988, to the letter. cester avoids newer features of C compilers. The project includes only `stdlib.h`, `time.h`, `stdio.h` and `windows.h` on WIndows to color output. Some function are manually implemented in the library to ensure it works in embedded system and even in the most isolated system. 

The project is designed for C, but also works with C++ as it compatible with C++11 Standard (ISO/IEC 14882:2011).

## Installation

If you install the library file `cester.h` using any of the commands below, it can be included in your test like `<exotic/cester.h>`.

### Windows

Install the library using powershell. It auto detect your C compiler include directory and install libcester into the include folder. Execute the command in powershell.

```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; iex ((New-Object System.Net.WebClient).DownloadString('https://exoticlibraries.github.io/dl/cester/cester.ps1'))
```

### Linux

Use apt package manager to install libcester 

```bash
apt install libcester
```

Use the remote installation script to install libcester with bash. Before running this command ensure you are root `su` so it can move cester.h to the /usr/include/ folder. 

```bash
bash <(curl -s https://exoticlibraries.github.io/dl/cester/cester.sh)
```

### Other platforms

You can simply download the header file `cester.h` from the repo in your project source folder and include it in your project. Download the file from [here](https://raw.githubusercontent.com/exoticlibraries/libcester/master/include/exotic/cester.h). The you can include it in your test relatively like `#include "cester.h"`.

## Documentation

## Mocking

## Usage

### Writing and Running test

### Macros

### Cester options

## FAQ

### No test detected

If no test was ran or your test cases were not detected, in most cases it because your compiler did not define the __BASE_FILE__ macro. If you are using the Visual studio IDE you should define the macro in 
`Properties -> C/C++ -> Preprocessor -> Preprocessor Definition` as `__BASE_FILE__="%(Filename)%(Extension)"`. Or you can add the macro at compile time as option to your compiler using the macro option. 
e.g. in gcc 

```bash
gcc -D__BASE_FILE__=\"/the/path/to/yout/testfile.c\" testfile.c -I.
```

Alternatively the test cases should be manually registered in the main method, you will have to disable cester main function by defining the macro CESTER_NO_MAIN. 

```c
#include <exotic/cester.h>

#define CESTER_NO_MAIN

CESTER_TEST(test1, test_instance,
	cester_assert_equal(NULL, NULL);
)

CESTER_BODY(
int main(int argc, char** argv) {
	CESTER_REGISTER_TEST(test1);
	return CESTER_RUN_ALL_TESTS(argc, argv);
}
)
```

Visit this [link](https://exoticlibraries.github.io/libcester/docs/manual_test_registration.html) for more detail on manual test registration.

## How it works

The base file which is the file that contains the tests is included more than twice during the macro expansion process to define and register the test cases. The working principle is best explained by a thought experiment. 

> Imagine a source file including a header file. Then imagine the header file including the source file that included it. Now imagine doing that three times in a row within the same header file. Proceed to imagine redefining all of the identifiers each time. Finally imagine doing all of that with preprocessor directives. What you ended up with is CHEAT - Sampsa Kiiskinen

Yes the project uses the same approach used by the [cheat](http://users.jyu.fi/~sapekiis/cheat/index.html) project. The project makes a very tricky use of the C preprocessor directive to achieve test cases registration so the developer can concentrate on writing the test only while cester manages the test registration, execution and analysis.

## Contributing

If you have any issue or you want to request a feature you can open a request [here](https://github.com/exoticlibraries/libcester/issues/new/choose) anytime and if you made some changes that should be added to the main project send in a [pull request](https://github.com/Thecarisma/Cronux/compare). 

## Useful Links

 - [ANSI C](https://en.wikipedia.org/wiki/ANSI_C)
 - [CHEAT](http://users.jyu.fi/~sapekiis/cheat/index.html)
 - [Exotic Libraries](https://exoticlibraries.github.io/)
 - [Author](https://thecarisma.github.io/)

## License

GNU General Public License v3.0 Copyright (c) 2020, Adewale Azeez 

