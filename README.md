
![](https://github.com/exoticlibraries/libcester/raw/main/docs/libcester.png)

# libcester

A robust header only unit testing framework for C programming language. Support function mocking, memory leak detection, crash report. 

cester is a header only automated testing framework for the C programming language, it requires no dependency and can be downloaded and used in a project immediately. Works on various platorms including embedded systems and compatible with various compilers. Allows shared instance `TestInstance` object in which each test cases can use to share data and access the command line arguments. 

```c
#include <exotic/cester.h>

CESTER_TEST(test_one, inst,
    cester_assert_equal(NULL, ((void*)0));    
)
```

The test results can be outputed as various format JunitXML, Test Anything Protocol, Test Anything Protocol Version 13 and text. Visit [https://exoticlibraries.github.io/libcester/docs/](https://exoticlibraries.github.io/libcester/docs/) for documentation and tutorials. 
___

## Table of content
- [Features](#features)
- [Standards Compliance and Portability](#standards-compliance-and-portability)
- [Installation](#installation)
    - [Install](#install)
        - [Windows](#windows)
        - [Unix, Linux, Mac](#unix-linux-mac)
        - [Other platforms](#other-platforms)
- [Documentation](#documentation)
- [Usage](#usage)
    - [Writing and Running test](#writing-test)
    - [Cester options](#cester-options)
    - [Macros](#macros)
- [Mocking](#mocking)
- [FAQ](#faq)
    - [No test case detected](#no-test-case-detected)
- [How it works](#how-it-works)
- [Contributing](#contributing)
- [References](#references)
- [License](#license)

## Features

- Single header only, just download cester.h and you are good to go.
- Automatic test detection, registration and execution, just write your test and run.
- Isolated unit testing, each test case is executed in it own process so a crashed test can be properly reported.
- Very portable, compatiple with ANSI C and C++98 without any trade off in functionalities.
- A test instance object to share data between multiple test case to avoid the global scope pollution.
- Provides simple API for mocking functions with gcc compiler options.
- Generate report in various output formats, junitxml, text, tap, tapV13.
- Does not produce any warnings even with strict warning options turned on.
- Test for failures such as segfault, memory leak, premature termination e.t.c.
- Rich collection of assertions for various type with proper reporting.
- Modular, excluded un-used features from your test, [selective_compilation](https://exoticlibraries.github.io/libcester/docs/selective_compilation.html).
- No extra dependencies needed, once you have the C or C++ standard library available.
- Support test fixture to setup and tear down resources used by the test cases.
- Detail docuentation with examples and API references.

## Standards Compliance and Portability

The project is compliant with the original C language specification ISO/IEC 9899:1990 and the first POSIX specification IEEE Std 1003.1-1988 which ensures the project compatibility in various environments. It also makes use of features in the newer revisions ISO/IEC 9899:1999 and IEEE Std 1003.1-2001 whenever possible. 

Even though the project is designed for C, but also works with C++ as it is compatible with C++98 Standard (ISO/IEC 14882:1998), C++03 Standard (ISO/IEC 14882:2003) and C++11 Standard (ISO/IEC 14882:2011).

The project can be used with any C or C++ compiler. There are optional macros and options that can be used to attain the desired output in the case of undesired results.

## Installation

If you install the library file `cester.h` using any of the commands below, it can be included in your test like `<exotic/cester.h>`.

### Windows

Install the library using powershell. It auto detect your insalled C and C++ compilers include directory and install libcester into the include folder. Execute the command in powershell as admin.

```powershell
& $([scriptblock]::Create((New-Object Net.WebClient).DownloadString("https://exoticlibraries.github.io/magic/install.ps1"))) libcester
```

### Unix, Linux, Mac

Use the remote installation script to install libcester with bash. If the command is executes with super user priviledge (sudo) it will be installed in the folder /usr/include else it will be installed in the folder /usr/local/include. Or you can specify where to install it using the option `--installfolder=./` 

```bash
bash <(curl -s https://exoticlibraries.github.io/magic/install.sh) libcester
```

### Other platforms

You can simply download the header file `cester.h` from the repo into your project source folder and include it in your project. Download the file from [here](https://github.com/exoticlibraries/libcester/releases). The you can include it in your test relatively like `#include "cester.h"`.

## Documentation

The [documentation](https://exoticlibraries.github.io/libcester/docs/) provides several examples, tutorials, and detailed guides for using the library. While [reference](https://exoticlibraries.github.io/libcester/reference/) provides a low-level overview of all the implemented APIs in the library. 

Some of the documentation pages are listed below:

 - [Assertion Macros](https://exoticlibraries.github.io/libcester/docs/assertions.html)
 - [Mocking](https://exoticlibraries.github.io/libcester/docs/mocking.html)
 - [Helper Macros](https://exoticlibraries.github.io/libcester/docs/macros.html)
 - [Manual Tests Registration](https://exoticlibraries.github.io/libcester/docs/manual_test_registration.html)
 - [Cester Options](https://exoticlibraries.github.io/libcester/docs/options.html)
 - [Test Fixtures](https://exoticlibraries.github.io/libcester/docs/fixtures.html)
 - [Output Formats](https://exoticlibraries.github.io/libcester/docs/output_formats.html)
 - [Testing for failures](https://exoticlibraries.github.io/libcester/docs/test_for_failure.html)
 - [Testing Output Streams](https://exoticlibraries.github.io/libcester/docs/testing_stream.html)
 - [How it works](https://exoticlibraries.github.io/libcester/how_it_works/index.html)

 For some know unfixed issues see the page [known_issues](file:///C:/Users/thecarisma/Documents/OPEN_SOURCE/EXOTIC_LIBRARIES/libcester/docs/build/html/docs/known_issues.html).

## Usage

### Writing and Running test

The macro CESTER_TEST is used to create a test case, the first parameter is the test case name the second parameter is the test instance object which is used to share data between the test cases and also has the command line arguments object and count, the last parameter is the body of the test case. The following example defines a test case that chack if `NULL` is the same as `((void*)0)`

```c
//test.c
#include <exotic/cester.h>

CESTER_TEST(test_one, inst,
    cester_assert_equal(NULL, ((void*)0));    
)

CESTER_TEST(test_two, inst,
    cester_assert_ptr_equal(inst, NULL);    
)
```

cester will automatically detect and register the test cases if the macro `__BASE_FILE__` is predefined by the compiler. If no test is detected see the [FAQ](#faq) below on ways to make cester aware of the test case. 

The test above can be compiled and run like below. **Do not forget to add the option -I. for gcc so it can find the `__BASE_FILE__`**.

```bash
gcc test.c -I.-o test
./test

  + (0.00s) test one
  - (0.00s) test two

AssertionError crash_test.c:10: in 'test_two' => expected '0761C50', received '0000000'

Ran 2 test(s) in 0.01 Seconds
Synthesis: FAILURE Tests: 2 | Passing: 1 | Failing: 1
```

### Macros

Many predefined helper macros are present in cester, all cester macros begins with CESTER_ and cester_. The detail documentation of the macros is at [Helper Macros](https://exoticlibraries.github.io/libcester/docs/macros.html).

## Mocking

cester supports mocking function. The mock feature currently works on GCC compiler because 
of the use of the `--wrap` option which is not supported on MAC OSX and might not be available in other compilers. The two macros [CESTER_MOCK_SIMPLE_FUNCTION](https://exoticlibraries.github.io/libcester/docs/macros.html#cester-mock-simple-function) and [CESTER_MOCK_FUNCTION](https://exoticlibraries.github.io/libcester/docs/macros.html#cester-mock-function) are used for function mocking.

The following test mocks a funtion that accept no parameter and return a value:

*originals.c*

```c
#ifndef ORIGINALS
#define ORIGINALS

int multiply_by() {
    return 2;
}

int multiply_a_number(int a) {
    return a * multiply_by() ;
}
#endif
```

*test_mock.c*

```c
#include <exotic/cester.h>
#include "originals.c"

CESTER_MOCK_FUNCTION(multiply_by(), int, {
    return 5;
})

CESTER_TEST(check_mocked_function, test_instance,
    cester_assert_equal(multiply_a_number(2), 10);
)
```

Compile the test file *test_mock.c* with the --wrap option e.g. in the example above the function `multiply_by` was mocked so the option *-Wl,--wrap=multiply_by* is supplied during 
compilation. 

```bash
gcc test_mock.c -I. -Wl,--wrap=multiply_by -o test_mock
./test_mock

+ (0.00s) check mocked function

Ran 1 test(s) in 0.00 Seconds
Synthesis: SUCCESS Tests: 1 | Passing: 1 | Failing: 0
```

More detailed explanation on mocking function can be seen at [https://exoticlibraries.github.io/libcester/docs/mocking.html](https://exoticlibraries.github.io/libcester/docs/mocking.html).

### Cester options

cester accepts various options to tune it functionalities. Any command line parameter that starts with --cester- is treated as cester option otherwise it is ignored. All the available options can be viewed [here](https://exoticlibraries.github.io/libcester/docs/options.html).

The following options performs important task:

- **--cester-noisolation**: instruct cester to run all the test in one single process. With this option signal will be used for crash reporting but if the test is compiled with the macro `CESTER_NO_SIGNAL` defined, cester will not be able to recover from critical crash therefore if a test case segfault the tests will terminate immediately.

 - **--cester-output**: Change the format in which the outpout is generated. Various format is supported, all the supported format can be viewed [here](https://exoticlibraries.github.io/libcester/docs/output_formats.html). E.g. to print the output in JunitXML format you supply the option `--cester-output=junitxml`.

 - **--cester-nomemtest**: instruct cester to skip memory leak detection and test. Alternatively the test can be compiled with the macro `CESTER_NO_MEM_TEST` defined at the beginning of the source file.

 - **--cester-verbose**: printf as much output as possible including passed test expression, output to the stdout from within the test case. This option combined with **--cester-minimal** prints out the output in a very sane format.

 - **--cester-help**: to view all the options accepted by cester.

## FAQ

### No test detected

If no test was ran or your test cases were not detected, in most cases it because your compiler did not define the `__BASE_FILE__` macro. If you are using the Visual studio IDE you should define the macro in 
`Properties -> C/C++ -> Preprocessor -> Preprocessor Definition` as `__BASE_FILE__="%(Filename)%(Extension)"`. Or you can add the macro at compile time as option to your compiler using the macro option. 
e.g. in gcc 

```bash
gcc -D__BASE_FILE__=\"/the/path/to/your/testfile.c\" testfile.c -I.
```

Setting for Visual C compiler

```powershell
cl /D__BASE_FILE__=\"/the/path/to/your/testfile.c\" testfile.c
```

You can also define the `__BASE_FILE__` at the beginning of your test file with the absolute 
path to the test file. E.g for the test file test.c:

```c
#define __BASE_FILE__ "/path/to/test.c"
#include <exotic/cester.h>

CESTER_TEST(test1, test_instance,
    cester_assert_equal(NULL, NULL);
)
```

Alternatively the test cases should be manually registered in the main method, you will have to disable cester main function by defining the macro CESTER_NO_MAIN. 

```c
#define CESTER_NO_MAIN
#include <exotic/cester.h>

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

The project uses the same approach used by the [cheat](https://github.com/Tuplanolla/cheat) project. It makes a very tricky use of the C preprocessor directive to achieve test cases registration so the developer can concentrate on writing the test only while cester manages the test registration, execution and analysis.

See the pages at [how it works](https://exoticlibraries.github.io/libcester/how_it_works/index.html) for more explanation.

## Contributing

If you have any issue or you want to request a feature you can open a request [here](https://github.com/exoticlibraries/libcester/issues/new/choose) anytime and if you made some changes that should be added to the main project send in a [pull request](https://github.com/exoticlibraries/libcester/compare). 

## References

 - [ANSI C](https://en.wikipedia.org/wiki/ANSI_C)
 - [CHEAT](https://github.com/Tuplanolla/cheat)
 - [Exotic Libraries](https://exoticlibraries.github.io/)
 - [Author](https://thecarisma.github.io/)

## License

MIT License Copyright (c) 2020, Adewale Azeez 

