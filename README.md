
![](https://github.com/exoticlibraries/libcester/raw/master/docs/cester.png)

# libcester

A header only unit testing framework for C.

___

cester is a header only automated testing framework for the C programming language, it requires no dependency and can be downloaded and used in a project immediately. cester allows shared instance `test_instance` in which each test cases can use to share data and access the command line arguments. If the project is downloaded using one of the install script it will be located in `<exotic/cester.h>` of the compiler include directoy. 

```c
//!gcc {0} -I. -o test; ./test
#include <exotic/cester.h>

CESTER_BEFORE_ALL(test_instance,
    test_instance->arg = "Hello World";
)

CESTER_TEST(check_shared_arg, test_instance,
    cester_assert_equal(test_instance->arg, "Hello World");
    cester_assert_not_equal(2, 1);
)
```
___

## Table of content
- [Portability](#portability)
- [Installation](#installation)
	- [Install](#install)
		- [Windows](#windows)
		- [Linux](#linux)
		- [Download and include](#download-and-include)
	- [Uninstall](#uninstall)
- [Usage](#usage)
- [How it works](#how-it-works)
- [Contributing](#contributing)
- [Useful Links](#useful-links)
- [License](#license)

## Portability

cester follows the original C language specification, ISO/IEC 9899:1990, and the first POSIX specification, IEEE Std 1003.1-1988, to the letter. The project includes only `stdlib.h`, `time.h`, `stdio.h` and `windows.h` on WIndows to colorful output. Some function are manually implemented in the library to ensure it works in embedded system and even in the most isolated system. 

The project is designed for C, but also works with C++ but be ready for waves of warnings.

## Installation

### Windows

### Linux

### Download and include

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

