
/**
    \copyright MIT License Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 10 April 2020
    \file cester.h

    Cester is a header only unit testing framework for C. The header 
    file can be downloaded and placed in a project folder or can be 
    used as part of libopen library by including it in the projects 
    like `<libopen/cester.h>`. 
    
    A single test file is considered a test suite in cester, a single 
    test file should contain related tests functions only. 
*/

#ifndef LIBOPEN_CESTER_H
#define LIBOPEN_CESTER_H

/*
    BEFORE YOU SUGGEST ANY EDIT PLEASE TRY TO 
    UNDERSTAND THIS CODE VERY WELL. 
*/

#ifdef __cplusplus
extern "C" {
#endif

/** 
    The inline keyword to optimize the function. In 
    C89 and C90 the inline keyword semantic is 
    different from current C standard semantic hence 
    for compilation targeting C89 or C99 the inline 
    keyword is ommited.
*/
#ifdef __STDC_VERSION__
    #define __CESTER_STDC_VERSION__ __STDC_VERSION__
#else
    #ifdef __cplusplus
        #if __cplusplus > 199711L
            #define __CESTER_STDC_VERSION__ __cplusplus
        #endif
    #endif
#endif
#ifndef __CESTER_STDC_VERSION__
    #define __CESTER_INLINE__ 
    #define __CESTER_LONG_LONG__ long
    #define __CESTER_LONG_LONG_FORMAT__ "%ld"
    #ifdef __FUNCTION__ 
        #define __CESTER_FUNCTION__ __FUNCTION__
    #else
        #define __CESTER_FUNCTION__ "<unknown>"
    #endif
    #define CESTER_NULL 0L
#else 
    #define __CESTER_INLINE__ inline
    #define __CESTER_LONG_LONG__ long long
    #define __CESTER_LONG_LONG_FORMAT__ "%lld"
    #define __CESTER_FUNCTION__ __func__
    #define CESTER_NULL NULL
#endif

#ifdef __cplusplus
#if defined(_WIN32) && !defined(CESTER_EXCLUDE_WINDOWS_H)
    #define __CESTER_CAST_CHAR_ARRAY__ (unsigned)
#else
    #define __CESTER_CAST_CHAR_ARRAY__ (char*)
#endif
#else
    #define __CESTER_CAST_CHAR_ARRAY__
#endif

#if defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
#define _POSIX_SOURCE
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#endif

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef CESTER_NO_SIGNAL
#include <signal.h>
#include <setjmp.h>
jmp_buf buf;
#endif

#ifndef __BASE_FILE__
#ifdef _MSC_VER
    #pragma message("__BASE_FILE__ not defined. Define the __BASE_FILE__ directive in Properties -> C/C++ -> Preprocessor -> Preprocessor Definition as __BASE_FILE__=\"%(Filename)%(Extension)\" or register your test cases manually.")
#else
    #pragma message("__BASE_FILE__ not defined. Define __BASE_FILE__ during compilation. -D__BASE_FILE__=\"/the/path/to/yout/testfile.c\" or register your test cases manually.")
#endif
#endif

#ifdef _WIN32
#ifndef CESTER_EXCLUDE_WINDOWS_H
#ifndef NOMINMAX
    #define NOMINMAX
#endif
#include <windows.h>
#endif
#include <direct.h>

#define mkdir(x,y) _mkdir(x)
#ifndef stat
#define stat __stat64
#endif
/*
**  Windows 
**  Support Windows XP 
**  To avoid error message : procedure entry point **  InitializeConditionVariable could not be located **  in Kernel32.dll 
*/
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x502
#define EXOTICTYPES_WINDLLEXPORT 1
/* Linux */
#else
#define EXOTICTYPES_WINDLLEXPORT 0
#endif
#ifndef __cplusplus
    #if EXOTICTYPES_WINDLLEXPORT
        #define EXOTIC_API __declspec(dllexport) /**< the platform is windows use windows export keyword __declspec(dllexport) */ 
    #else
        #define EXOTIC_API extern                /**< Keyword to export the functions to allow ussage dynamically. NOT USED. IGNORED  */
    #endif
#else
    #define EXOTIC_API
#endif

#if defined(_WIN32) && !defined(CESTER_EXCLUDE_WINDOWS_H)

#define CESTER_RESET_TERMINAL           15                                                /**< reset the terminal color //Nothing     */
#define CESTER_BOLD                     15                                                /**< bold text                //Nothing     */
#define CESTER_FOREGROUND_BLACK         8                                                 /**< gray terminal foreground color         */
#define CESTER_FOREGROUND_RED           4                                                 /**< red terminal foreground color          */
#define CESTER_FOREGROUND_GREEN         2                                                 /**< green foreground color                 */
#define CESTER_FOREGROUND_YELLOW        6                                                 /**< yellow terminal foreground color       */
#define CESTER_FOREGROUND_BLUE          3                                                 /**< blue terminal foreground color         */
#define CESTER_FOREGROUND_MAGENTA       5                                                 /**< magenta terminal foreground color      */
#define CESTER_FOREGROUND_CYAN          11                                                /**< cyan terminal foreground color         */
#define CESTER_FOREGROUND_WHITE         15                                                /**< white terminal foreground color        */
#define CESTER_FOREGROUND_GRAY          8                                                 /**< gray terminal foreground color         */
#define CESTER_BACKGROUND_BLACK         0                                                 /**< black terminal background color        */
#define CESTER_BACKGROUND_RED           64                                                /**< red terminal background color          */
#define CESTER_BACKGROUND_GREEN         39                                                /**< green terminal background color        */
#define CESTER_BACKGROUND_YELLOW        96                                                /**< yellow terminal background color       */
#define CESTER_BACKGROUND_BLUE          48                                                /**< blue terminal background color         */
#define CESTER_BACKGROUND_MAGENTA       87                                                /**< magenta terminal background color      */
#define CESTER_BACKGROUND_CYAN          176                                               /**< cyan terminal background color         */
#define CESTER_BACKGROUND_GRAY          0                                                 /**< gray terminal background color         */
#define CESTER_BACKGROUND_WHITE         10                                                /**< gray terminal background color         */
#define CESTER_RESET_TERMINAL_ATTR()    SetConsoleTextAttribute(hConsole, default_color); /**< reset the terminal color               */

#else
    
#define CESTER_RESET_TERMINAL           "\x1B[0m"     /**< reset the terminal color           */
#define CESTER_BOLD                     "\x1B[1m"     /**< bold text                          */
#define CESTER_FOREGROUND_BLACK         "\x1B[30m"    /**< gray terminal foreground color     */
#define CESTER_FOREGROUND_RED           "\x1B[31m"    /**< red terminal foreground color      */
#define CESTER_FOREGROUND_GREEN         "\x1B[32m"    /**< green foreground color             */
#define CESTER_FOREGROUND_YELLOW        "\x1B[33m"    /**< yellow terminal foreground color   */
#define CESTER_FOREGROUND_BLUE          "\x1B[34m"    /**< blue terminal foreground color     */
#define CESTER_FOREGROUND_MAGENTA       "\x1B[35m"    /**< magenta terminal foreground color  */
#define CESTER_FOREGROUND_CYAN          "\x1B[36m"    /**< cyan terminal foreground color     */
#define CESTER_FOREGROUND_WHITE         "\x1B[37m"    /**< white terminal foreground color    */
#define CESTER_FOREGROUND_GRAY          "\x1B[90m"    /**< gray terminal foreground color     */
#define CESTER_BACKGROUND_BLACK         "\x1B[40m"    /**< black terminal background color    */
#define CESTER_BACKGROUND_RED           "\x1B[41m"    /**< red terminal background color      */
#define CESTER_BACKGROUND_GREEN         "\x1B[42m"    /**< green terminal background color    */
#define CESTER_BACKGROUND_YELLOW        "\x1B[43m"    /**< yellow terminal background color   */
#define CESTER_BACKGROUND_BLUE          "\x1B[44m"    /**< blue terminal background color     */
#define CESTER_BACKGROUND_MAGENTA       "\x1B[45m"    /**< magenta terminal background color  */
#define CESTER_BACKGROUND_CYAN          "\x1B[46m"    /**< cyan terminal background color     */
#define CESTER_BACKGROUND_GRAY          "\x1B[100m"   /**< gray terminal background color     */
#define CESTER_BACKGROUND_WHITE         "\x1B[47m"    /**< gray terminal background color     */
#define CESTER_RESET_TERMINAL_ATTR()    ;             /**< reset the terminal color           */

#endif

/**
    Cester current version
*/
#define CESTER_VERSION "0.4"

/**
    Cester current version
*/
#define CESTER_VERSION_NUM 0.4

/**
    Cester License
*/
#define CESTER_LICENSE "MIT License"

/**
    Cester Authors
*/
#define CESTER_AUTHOR "Adewale Azeez and other contributors"

/**
    The hash # symbol for macro directive
*/
#define CESTER_HASH_SIGN #

/**
    Concat two items including C macro directives.
*/
#define CESTER_CONCAT(x, y) x y

/**
    The type of caparison to perform on two values.

    This is introduce to resolve the bug https://github.com/exoticlibraries/libcester/issues/30
*/
enum cester_assertion_caparator {
    CESTER_COMPARATOR_EQUAL,                   /**< the comparisson operator is '==' */
    CESTER_COMPARATOR_NOT_EQUAL,               /**< the comparisson operator is '!=' */
    CESTER_COMPARATOR_GREATER_THAN,            /**< the comparisson operator is '>' */
    CESTER_COMPARATOR_GREATER_THAN_OR_EQUAL,   /**< the comparisson operator is '>=' */
    CESTER_COMPARATOR_LESSER_THAN,             /**< the comparisson operator is '<' */
    CESTER_COMPARATOR_LESSER_THAN_OR_EQUAL     /**< the comparisson operator is '<=' */  
};

/**
    The execution status of a test case that indicates 
    whether a test passes of fails. And also enable the 
    detection of the reason if a test fail.
*/
enum cester_test_status {
    CESTER_RESULT_SUCCESS,            /**< the test case passed */
    CESTER_RESULT_FAILURE,            /**< the test case failes dues to various reason mostly AssertionError */
    CESTER_RESULT_TERMINATED,         /**< in isolated test, the test case was termiated by a user or another program */
    CESTER_RESULT_SEGFAULT,           /**< the test case crahses or causes segmentation fault */
    CESTER_RESULT_UNRELEASED_STREAM,  /**< the test case has unreleased streams */
#ifndef CESTER_NO_MEM_TEST
    CESTER_RESULT_MEMORY_LEAK,         /**< the test case passes or fails but failed to free allocated memory */
#endif
    CESTER_RESULT_TIMED_OUT,          /**< cester terminated the test case because it running for too long */
    CESTER_RESULT_UNKNOWN             /**< the test case was never ran */
};

typedef enum cester_test_type {
    CESTER_NORMAL_TEST,             /**< normal test in global or test suite. For internal use only.                                              */
    CESTER_NORMAL_TODO_TEST,        /**< test to be implemented in future. For internal use only.                                                 */
    CESTER_NORMAL_SKIP_TEST,        /**< test to be skipped. For internal use only.                                                               */
    CESTER_BEFORE_ALL_TEST,         /**< test to run before all normal tests in global or test suite. For internal use only.                      */
    CESTER_BEFORE_EACH_TEST,        /**< test to run before each normal tests in global or test suite. For internal use only.                     */
    CESTER_AFTER_ALL_TEST,          /**< test to run after all normal tests in global or test suite. For internal use only.                       */
    CESTER_AFTER_EACH_TEST,         /**< test to run after each normal tests in global or test suite. For internal use only.                      */
    CESTER_OPTIONS_FUNCTION,        /**< the cester function for test, this wil be excuted before running the tests. For internal use only.       */
    CESTER_TEST_FILE_COMMENT,       /**< The function that holds the text defined in the CESTER_COMMENT macro. For internal use only.              */
    CESTER_TESTS_TERMINATOR         /**< the last value in the test cases to terminates the tests. For internal use only.                         */
} TestType;

/**
    The structure that manages the stream that has been captured 
    by cester. It keeps record of the original stream and also of 
    the stream that replaces the original, this way when a stream is 
    to be released by cester it can simly set the original stream 
    to it original state with no consequences and the extrac stream 
    can be properlly freed.
*/
typedef struct captured_stream {
    unsigned line_num;                      /**< the line number where the stream was captured. For internal use only. */
    char *function_name;                    /**< The function name (test case) where the stream was catured. For internal use only.*/
    char *original_stream_ptr_str;          /**< The captured stream pointer address as string. For internal use only.*/
    char *replaced_stream_ptr_str;          /**< The stream to replace the captured stream pointer address as string. For internal use only.*/
    char *stream_buffer;                    /**< The stream content. This is needed so we can peoperly free allocated memory. For internal use only.*/
    char *replaced_stream_file_path;  /**< The file path to the temporary file that replaces the stream. For internal use only.*/
    FILE original_stream;                   /**< The actual address of the captured stream. For internal use only.*/
    FILE *original_stream_handle;           /**< The actual variable of the captured stream. For internal use only.*/
    FILE *replaced_stream_handle;           /**< The opened file handle that replaces the captured stream. For internal use only.*/
} CapturedStream;

/**
    The test instance that contains the command line argument 
    length and values, with void* pointer that can be used to 
    share data between unit tests.
*/
typedef struct test_instance {
    unsigned argc;                   /**< the length of the command line arg                            */
    char **argv;                   /**< the command line arguments                                    */
    void *arg;                     /**< pointer to an object that can be passed between unit tests    */
} TestInstance;

/**
    The function signature for each test case and the before after functions. 
    It accepts the ::test_instance as it only argument. 
*/
typedef void (*cester_test)(TestInstance*);

/**
    The function signature for function to execute before and after each test 
    cases. It accepts the ::test_instance, char* and unsigned as parameters. 
*/
typedef void (*cester_before_after_each)(TestInstance*, char * const, unsigned);

/**
    A void function signature with no return type and no parameters.
*/
typedef void (*cester_void)();

typedef struct test_case {
    unsigned execution_status;                      /**< the test execution result status. For internal use only. */
    unsigned line_num;                              /**< the line number where the test case is created. For internal use only. */
    enum cester_test_status expected_result;        /**< The expected result for the test case. For internal use only. */
#ifndef CESTER_NO_TIME
    double start_tic;                               /**< the time taken for the test case to complete. For internal use only. */
    double execution_time;                          /**< the time taken for the test case to complete. For internal use only. */
#endif
    char* execution_output;                         /**< the test execution output in string. For internal use only. */
    char *name;                                     /**< the test function name. For internal use only. */
    cester_test test_function;                      /**< the function that enclosed the tests. For internal use only. */
    cester_before_after_each test_ba_function;      /**< the function that enclosed the tests. For internal use only. */
    cester_void test_void_function;                 /**< the function that enclosed the tests. For internal use only. */
    TestType test_type;                             /**< the type of the test function. For internal use only. */
} TestCase; 

#ifndef CESTER_NO_MEM_TEST

typedef struct allocated_memory {
    unsigned line_num;               /**< the line number where the memory was allocated. For internal use only.   */
    size_t allocated_bytes;          /**< the number of allocated bytes. For internal use only.                    */
    unsigned function_name_allocated;  /**< check whether the vallue was set using malloc. For internal use only.                    */
    char* address;                   /**< the allocated pointer address. For internal use only.                    */
    char* function_name;       /**< the function where the memory is allocated in. For internal use only.    */
    const char* file_name;           /**< the file name where the memory is allocated. For internal use only.      */
} AllocatedMemory;

#endif

/**
    The initial amount of item the ::CesterArray can accept the first 
    time it initialized.
*/
#define CESTER_ARRAY_INITIAL_CAPACITY 30

/**
    The maximum number of item the ::CesterArray can contain, in case of 
    the Memory manager array reaching this max capacity continous mem 
    test will be disabled.
*/
#define CESTER_ARRAY_MAX_CAPACITY ((size_t) - 5)

typedef struct cester_array_struct {
    size_t size;                        /**< the size of the item in the array                         */
    size_t capacity;                    /**< the number of item the array can contain before expanding */
    void** buffer;                      /**< pointer to the pointers of items added to the array       */
} CesterArray;


#define CESTER_ARRAY_FOREACH(w,x,y,z) for (x = 0; x < w->size; ++x) {\
                                          void* y = w->buffer[x];\
                                          z\
                                      }

/**
    This structure manages the _BEFORE_ and _AFTER_ functions 
    for the test main ::test_instance. And also accounts for all the 
    registered test cases. This is for Cester internal use only.
*/
typedef struct super_test_instance {
    unsigned no_color;                                    /**< Do not print to the console with color if one. For internal use only. */
    unsigned total_tests_count;                           /**< the total number of tests to run, assert, eval e.t.c. To use in your code call CESTER_TOTAL_TESTS_COUNT */
    unsigned total_tests_ran;                             /**< the total number of tests that was run e.t.c. To use in your code call CESTER_TOTAL_TESTS_RAN */
    unsigned total_failed_tests_count;                    /**< the total number of tests that failed. To use in your code call CESTER_TOTAL_FAILED_TESTS_COUNT */
    unsigned total_passed_tests_count;                    /**< the total number of tests that passed. To use in your code call CESTER_TOTAL_FAILED_TESTS_COUNT */
    unsigned total_test_errors_count;                     /**< the total number of errors that occurs. To use in your code call CESTER_TOTAL_TEST_ERRORS_COUNT */
    unsigned verbose_level;                               /**< the level of cester verbosity for how much information is printed in the terminal */
    unsigned print_error_only;                            /**< if false or 0 prints all t assertion evaluation result, default is 1/true */
    unsigned print_version;                               /**< prints cester version before running tests */
    unsigned selected_test_cases_size;                    /**< the number of selected test casses from command line. For internal use only. */
    unsigned selected_test_cases_found;                   /**< the number of selected test casses from command line that is found in the test file. For internal use only. */
    unsigned single_output_only;                          /**< display the output for a single test only no summary and syntesis. For internal use only. */
    unsigned mem_test_active;                             /**< Enable or disable memory test at runtime. Enabled by default. For internal use only. */
    unsigned current_execution_status;                    /**< the current test case status. This is used when the test cases run on a single process. For internal use only. */
    unsigned isolate_tests;                               /**< Isolate each test case to run in different process to prevent a crashing test case from crahsing others. For internal use only. */
    unsigned skipped_test_count;                          /**< The number of test cases to be skipped. For internal use only. */
    unsigned todo_tests_count;                            /**< The number of test cases that would be implemented in future. For internal use only. */
    unsigned format_test_name;                            /**< Format the test name for fine output e.g. 'test_file_exit' becomes 'test file exist'. For internal use only. */
    unsigned report_success_regardless;                   /**< If the value is set to 1 the test will be mark as success even if it fails. For internal use only. */
    unsigned report_failure_regardless;                   /**< If the value is set to 1 the test will be mark as failure even if it passes. For internal use only. */
    TestType current_cester_function_type;                /**< The current cester funtion type, this enable cester to properly track memory allocation in non test case functions. For internal use only. */
#ifndef CESTER_NO_TIME
    double start_tic;                                   /**< The unix time when the tests starts. For internal use only. */
#endif
    char *main_execution_output;                        /**< The main test execution output in string. For internal use only. . */
    char *flattened_cmd_argv;                           /**< Flattened command line argument for sub process. For internal use only. */
    char *test_file_path;                               /**< The main test file full path. For internal use only. */
    char *output_format;                                /**< The output format to print the test result in. For internal use only. */
    char *output_stream_str;                            /**< The string value of the output stream pointer. For internal use only. */
    char *captured_streams_tmp_folder;                  /**< The folder to store temporary file for captured streams. For internal use only. */
    TestInstance *test_instance ;                       /**< The test instance for sharing datas. For internal use only. */
    FILE output_stream_address;                         /**< Output stream address. incase the output stream was captured in test it state can be reset. For internal use only. */
    FILE *output_stream;                                /**< Output stream to write message to, stdout by default. For internal use only. */
    char **selected_test_cases_names;                   /**< selected test cases from command line. For internal use only. e.g. --cester-test=Test2,Test1 */
    TestCase *current_test_case;                        /**< The currently running test case. For internal use only. */
    CesterArray *registered_test_cases;                 /**< all the manually registered test cases in the instance. For internal use only. */
    CesterArray *captured_streams;                        /**< all the file stream captured for testing by cester. For internal use only. */
#ifndef CESTER_NO_MEM_TEST
    CesterArray* mem_alloc_manager;                     /**< the array of allocated memory. For testing and detecting memory leaks. For internal use only. */
#endif
} SuperTestInstance;

/* CesterArray */
static __CESTER_INLINE__ unsigned cester_array_init(CesterArray**);
static __CESTER_INLINE__ unsigned cester_array_add(CesterArray*, void*);
static __CESTER_INLINE__ void* cester_array_remove_at(CesterArray*, size_t);
static __CESTER_INLINE__ void cester_array_destroy(CesterArray*);

static __CESTER_INLINE__ unsigned cester_run_all_test(unsigned, char **);
static __CESTER_INLINE__ void cester_str_value_after_first(char *, char, char**);


SuperTestInstance superTestInstance = { 
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    1,
    0,
    0,
    0,
    0,
    1,
    CESTER_RESULT_SUCCESS,
    1,
    0,
    0,
    1,
    0,
    0,
    CESTER_TESTS_TERMINATOR,
#ifndef CESTER_NO_TIME
    0.0,
#endif
    (char*)"",
    (char*)"",
#ifdef __BASE_FILE__
    (char*)__BASE_FILE__,
#else
    (char*)__FILE__,
#endif
    (char*)"text",
    (char*)"",
    (char*)"./build/libcester/captured_streams/",
    0,
    0,
    0,
    CESTER_NULL,
    0,
    0,
    0,
#ifndef CESTER_NO_MEM_TEST
    0
#endif
};

#ifdef _MSC_VER
#define cester_sprintf(x,y,z,a,b,c) sprintf_s(x, y, z, a, b, c);
#define cester_sprintf1(x,y,z,a) cester_sprintf(x,y,z,a,"","")
#define cester_sprintf2(x,y,z,a,b) cester_sprintf(x,y,z,a,b,"")
#define cester_sprintf3(x,y,z,a,b,c) cester_sprintf(x,y,z,a,b,c)
#else
#define cester_sprintf(x,y,z,a,b) sprintf(x, z, a, b);
#define cester_sprintf1(x,y,z,a) sprintf(x, z, a)
#define cester_sprintf2(x,y,z,a,b) sprintf(x, z, a, b)
#define cester_sprintf3(x,y,z,a,b,c) sprintf(x, z, a, b, c)
#endif


/* cester options */

/**
    Change the output stream used by cester to write data. The default is `stdout`. 
    E.g to change the output stream to a file. 
    
    \code{.c} 
    CESTER_CHANGE_STREAM(fopen("./test.txt", "w+"));
    \endcode
    
    The code above changes the stream to a file test.txt, all the output from 
    the test will be written in the file.
**/
#define CESTER_CHANGE_STREAM(x) { cester_ptr_to_str(&(superTestInstance.output_stream_str), x); superTestInstance.output_stream_address = *x; } (superTestInstance.output_stream = x)

/**
    Do not print to the output stream with color. This should be 
    used to prevent writing the color bytes into a file stream (in case).
    
    This option can also be set from the command line with `--cester-nocolor`
*/
#define CESTER_NOCOLOR() (superTestInstance.no_color = 1)

/**
    Change the option to print error only for the assertion. The default 
    value is true. Change the value to false to print all the results.
    
    The macro CESTER_VERBOSE also modify the value to false.
*/
#define CESTER_PRINT_ERROR_ONLY(x) (superTestInstance.print_error_only = x)

/**
    Print minimal info into the output stream. With this option set the 
    expression evaluated will not be printed in the result output. 
    
    This option can also be set from the command line with `--cester-minimal` 
    or `--cester-verbose-level=0`
*/
#define CESTER_MINIMAL() (superTestInstance.verbose_level = 0)

/**
    Print as much info as possible into the output stream. With this option set  
    both passed and failed expression evaluated will be printed in the result. 

    This macro also set the value of print_error_only only to false to display 
    output of all the assertions.
    
    This option can also be set from the command line with `--cester-verbose` or 
    `--cester-verbose-level=10`
*/
#define CESTER_VERBOSE() (superTestInstance.verbose_level = 10); (superTestInstance.print_error_only = 0)

/**
    Change the verbose level of the output, the higher the velue the more 
    the information printed into the terminal. 0 value means no output 
    apart from the testcase's and value 4 and above prints the full path 
    to the test file.
*/
#define CESTER_DEBUG_LEVEL(x) (superTestInstance.verbose_level = x)

/**
    Deprecated. Use CESTER_DEBUG_LEVEL
*/
#define CESTER_VERBOSE_LEVEL(x) (superTestInstance.verbose_level = x)

/**
    Print cester version before running any test. 
    
    This option can also be set from the command line with `--cester-printversion`
**/
#define CESTER_PRINT_VERSION() (superTestInstance.print_version = 1)

/**
    Display test for a single test case only, skip syntesis and summary.
    
    This option can also be set from the command line with `--cester-singleoutput`
**/
#define CESTER_SINGLE_OUPUT_ONLY() (superTestInstance.single_output_only = 1)

/**
    Do not isolate the tests, run each of the test cases in a single process. 
    The drawback is if a test case causes segfault or crash the entire test 
    crashes and no summary is displayed. No isolation causes a crash one 
    crash all scenerio.
    
    This option can also be set from the command line with `--cester-noisolation`
**/
#define CESTER_NO_ISOLATION() (superTestInstance.isolate_tests = 0)

/**
    Disable memory leak detection test.
    
    This option can also be set from the command line with `--cester-nomemtest`
**/
#define CESTER_NO_MEMTEST() (superTestInstance.mem_test_active = 0)

/**
    Enable memory allocation. The combination of CESTER_NO_MEMTEST() and 
    CESTER_DO_MEMTEST() is valid only in non isolated tests. 
    
    This togle combined with `CESTER_NO_MEMTEST()` can be used to selectively 
    test memory allocation in a test e.g. Calling CESTER_NO_MEMTEST() before 
    a test case will prevent memory test from the beginning of that function and 
    calling CESTER_DO_MEMTEST() at the end of the test case will ensure memory 
    allocation will be validated in all the other test case that follows.
**/
#define CESTER_DO_MEMTEST() (superTestInstance.mem_test_active = 1)

/**
    Change the output format to text
*/
#define CESTER_OUTPUT_TEXT() {if (superTestInstance.output_format != CESTER_NULL) { free(superTestInstance.output_format); }} superTestInstance.output_format = (char*) "text"

/**
    Change the output format to junitxml
*/
#define CESTER_OUTPUT_JUNITXML() {if (superTestInstance.output_format != CESTER_NULL) { free(superTestInstance.output_format); }} superTestInstance.output_format = (char*) "junitxml"

/**
    Change the output format to TAP (Test Anything Protocol)
*/
#define CESTER_OUTPUT_TAP() {if (superTestInstance.output_format != CESTER_NULL) { free(superTestInstance.output_format); }} superTestInstance.output_format = (char*) "tap"

/**
    Change the output format to TAP (Test Anything Protocol) Version 13
*/
#define CESTER_OUTPUT_TAPV13() {if (superTestInstance.output_format != CESTER_NULL) { free(superTestInstance.output_format); }} superTestInstance.output_format = (char*) "tapV13"

/**
    Format the test case name for output. E.g the test name 
    `modify_test_instance` becomes `modify test instance`. This 
    does not apply to junitxml as the test name remain the way it 
    declared in the test source.
*/
#define CESTER_FORMAT_TESTNAME() superTestInstance.format_test_name = 1;

/**
    Do not format the test case name, it remain the way it 
    declared in the test source.
*/
#define CESTER_DONT_FORMAT_TESTNAME() superTestInstance.format_test_name = 0;

/* test counts */

/**
    The total number of tests that is present in the test file.
*/
#define CESTER_TOTAL_TESTS_COUNT (superTestInstance.total_tests_count)

/**
    The total number of tests that was ran.
*/
#define CESTER_TOTAL_TESTS_RAN (superTestInstance.total_tests_ran)

/**
    The total number of tests that failed.
*/
#define CESTER_TOTAL_FAILED_TESTS_COUNT (superTestInstance.total_failed_tests_count)

/**
    The total number of errors that occur during the test.
    
    The errors is not tied to the test cases, the error 
    is tied to cester fixtures, environment error and error 
    that occur outside a test case. 
    
    Error that occur within a test case is reported for 
    that test case
*/
#define CESTER_TOTAL_TEST_ERRORS_COUNT (superTestInstance.total_test_errors_count)

/**
    The number of test that was skipped. 
    
    If the selected test_cases_size is 0 then no test was skipped else the 
    number of executed selected test cases minus the total number of test cases 
    is the number of test that was skipped.
*/
#define CESTER_TOTAL_TESTS_SKIPPED (superTestInstance.skipped_test_count)

/**
    The total number of tests that passed. CESTER_TOTAL_TESTS_COUNT - CESTER_TOTAL_FAILED_TESTS_COUNT
*/
#define CESTER_TOTAL_PASSED_TESTS_COUNT (superTestInstance.total_passed_tests_count)

/**
    The number of test that was marked as todo and skipped. 
    
    If the selected test_cases_size is 0 then no test was skipped else the 
    number of executed selected test cases minus the total number of test cases 
    is the number of test that was skipped.
*/
#define CESTER_TOTAL_TODO_TESTS (superTestInstance.todo_tests_count)

/**
    Run all the test registered in cester, the TestInstance* pointer 
    will be initalized with the pointer to the string arguments from 
    cli and the length of the arguments. The `void* arg` pointer in the 
    TestInstance* can be initalized in the *_BEFORE_* function to share 
    data between the unit tests.
*/
#define CESTER_RUN_ALL_TESTS(x,y) cester_run_all_test(x,y)

/**
    Always mark the test as success even if the test cases 
    failed or an error occur while running the test.
*/
#define CESTER_REPORT_SUCCESS_REGARDLESS() (superTestInstance.report_failure_regardless = 0); (superTestInstance.report_success_regardless = 1)

/**
    Always mark the test as failure even if the test cases 
    passes and no error occur.
*/
#define CESTER_REPORT_FAILURE_REGARDLESS() (superTestInstance.report_success_regardless = 0); (superTestInstance.report_failure_regardless = 1)

#if defined(_WIN32) && !defined(CESTER_EXCLUDE_WINDOWS_H)
    int default_color = CESTER_RESET_TERMINAL;
    HANDLE hConsole;
#else
    const char* default_color = CESTER_RESET_TERMINAL;
#endif

static void cester_copy_str(char **src_out, char **dest_out, int size)
{
    int index = 0;
    while (index < size) {
        (*dest_out)[index] = (*src_out)[index];
        index++;
    }
    (*dest_out)[index] = '\0';
}

static __CESTER_INLINE__ char *cester_extract_name(char const* const file_path) {
    unsigned i = 0, j = 0;
    char *file_name_only_actual;
    char *file_name_only = (char*) malloc (sizeof (char) * 200);
    while (file_path[i] != '\0') {
        if (file_path[i] == '\\' || file_path[i] == '/') {
            j = 0;
        } else {
            file_name_only[j] = file_path[i];
            j++;
        }
        ++i;
    }
    file_name_only_actual = (char*) malloc(j+1);
    cester_copy_str(&file_name_only, &file_name_only_actual, j);
    free(file_name_only);
    return file_name_only_actual;
}

static __CESTER_INLINE__ char *cester_extract_name_only(char const* const file_path) {
    unsigned i = 0;
    char *file_name = cester_extract_name(file_path);
    while (file_name[i] != '\0') {
        if (file_name[i] == '.') {
            file_name[i] = '\0';
            break;
        }
        ++i;
    }
    return file_name;
}

static __CESTER_INLINE__ void cester_concat_str(char **out, const char * extra);

/* For some wierd reasons sprintf clears old array first 
before concatenatng in old compiler e.g Turbo C. 
So we first convert int to str then concat it to str*/

static __CESTER_INLINE__ void cester_concat_char(char **out, char extra) {
    char tmp[5] ;
    cester_sprintf1(tmp, 5, "%c", extra);
    cester_concat_str(out, tmp);
}

static __CESTER_INLINE__ void cester_concat_int(char **out, int extra) {
    char tmp[30];
    cester_sprintf1(tmp, 30, "%d", extra);
    cester_concat_str(out, tmp);
}

static __CESTER_INLINE__ void cester_concat_sizet(char ** out, size_t extra) {
    char tmp[30];
    cester_sprintf1(tmp, 30, __CESTER_LONG_LONG_FORMAT__, (__CESTER_LONG_LONG__)extra);
    cester_concat_str(out, tmp);
}

static __CESTER_INLINE__ void cester_ptr_to_str(char **out, void* extra) {
    (*out) = (char*) malloc(sizeof(char) * 30 );
    cester_sprintf1((*out), (30), "%p", extra);
}

static __CESTER_INLINE__ unsigned cester_str_after_prefix(const char* arg, char* prefix, unsigned prefix_size, char** out) {
    unsigned i = 0, index = 0;
    char *value = (char*) malloc(sizeof (char) * 1000);
    
    while (1) {
        if (arg[i] == '\0') {
            if (i < prefix_size) {
                free(value);
                return 0;
            } else {
                break;
            }
        }
        if (i < prefix_size && arg[i] != prefix[i]) {
            free(value);
            return 0;
        }
        if (i >= prefix_size) {
            value[i-prefix_size] = arg[i];
        }
        ++i;
    }
    i = i-prefix_size;
    *out = (char*) malloc(i+1);
    cester_copy_str(&value, out, i);
    free(value);
    return 1;
}

static __CESTER_INLINE__ char* cester_str_replace(char* str, char old_char, char new_char) {
    char* tmp = (char*) malloc(strlen(str) + 1);
    unsigned index = 0;
    do {
        if (*str == old_char) {
            tmp[index] = new_char;
        } else {
            tmp[index] = *str;
        }
        ++str;
        index++;
    } while (*str != '\0');
    tmp[index] = '\0';
    
    return tmp;
}

static __CESTER_INLINE__ unsigned cester_string_equals(char* arg, char* arg1) {
    unsigned i = 0;
    if (arg == CESTER_NULL || arg1 == CESTER_NULL) {
        return 0;
    }
    while (1) {
        if (arg[i] == '\0' && arg1[i] == '\0') {
            break;
        }
        if (arg[i] != arg1[i]) {
            return 0;
        }
        ++i;
    }
    return 1;
}

static __CESTER_INLINE__ unsigned cester_string_contains(char* arg, char* arg1) {
    unsigned i = 0, index = 0;
    if (arg == CESTER_NULL || arg1 == CESTER_NULL) {
        return 0;
    }
    while (1) {
        if (arg[i] == '\0' || arg1[index] == '\0') {
            return 0;
        }
        if (arg[i] == arg1[index]) {
            i++;
            index++;
            while (arg[i] == arg1[index]) {
                if (arg[i] == '\0') {
                    break;
                }
                i++;
                index++;
            }
            if (arg1[index] == '\0') {
                return 1;
            }
            index = 0;
            continue;
        }
        ++i;
    }
    return 1;
}

static __CESTER_INLINE__ unsigned cester_string_starts_with(char* arg, char* arg1) {
    unsigned i = 0;
    while (1) {
        if (arg[i] == '\0' && arg1[i] == '\0') {
            break;
        }
        if (arg[i] != arg1[i]) {
            if (arg1[i] == '\0') {
                break;
            } else {
                return 0;
            }
        }
        ++i;
    }
    return 1;
}

static __CESTER_INLINE__ void unpack_selected_extra_args(char *arg, char ***out, unsigned *out_size) {
    unsigned i = 0;
    unsigned size = 0, current_index = 0;
    char* prefix = (char*) "test=";
    char **arr = (char**) malloc(30 * sizeof(char*));
    
    arr[size] = (char*) malloc(sizeof(char) * 1000);
    while (1) {
        if (arg[i] == '\0') {
            ++size;
            break;
        }
        if (i < 5 && arg[i] != prefix[i]) {
            break;
        }
        if (arg[i] == ',') {
            arr[size][current_index] = '\0';
            current_index = 0;
            ++size;
            arr[size] = (char*) malloc(sizeof(char) * 1000);
            goto continue_loop;
        }
        if (i >= 5) {
            arr[size][current_index] = arg[i];
            ++current_index;
        }
        continue_loop:
                      ++i;
    }
    if (current_index > 0) {
        arr[size-1][current_index] = '\0';
    }
    current_index = 0;
    (*out) = (char**) malloc(size * sizeof(char*));
    while (current_index < size) {
        (*out)[current_index] = arr[current_index];
        current_index++;
    }
    free(arr);

    *out_size = size;
}

static __CESTER_INLINE__ void cester_str_value_after_first(char *arg, char from, char** out) {
    unsigned i = 0, index = 0;
    unsigned found_char = 0;
    char *value = (char*) malloc(sizeof(char) * 200);
    while (1) {
        if (arg[i] == '\0') {
            break;
        }
        if (arg[i] == from) {
            found_char = 1;
            goto continue_loop;
        }
        if (found_char == 1) {
            value[index] = arg[i];
            ++index;
        }
        continue_loop:
                      ++i;
    }
    (*out) = (char*) malloc(index+1);
    cester_copy_str(&value, out, index);
    free(value);
}

static __CESTER_INLINE__ void cester_concat_str(char **out, const char * extra) {
    size_t concatted_pos = 0, index = 0;
    char *concatted = (char*) malloc(sizeof(char) * 80000 );
    if (extra == CESTER_NULL) {
        extra = (char *) "(null)";
    }
    while (1) {
        if ((*out) == CESTER_NULL || (*out)[index] == '\0') {
            break;
        }
        concatted[concatted_pos] = (*out)[index];
        concatted_pos++;
        index++;
    }
    index = 0;
    while (1) {
        if (extra[index] == '\0') {
            break;
        }
        concatted[concatted_pos] = extra[index];
        concatted_pos++;
        index++;
    }
    concatted[concatted_pos] = '\0';
    if (strlen(*out) > 0) {
        free(*out);
    }
    *out = (char*) malloc(concatted_pos+1);
    cester_copy_str(&concatted, out, concatted_pos);
    free(concatted);
}

static __CESTER_INLINE__ void cester_concat_ptr(char **out, void *ptr) {
    char *extra;
    cester_ptr_to_str(&extra, ptr);
    cester_concat_str(out, extra);
    free(extra);
}

static __CESTER_INLINE__ unsigned cester_is_validate_output_option(char *format_option) {
    return (cester_string_equals(format_option, (char*) "junitxml") ||  
	    cester_string_equals(format_option, (char*) "tap") ||
            cester_string_equals(format_option, (char*) "tapV13") ||  
            cester_string_equals(format_option, (char*) "text"));
}

#ifdef _WIN32
#define CESTER_SELECTCOLOR(x) (superTestInstance.no_color == 1 ? default_color : x)
#else 
#define CESTER_SELECTCOLOR(x) (superTestInstance.no_color == 1 ? "" : x)
#endif
#define CESTER_GET_RESULT_AGGR (superTestInstance.total_failed_tests_count == 0 ? "SUCCESS" : "FAILURE")
#define CESTER_GET_RESULT_AGGR_COLOR (superTestInstance.total_failed_tests_count == 0 ? (CESTER_FOREGROUND_GREEN) : (CESTER_FOREGROUND_RED))

#if defined(_WIN32) && !defined(CESTER_EXCLUDE_WINDOWS_H)
#define CESTER_DELEGATE_FPRINT_STR(x,y) SetConsoleTextAttribute(hConsole, CESTER_SELECTCOLOR(x)); fprintf(superTestInstance.output_stream, "%s", y)
#define CESTER_DELEGATE_FPRINT_PTR(x,y) SetConsoleTextAttribute(hConsole, CESTER_SELECTCOLOR(x)); fprintf(superTestInstance.output_stream, "%p", y)
#define CESTER_DELEGATE_FPRINT_INT(x,y) SetConsoleTextAttribute(hConsole, CESTER_SELECTCOLOR(x)); fprintf(superTestInstance.output_stream, "%d", y)
#define CESTER_DELEGATE_FPRINT_UINT(x,y) SetConsoleTextAttribute(hConsole, CESTER_SELECTCOLOR(x)); fprintf(superTestInstance.output_stream, "%u", y)
#ifndef CESTER_NO_TIME
#define CESTER_DELEGATE_FPRINT_DOUBLE(x,y) SetConsoleTextAttribute(hConsole, CESTER_SELECTCOLOR(x)); fprintf(superTestInstance.output_stream, "%f", y)
#define CESTER_DELEGATE_FPRINT_DOUBLE_2(x,y) SetConsoleTextAttribute(hConsole, CESTER_SELECTCOLOR(x)); fprintf(superTestInstance.output_stream, "%.2f", y)
#endif
#else
#define CESTER_DELEGATE_FPRINT_STR(x,y) fprintf(superTestInstance.output_stream, "%s%s%s", CESTER_SELECTCOLOR(x), y, CESTER_SELECTCOLOR(CESTER_RESET_TERMINAL))
#define CESTER_DELEGATE_FPRINT_PTR(x,y) fprintf(superTestInstance.output_stream, "%s%p%s", CESTER_SELECTCOLOR(x), y, CESTER_SELECTCOLOR(CESTER_RESET_TERMINAL))
#define CESTER_DELEGATE_FPRINT_INT(x,y) fprintf(superTestInstance.output_stream, "%s%d%s", CESTER_SELECTCOLOR(x), y, CESTER_SELECTCOLOR(CESTER_RESET_TERMINAL))
#define CESTER_DELEGATE_FPRINT_UINT(x,y) fprintf(superTestInstance.output_stream, "%s%u%s", CESTER_SELECTCOLOR(x), y, CESTER_SELECTCOLOR(CESTER_RESET_TERMINAL))
#ifndef CESTER_NO_TIME
#define CESTER_DELEGATE_FPRINT_DOUBLE(x,y) fprintf(superTestInstance.output_stream, "%s%f%s", CESTER_SELECTCOLOR(x), y, CESTER_SELECTCOLOR(CESTER_RESET_TERMINAL))
#define CESTER_DELEGATE_FPRINT_DOUBLE_2(x,y) fprintf(superTestInstance.output_stream, "%s%.2f%s", CESTER_SELECTCOLOR(x), y, CESTER_SELECTCOLOR(CESTER_RESET_TERMINAL))
#endif
#endif

static __CESTER_INLINE__ void cester_print_version() {
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "cester v");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), CESTER_VERSION);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " by ");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), CESTER_AUTHOR);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ".\n");
}

static __CESTER_INLINE__ void cester_print_help() {
    char *file_name = cester_extract_name_only(superTestInstance.test_file_path);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), CESTER_LICENSE);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\nUsage: ./");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), file_name);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " [-options] [args...]\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\nwhere options include:\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-verbose-level=[LEVEL]  change how much information is printed in the terminal\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-minimal                print minimal info into the output stream\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-verbose                print as much info as possible into the output stream\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-nocolor                do not print info with coloring\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-singleoutput           display cester version and exit\n");
#ifndef CESTER_NO_MEM_TEST
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-nomemtest              disable memory leak detection in the tests\n");
#endif
#ifdef __CESTER_STDC_VERSION__
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-noisolation            run all the test on a single process. Prevents recovery from crash.\n");
#endif
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-printversion           display cester version before running the tests\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-dontformatname         leave the test case name as declared in the source file in the output\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-test=Test1,...         run only selected tests. Seperate the test cases by comma\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-output=[FORMAT]        change the format in which the test results are printed\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-version                display cester version and exit\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-help                   display this help info version and exit\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "See https://exoticlibraries.github.io/libcester/docs/options.html for more details\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\nSupported output formats. [FORMAT]:\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    text\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    junitxml\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    tap\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    tapV13\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\nVerbose levels. [LEVEL]:\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    0 - No information alias of --cester-minimal\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    1,2\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    3 - Meaningful information\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    4,5,6,7,8,9\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    10 - Meaningful informations + garbage alias of --cester-verbose\n");
    free(file_name);
}

static void cester_print_test_case_message(char const* const type, char const* const message, char const* const file_path, unsigned const line_num) {
    char *cleaned_name = (char *) (superTestInstance.verbose_level >= 4 ? file_path : cester_extract_name(file_path) );
    if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "# ");

    } else if (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "    - ");

    }
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, type);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, " ");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, cleaned_name);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ":");
    cester_concat_int(&(superTestInstance.current_test_case)->execution_output, line_num);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ":");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, " in '");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, (superTestInstance.current_test_case)->name);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "': ");
    if (superTestInstance.verbose_level >= 2) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, message);
    }
    if (superTestInstance.verbose_level < 4) {
        free(cleaned_name);
    }
}

static __CESTER_INLINE__ void cester_print_assertion(char const* const expression, char const* const file_path, unsigned const line_num) {
    char *cleaned_name = (char *) (superTestInstance.verbose_level >= 4 ? file_path : cester_extract_name(file_path) );
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, cleaned_name);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ":");
    cester_concat_int(&(superTestInstance.current_test_case)->execution_output, line_num);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ":");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, " in '");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, (superTestInstance.current_test_case)->name);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "'");
    if (superTestInstance.verbose_level >= 2) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, " expr => '");
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, expression);
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "'");
    }
    if (superTestInstance.verbose_level < 4) {
        free(cleaned_name);
    }
}

static __CESTER_INLINE__ void cester_print_expect_actual(unsigned expecting, char const* const expect, char const* const received, char const* const file_path, unsigned const line_num) {
    char *cleaned_name = (char *) (superTestInstance.verbose_level >= 4 ? file_path : cester_extract_name(file_path) );
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, cleaned_name);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ":");
    cester_concat_int(&(superTestInstance.current_test_case)->execution_output, line_num);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ":");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, " in '");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, (superTestInstance.current_test_case)->name);
    if (superTestInstance.verbose_level >= 2) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "' =>");
        if (expecting == 0) {
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, " not expecting ");
        } else {
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, " expected ");
        }

        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "'");
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, expect);
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "'");
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ", received ");
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "'");
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, received);
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "'");
    }
    
    /*CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), (superTestInstance.verbose_level >= 4 ? file_path : cester_extract_name(file_path) ));
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ":");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_YELLOW), line_num);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ":");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " in '");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), (superTestInstance.current_test_case)->name);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "' =>");
    if (expecting == 0) {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " not expecting ");
    } else {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " expected ");
    }
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), received);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ", received ");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), expect);*/
    if (superTestInstance.verbose_level < 4) {
        free(cleaned_name);
    }
}

#ifndef CESTER_NO_TIME
static __CESTER_INLINE__ void print_test_result(double time_spent) {
#else
static __CESTER_INLINE__ void print_test_result() {
#endif
    unsigned cached_total_failed_tests_count = superTestInstance.total_failed_tests_count;
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\nRan ");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_WHITE), (superTestInstance.selected_test_cases_size == 0 ? CESTER_TOTAL_TESTS_COUNT : CESTER_TOTAL_TESTS_RAN));
    #ifndef CESTER_NO_TIME
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " test(s) in ");
        CESTER_DELEGATE_FPRINT_DOUBLE_2((CESTER_FOREGROUND_WHITE), (time_spent > 60 ? (time_spent / 60) : time_spent) );
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), (time_spent > 60 ? " Minutes\n" : " Seconds\n" ));
    #else
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " test(s)\n");
    #endif
    
    superTestInstance.total_failed_tests_count = superTestInstance.current_execution_status == CESTER_RESULT_SUCCESS && 
                                                 superTestInstance.total_failed_tests_count == 0 ? 0 : 1;
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "Synthesis: ");
    if (superTestInstance.report_success_regardless == 1) {
        CESTER_DELEGATE_FPRINT_STR(CESTER_FOREGROUND_GREEN, "SUCCESS");
    } else if (superTestInstance.report_failure_regardless == 1) {
        CESTER_DELEGATE_FPRINT_STR(CESTER_FOREGROUND_RED, "FAILURE");
    } else {
        CESTER_DELEGATE_FPRINT_STR(CESTER_GET_RESULT_AGGR_COLOR, CESTER_GET_RESULT_AGGR);
    }
    superTestInstance.total_failed_tests_count = cached_total_failed_tests_count;
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " Tests: ");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_YELLOW), CESTER_TOTAL_TESTS_COUNT);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " | Passing: ");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GREEN), CESTER_TOTAL_PASSED_TESTS_COUNT);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " | Failing: ");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_RED), CESTER_TOTAL_FAILED_TESTS_COUNT);
    if (CESTER_TOTAL_TEST_ERRORS_COUNT > 0) {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " | Errors: ");
        CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_RED), CESTER_TOTAL_TEST_ERRORS_COUNT);
    }
    if (CESTER_TOTAL_TESTS_SKIPPED > 0) {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " | Skipped: ");
        CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_YELLOW), CESTER_TOTAL_TESTS_SKIPPED);
    }
    if (CESTER_TOTAL_TODO_TESTS > 0) {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " | Todo: ");
        CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_YELLOW), CESTER_TOTAL_TODO_TESTS);
    }
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
    if (superTestInstance.report_failure_regardless == 1 || superTestInstance.report_success_regardless == 1) {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Avoid using the CESTER_REPORT_*_REGARDLESS macros, they hides the actual result of the test\n");
    }
}

static __CESTER_INLINE__ void print_test_case_result(TestCase* test_case) {
    char *cleaned_name = (superTestInstance.format_test_name == 1 ? cester_str_replace(test_case->name, '_', ' ') : test_case->name );
    #if defined(_WIN32) && !defined(CESTER_EXCLUDE_WINDOWS_H)
        unsigned print_color = __CESTER_CAST_CHAR_ARRAY__ CESTER_FOREGROUND_GRAY;
    #else 
        char* print_color = __CESTER_CAST_CHAR_ARRAY__ CESTER_FOREGROUND_GRAY;
    #endif
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "  ");
    if (test_case->test_type == CESTER_NORMAL_TODO_TEST || test_case->test_type == CESTER_NORMAL_SKIP_TEST) {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "o ");
        #ifndef CESTER_NO_TIME
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "(");
            CESTER_DELEGATE_FPRINT_DOUBLE_2((CESTER_FOREGROUND_GRAY), (test_case->execution_time > 60 ? (test_case->execution_time / 60) : test_case->execution_time));
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), (test_case->execution_time > 60 ? "m" : "s"));
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), ") ");
        #endif
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), cleaned_name);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), (test_case->test_type == CESTER_NORMAL_TODO_TEST ? " TODO " : " SKIP "));
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
    } else {
    	if (test_case->execution_status == CESTER_RESULT_SUCCESS) {
	        #ifdef _WIN32
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GREEN), "+ ");
	        #else
                #ifdef __CESTER_STDC_VERSION__
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GREEN), "\u2713 ");
                #else
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GREEN), "+ ");
                #endif
	        #endif
	    } else {
	        #ifdef _WIN32
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), "- ");
	        #else
                #ifdef __CESTER_STDC_VERSION__
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), "X ");
                #else
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), "- ");
                #endif
	        #endif
	        print_color = __CESTER_CAST_CHAR_ARRAY__ CESTER_FOREGROUND_RED;
	    }
        #ifndef CESTER_NO_TIME
	        CESTER_DELEGATE_FPRINT_STR((print_color), "(");
	        CESTER_DELEGATE_FPRINT_DOUBLE_2((print_color), (test_case->execution_time > 60 ? (test_case->execution_time / 60) : test_case->execution_time));
	        CESTER_DELEGATE_FPRINT_STR((print_color), (test_case->execution_time > 60 ? "m" : "s"));
            CESTER_DELEGATE_FPRINT_STR((print_color), ") ");
        #endif
            CESTER_DELEGATE_FPRINT_STR((print_color), cleaned_name);
            CESTER_DELEGATE_FPRINT_STR((print_color), "\n");
    }
    if (superTestInstance.format_test_name == 1) {
        free(cleaned_name);
    }
}

static __CESTER_INLINE__ void print_test_case_outputs(TestCase* test_case) {
    char *cleaned_name = (superTestInstance.verbose_level >= 4 ? superTestInstance.test_file_path : cester_extract_name(superTestInstance.test_file_path) );
    if (test_case->execution_status == CESTER_RESULT_SEGFAULT || test_case->execution_status == CESTER_RESULT_TERMINATED) {
        if (test_case->execution_status == CESTER_RESULT_SEGFAULT) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "SegfaultError ");
        } else {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "PrematureTermination ");
        }
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), cleaned_name);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ":");
        CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_WHITE), test_case->line_num);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ": ");
        if (test_case->execution_status == CESTER_RESULT_SEGFAULT) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "Segmentation fault ");
        } else {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "Premature Termination ");
        }
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "in '");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), test_case->name);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "' \n");
        
    }
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), test_case->execution_output);
    if (superTestInstance.verbose_level < 4) {
        free(cleaned_name);
    }
}

static __CESTER_INLINE__ void write_testcase_tap(TestCase *a_test_case, char* file_name, int index) {
    char *cleaned_name = (superTestInstance.format_test_name == 1 ? cester_str_replace(a_test_case->name, '_', ' ') : a_test_case->name );
    #if defined(_WIN32) && !defined(CESTER_EXCLUDE_WINDOWS_H)
        unsigned print_color = __CESTER_CAST_CHAR_ARRAY__ CESTER_FOREGROUND_YELLOW;
    #else 
        char* print_color = __CESTER_CAST_CHAR_ARRAY__ CESTER_FOREGROUND_YELLOW;
    #endif
    if (a_test_case->execution_status == CESTER_RESULT_SUCCESS || 
        a_test_case->test_type == CESTER_NORMAL_SKIP_TEST || 
        a_test_case->test_type == CESTER_NORMAL_TODO_TEST) {
            
        if (a_test_case->execution_status == CESTER_RESULT_SUCCESS) {
            print_color = __CESTER_CAST_CHAR_ARRAY__ CESTER_FOREGROUND_GREEN;
        }
        CESTER_DELEGATE_FPRINT_STR((print_color), "ok ");
        
    } else {
        print_color = __CESTER_CAST_CHAR_ARRAY__ CESTER_FOREGROUND_RED;
        CESTER_DELEGATE_FPRINT_STR((print_color), "not ok ");
    }
    CESTER_DELEGATE_FPRINT_INT((print_color), index);
    CESTER_DELEGATE_FPRINT_STR((print_color), " - ");
    if (a_test_case->test_type == CESTER_NORMAL_SKIP_TEST) {
        CESTER_DELEGATE_FPRINT_STR((print_color), "# SKIP ");
        
    } else if (a_test_case->test_type == CESTER_NORMAL_TODO_TEST) {
        CESTER_DELEGATE_FPRINT_STR((print_color), "# TODO ");
        
    }
    CESTER_DELEGATE_FPRINT_STR((print_color), cleaned_name);
    CESTER_DELEGATE_FPRINT_STR((print_color), ", ");
    switch (a_test_case->execution_status) {
        case CESTER_RESULT_SUCCESS:
            CESTER_DELEGATE_FPRINT_STR((print_color), "Passed");
            break;
        case CESTER_RESULT_SEGFAULT:
            CESTER_DELEGATE_FPRINT_STR((print_color), "Failed: Segmentation fault ");
            break;
        case CESTER_RESULT_TERMINATED:
            CESTER_DELEGATE_FPRINT_STR((print_color), "Failed: Premature Termination ");
            break;
        case CESTER_RESULT_UNRELEASED_STREAM:
            CESTER_DELEGATE_FPRINT_STR((print_color), "Failed: Unreleased Stream ");
            break;
#ifndef CESTER_NO_MEM_TEST
        case CESTER_RESULT_MEMORY_LEAK:
            CESTER_DELEGATE_FPRINT_STR((print_color), "Failed: Memory leak");
            break;
#endif
        default:
            if (a_test_case->test_type != CESTER_NORMAL_SKIP_TEST && 
                a_test_case->test_type != CESTER_NORMAL_TODO_TEST) {
                
                CESTER_DELEGATE_FPRINT_STR((print_color), "Failed");
            }
            break;
    }
    CESTER_DELEGATE_FPRINT_STR((print_color), "\n");
    if (superTestInstance.verbose_level >= 1) {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), a_test_case->execution_output);
    }
    if (superTestInstance.format_test_name == 1) {
        free(cleaned_name);
    }
}

static __CESTER_INLINE__ void write_testcase_tap_v13(TestCase *a_test_case, char* file_name, int index) {
    char *cleaned_name = (superTestInstance.format_test_name == 1 ? cester_str_replace(a_test_case->name, '_', ' ') : a_test_case->name );
    char *clean_file_path = (superTestInstance.verbose_level >= 4 ? superTestInstance.test_file_path : cester_extract_name(superTestInstance.test_file_path));
    #if defined(_WIN32) && !defined(CESTER_EXCLUDE_WINDOWS_H)
        unsigned print_color = __CESTER_CAST_CHAR_ARRAY__ CESTER_FOREGROUND_YELLOW;
    #else 
        char* print_color = __CESTER_CAST_CHAR_ARRAY__ CESTER_FOREGROUND_YELLOW;
    #endif
    if (a_test_case->execution_status == CESTER_RESULT_SUCCESS || 
        a_test_case->test_type == CESTER_NORMAL_SKIP_TEST || 
        a_test_case->test_type == CESTER_NORMAL_TODO_TEST) {
            
        if (a_test_case->execution_status == CESTER_RESULT_SUCCESS) {
            print_color = __CESTER_CAST_CHAR_ARRAY__ CESTER_FOREGROUND_GREEN;
        }
        CESTER_DELEGATE_FPRINT_STR((print_color), "ok ");
        
    } else {
        print_color = __CESTER_CAST_CHAR_ARRAY__ CESTER_FOREGROUND_RED;
        CESTER_DELEGATE_FPRINT_STR((print_color), "not ok ");
    }
    CESTER_DELEGATE_FPRINT_INT((print_color), index);
    CESTER_DELEGATE_FPRINT_STR((print_color), " - ");
    if (a_test_case->test_type == CESTER_NORMAL_SKIP_TEST) {
        CESTER_DELEGATE_FPRINT_STR((print_color), "# SKIP ");
        
    } else if (a_test_case->test_type == CESTER_NORMAL_TODO_TEST) {
        CESTER_DELEGATE_FPRINT_STR((print_color), "# TODO ");
        
    }
    CESTER_DELEGATE_FPRINT_STR((print_color), cleaned_name);
    CESTER_DELEGATE_FPRINT_STR((print_color), "\n");
    if (superTestInstance.verbose_level >= 1 && a_test_case->test_type != CESTER_NORMAL_SKIP_TEST && 
        a_test_case->test_type != CESTER_NORMAL_TODO_TEST) {
        if (a_test_case->execution_status == CESTER_RESULT_SUCCESS && superTestInstance.verbose_level == 0) {
            if (superTestInstance.format_test_name == 1) {
                free(cleaned_name);
            }
            return;
        }
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "  ---\n");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "  at:\n");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "    file: ");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), clean_file_path);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "\n    test_case: ");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), a_test_case->name);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "\n    line: ");
        CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), a_test_case->line_num);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "\n    column: 1");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "\n");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "  outputs:\n");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), a_test_case->execution_output);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "  message: ");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), a_test_case->name);
        switch (a_test_case->execution_status) {
            case CESTER_RESULT_SUCCESS:
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " passed");
                break;
            case CESTER_RESULT_SEGFAULT:
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " failed: Segmentation fault ");
                break;
            case CESTER_RESULT_TERMINATED:
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " failed: Premature termination ");
                break;
            case CESTER_RESULT_UNRELEASED_STREAM:
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " failed: Unreleased stream ");
                break;
#ifndef CESTER_NO_MEM_TEST
            case CESTER_RESULT_MEMORY_LEAK:
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " failed: Memory leak");
                break;
#endif
            default:
                if (a_test_case->test_type != CESTER_NORMAL_SKIP_TEST && 
                    a_test_case->test_type != CESTER_NORMAL_TODO_TEST) {
                    
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " failed");
                }
                break;
        }
        #ifndef CESTER_NO_TIME
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "\n  time: ");
            CESTER_DELEGATE_FPRINT_DOUBLE_2((CESTER_FOREGROUND_GRAY), a_test_case->execution_time);
        #endif
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "\n  ...\n");
    }
    if (superTestInstance.format_test_name == 1) {
        free(cleaned_name);
    }
    if (superTestInstance.verbose_level < 4) {
        free(clean_file_path);
    }
}

static __CESTER_INLINE__ void write_testcase_junitxml(TestCase *a_test_case, char* file_name) {
    char *clean_file_path = (superTestInstance.verbose_level >= 4 ? superTestInstance.test_file_path : cester_extract_name(superTestInstance.test_file_path));
    
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), "    <testcase");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " classname=");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), file_name);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " name=");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), a_test_case->name);
    #ifndef CESTER_NO_TIME
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " time=");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
        CESTER_DELEGATE_FPRINT_DOUBLE_2((CESTER_FOREGROUND_MAGENTA), a_test_case->execution_time);
    #endif
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
    switch (a_test_case->execution_status) {
        case CESTER_RESULT_SUCCESS:
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), "/>\n");
            break;
        case CESTER_RESULT_SEGFAULT:
        case CESTER_RESULT_TERMINATED:
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), ">\n        <failure");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " message=");
            if (a_test_case->execution_status == CESTER_RESULT_SEGFAULT) {
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"the test case crashed\"");
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " type=");
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"SegmentationFault\"");
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), ">");
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "SegfaultError ");
            } else {
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"the test case was terminated\"");
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " type=");
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"PrematureTermination\"");
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), ">");
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "PrematureTermination ");
            }
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), clean_file_path);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), ":");
            CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), a_test_case->line_num);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), ": ");
            if (a_test_case->execution_status == CESTER_RESULT_SEGFAULT) {
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "Segmentation fault ");
            } else {
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "Premature Termination ");
            }
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "in '");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), a_test_case->name);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "' \n");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), a_test_case->execution_output);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), "        </failure>\n    </testcase>\n");
            break;
        case CESTER_RESULT_UNRELEASED_STREAM:
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), ">\n        <failure");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " message=");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"the test case failed to release captured streams\"");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " type=");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"StreamCaptureError\"");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), ">");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), a_test_case->execution_output);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), "\n        </failure>\n    </testcase>\n");
            break;
#ifndef CESTER_NO_MEM_TEST
        case CESTER_RESULT_MEMORY_LEAK:
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), ">\n        <failure");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " message=");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"the test case leaks memory\"");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " type=");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"MemoryLeakError\"");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), ">");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), a_test_case->execution_output);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), "\n        </failure>\n    </testcase>\n");
            break;
#endif
        default:
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), ">\n        <failure");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " message=");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"the test case failed\"");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " type=");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"TestFailed\"");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), ">");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), a_test_case->execution_output);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), "        </failure>\n    </testcase>\n");
            break;
    }
    if (superTestInstance.verbose_level < 4) {
        free(clean_file_path);
    }
    
}

#ifndef CESTER_NO_MEM_TEST
static __CESTER_INLINE__ unsigned check_memory_allocated_for_functions(char *funcname1, char *funcname2, char *prefix, char **write_string) {
    unsigned mem_index;
    unsigned leaked_memory_count = 0;
    char *cleaned_name = (superTestInstance.verbose_level >= 4 ? superTestInstance.test_file_path : cester_extract_name(superTestInstance.test_file_path) );
    if (superTestInstance.mem_test_active == 1) {
        CESTER_ARRAY_FOREACH(superTestInstance.mem_alloc_manager, mem_index, alloc_mem, {
            if ((funcname1 != CESTER_NULL && cester_string_equals((char*)((AllocatedMemory*)alloc_mem)->function_name, funcname1)) || 
                (funcname2 != CESTER_NULL && cester_string_equals((char*)((AllocatedMemory*)alloc_mem)->function_name, funcname2))) {
                    
                leaked_memory_count += 1;
                if (superTestInstance.current_test_case != CESTER_NULL) {
                    cester_concat_str(write_string, prefix);
                    cester_concat_str(write_string, "MemoryLeakError ");
                    cester_concat_str(write_string, cleaned_name);
                    cester_concat_str(write_string, ":");
                    cester_concat_int(write_string, ((AllocatedMemory*)alloc_mem)->line_num);
                    cester_concat_str(write_string, ": ");
                    cester_concat_str(write_string, "in '");
                    cester_concat_str(write_string, (char*)((AllocatedMemory*)alloc_mem)->function_name);
                    if (superTestInstance.verbose_level >= 2) {
                        cester_concat_str(write_string, "' => Memory allocated in line '");
                        cester_concat_int(write_string, ((AllocatedMemory*)alloc_mem)->line_num);
                        cester_concat_str(write_string, "' not freed. Leaking '");
                        cester_concat_sizet(write_string, ((AllocatedMemory *)alloc_mem)->allocated_bytes);
                        cester_concat_str(write_string, "' Bytes ");
                    }
                    cester_concat_str(write_string, "\n");
                }
            }
        })
    }
    if (superTestInstance.verbose_level < 4) {
        free(cleaned_name);
    }
    return leaked_memory_count;
}
#endif

/**
   Clean up all the super instance date and free 
   all the allocated memories used by libcester super instance
*/
static void cester_cleanup_super_instance();

static __CESTER_INLINE__ int cester_print_result(TestCase cester_test_cases[], TestInstance* test_instance) {
    unsigned index_sub, ret_val;
    unsigned i, index4, index5, index6, index7;
    char *prefix = (char *) "";
    char *file_name = cester_extract_name_only(superTestInstance.test_file_path);
    
    #ifndef CESTER_NO_TIME
        clock_t tok;
        double time_spent;

        tok = clock();
        time_spent = (double)(tok - superTestInstance.start_tic) / CLOCKS_PER_SEC;
    #endif
    if (superTestInstance.registered_test_cases->size == 0) {
        for (i=0;cester_test_cases[i].test_type != CESTER_TESTS_TERMINATOR;++i) {
            if (cester_test_cases[i].test_type == CESTER_AFTER_ALL_TEST && superTestInstance.single_output_only == 0) {
                superTestInstance.current_cester_function_type = CESTER_AFTER_ALL_TEST;
                ((cester_test)cester_test_cases[i].test_function)(test_instance);
            }
        }
    }
    CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index4, test_case, {
        if (((TestCase*)test_case)->test_type == CESTER_AFTER_ALL_TEST && superTestInstance.single_output_only == 0) {
            superTestInstance.current_cester_function_type = CESTER_AFTER_ALL_TEST;
            ((cester_test)((TestCase*)test_case)->test_function)(test_instance);
        }
    })
    if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1 || 
        cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1) {
        prefix = (char *) "# ";
    }
    
#ifndef CESTER_NO_MEM_TEST
    ret_val = check_memory_allocated_for_functions((char *)"CESTER_BEFORE_ALL", (char *)"CESTER_OPTIONS", prefix, &superTestInstance.main_execution_output);
    if (ret_val > 0) {
        superTestInstance.current_execution_status = CESTER_RESULT_MEMORY_LEAK;
        superTestInstance.total_test_errors_count += ret_val;
    }
#endif

    if (superTestInstance.single_output_only == 0) {
        if (cester_string_equals(superTestInstance.output_format, (char*) "junitxml") == 1) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), "<?xml");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " version=");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"1.0\"");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " encoding=");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"UTF-8\"");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), " ?>\n");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), "<testsuite");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " tests=");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
            CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_MAGENTA), (superTestInstance.selected_test_cases_size == 0 ? CESTER_TOTAL_TESTS_COUNT : CESTER_TOTAL_TESTS_RAN));
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " failures=");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
            CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_MAGENTA), superTestInstance.total_failed_tests_count);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " name=");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), file_name);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " errors=");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
            CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_MAGENTA), CESTER_TOTAL_TEST_ERRORS_COUNT);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " skipped=");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
            CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_MAGENTA), CESTER_TOTAL_TESTS_SKIPPED + CESTER_TOTAL_TODO_TESTS);
            #ifndef CESTER_NO_TIME
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), " time=");
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
                CESTER_DELEGATE_FPRINT_DOUBLE_2((CESTER_FOREGROUND_MAGENTA), time_spent);
            #endif
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_MAGENTA), "\"");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), ">\n");
            if (superTestInstance.registered_test_cases->size == 0) {
                for (i=0;cester_test_cases[i].test_type != CESTER_TESTS_TERMINATOR;++i) {
                    if (cester_test_cases[i].test_type == CESTER_NORMAL_TEST && cester_test_cases[i].execution_status != CESTER_RESULT_UNKNOWN) {
                        write_testcase_junitxml(&cester_test_cases[i], file_name);
                    }
                }
            }
            CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index5, test_case, {
                if (((TestCase*)test_case)->test_type == CESTER_NORMAL_TEST && ((TestCase*)test_case)->execution_status != CESTER_RESULT_UNKNOWN) {
                    write_testcase_junitxml(((TestCase*)test_case), file_name);
                }
            })
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_BLUE), "</testsuite>\n");
            
        } else if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1) {
            CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_WHITE), 1);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "..");
            CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_WHITE), (superTestInstance.selected_test_cases_size == 0 ? CESTER_TOTAL_TESTS_COUNT : CESTER_TOTAL_TESTS_RAN));
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
            index_sub = 1;
            if (superTestInstance.registered_test_cases->size == 0) {
                for (i=0;cester_test_cases[i].test_type != CESTER_TESTS_TERMINATOR;++i) {
                    if ((cester_test_cases[i].test_type == CESTER_NORMAL_TEST || cester_test_cases[i].test_type == CESTER_NORMAL_TODO_TEST || 
                        cester_test_cases[i].test_type == CESTER_NORMAL_SKIP_TEST)) {
                        
                        if (superTestInstance.selected_test_cases_size > 0 && cester_test_cases[i].execution_status == CESTER_RESULT_UNKNOWN) {
                            continue;
                        }
                        write_testcase_tap(&cester_test_cases[i], file_name, index_sub);
                        ++index_sub;
                    }
                }
            }
            CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index5, test_case, {
                if (((TestCase*)test_case)->test_type == CESTER_NORMAL_TEST || ((TestCase*)test_case)->test_type == CESTER_NORMAL_TODO_TEST || 
                    ((TestCase*)test_case)->test_type == CESTER_NORMAL_SKIP_TEST) {
                        
                    if (superTestInstance.selected_test_cases_size > 0 && ((TestCase*)test_case)->execution_status == CESTER_RESULT_UNKNOWN) {
                        continue;
                    }
                    write_testcase_tap(((TestCase*)test_case), file_name, index_sub);
                    ++index_sub;
                }
            })
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), superTestInstance.main_execution_output);
            if (superTestInstance.verbose_level >= 1) {
                if (CESTER_TOTAL_TEST_ERRORS_COUNT > 0) {
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "# ");
                    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), CESTER_TOTAL_TEST_ERRORS_COUNT);
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " total error(s) occured\n");
                }
                if (CESTER_TOTAL_TODO_TESTS > 0) {
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "# ");
                    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), CESTER_TOTAL_TODO_TESTS);
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " todo test case(s) skipped\n");
                }
                if (CESTER_TOTAL_TESTS_SKIPPED > 0) {
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "# ");
                    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), CESTER_TOTAL_TESTS_SKIPPED);
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " test case(s) skipped\n");
                }
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "# Failed ");
                CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), CESTER_TOTAL_FAILED_TESTS_COUNT);
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " of ");
                CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), (superTestInstance.selected_test_cases_size == 0 ? CESTER_TOTAL_TESTS_COUNT : CESTER_TOTAL_TESTS_RAN));
                #ifndef CESTER_NO_TIME
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " tests\n# Time ");
                    CESTER_DELEGATE_FPRINT_DOUBLE_2((CESTER_FOREGROUND_GRAY), (time_spent > 60 ? (time_spent / 60) : time_spent));
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), (time_spent > 60 ? " Minutes\n" : " Seconds\n" ));
                #else
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " tests\n");
                #endif
            }
            
        } else if (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_CYAN), "TAP version 13");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_CYAN), "\n");
            CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_CYAN), 1);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_CYAN), "..");
            CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_CYAN), (superTestInstance.selected_test_cases_size == 0 ? CESTER_TOTAL_TESTS_COUNT : CESTER_TOTAL_TESTS_RAN));
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_CYAN), "\n");
            index_sub = 1;
            if (superTestInstance.registered_test_cases->size == 0) {
                for (i=0;cester_test_cases[i].test_type != CESTER_TESTS_TERMINATOR;++i) {
                    if ((cester_test_cases[i].test_type == CESTER_NORMAL_TEST || cester_test_cases[i].test_type == CESTER_NORMAL_TODO_TEST || 
                        cester_test_cases[i].test_type == CESTER_NORMAL_SKIP_TEST)) {
                        
                        if (superTestInstance.selected_test_cases_size > 0 && cester_test_cases[i].execution_status == CESTER_RESULT_UNKNOWN) {
                            continue;
                        }
                        write_testcase_tap_v13(&cester_test_cases[i], file_name, index_sub);
                        ++index_sub;
                    }
                }
            }
            CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index5, test_case, {
                if (((TestCase*)test_case)->test_type == CESTER_NORMAL_TEST || ((TestCase*)test_case)->test_type == CESTER_NORMAL_TODO_TEST || 
                    ((TestCase*)test_case)->test_type == CESTER_NORMAL_SKIP_TEST) {
                    
                    if (superTestInstance.selected_test_cases_size > 0 && ((TestCase*)test_case)->execution_status == CESTER_RESULT_UNKNOWN) {
                        continue;
                    }
                    write_testcase_tap_v13(((TestCase*)test_case), file_name, index_sub);
                    ++index_sub;
                }
            })
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), superTestInstance.main_execution_output);
            if (superTestInstance.verbose_level >= 1) {
                if (CESTER_TOTAL_TEST_ERRORS_COUNT > 0) {
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "# ");
                    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), CESTER_TOTAL_TEST_ERRORS_COUNT);
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " total error(s) occured\n");
                }
                if (CESTER_TOTAL_TODO_TESTS > 0) {
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "# ");
                    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), CESTER_TOTAL_TODO_TESTS);
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " todo test case(s) skipped\n");
                }
                if (CESTER_TOTAL_TESTS_SKIPPED > 0) {
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "# ");
                    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), CESTER_TOTAL_TESTS_SKIPPED);
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " test case(s) skipped\n");
                }
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "# Failed ");
                CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), CESTER_TOTAL_FAILED_TESTS_COUNT);
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " of ");
                CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), (superTestInstance.selected_test_cases_size == 0 ? CESTER_TOTAL_TESTS_COUNT : CESTER_TOTAL_TESTS_RAN));
                #ifndef CESTER_NO_TIME
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " tests\n# Time ");
                    CESTER_DELEGATE_FPRINT_DOUBLE_2((CESTER_FOREGROUND_GRAY), (time_spent > 60 ? (time_spent / 60) : time_spent));
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), (time_spent > 60 ? " Minutes\n" : " Seconds\n" ));
                #else
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " tests\n");
                #endif
            }
            
        } else {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
            if (superTestInstance.registered_test_cases->size == 0) {
                for (i=0;cester_test_cases[i].test_type != CESTER_TESTS_TERMINATOR;++i) {
                    if (superTestInstance.selected_test_cases_size > 0 && cester_test_cases[i].execution_status != CESTER_RESULT_UNKNOWN) {
                        print_test_case_result(&cester_test_cases[i]);
                        
                    } else if (((cester_test_cases[i].test_type == CESTER_NORMAL_TEST && cester_test_cases[i].execution_status != CESTER_RESULT_UNKNOWN) || 
                            (cester_test_cases[i].test_type == CESTER_NORMAL_TODO_TEST || cester_test_cases[i].test_type == CESTER_NORMAL_SKIP_TEST)) && 
                            superTestInstance.selected_test_cases_size == 0) {
                            
                        print_test_case_result(&cester_test_cases[i]);
                    }
                }
            }
            CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index6, test_case_delegate, {
                TestCase* test_case = (TestCase*) test_case_delegate;
                if (superTestInstance.selected_test_cases_size > 0 && test_case->execution_status != CESTER_RESULT_UNKNOWN) {
                    print_test_case_result(test_case);
                    
                } else if (((test_case->test_type == CESTER_NORMAL_TEST && test_case->execution_status != CESTER_RESULT_UNKNOWN) || 
                        (test_case->test_type == CESTER_NORMAL_TODO_TEST || test_case->test_type == CESTER_NORMAL_SKIP_TEST)) && 
                        superTestInstance.selected_test_cases_size == 0) {
                        
                    print_test_case_result(test_case);
                }
            })
            
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
            if (superTestInstance.registered_test_cases->size == 0) {
                for (i=0;cester_test_cases[i].test_type != CESTER_TESTS_TERMINATOR;++i) {
                    if (cester_test_cases[i].test_type == CESTER_NORMAL_TEST && cester_test_cases[i].execution_status != CESTER_RESULT_UNKNOWN) {
                        print_test_case_outputs(&cester_test_cases[i]);
                    }
                }
            }
            CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index7, test_case_delegate1, {
                TestCase* test_case1 = (TestCase*) test_case_delegate1;
                if (test_case1->test_type == CESTER_NORMAL_TEST && test_case1->execution_status != CESTER_RESULT_UNKNOWN) {
                    print_test_case_outputs(test_case1);
                }
            })
            
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), superTestInstance.main_execution_output);
            #ifndef CESTER_NO_TIME
                print_test_result(time_spent);
            #else
                print_test_result();
            #endif
        }
    }
    
    CESTER_RESET_TERMINAL_ATTR();
    cester_cleanup_super_instance();
    if (CESTER_TOTAL_FAILED_TESTS_COUNT != 0 && superTestInstance.current_execution_status == CESTER_RESULT_SUCCESS) {
        free(file_name);
        return CESTER_RESULT_FAILURE;
    }
    if (superTestInstance.report_success_regardless == 1) {
        free(file_name);
        return CESTER_RESULT_SUCCESS;
    } else if (superTestInstance.report_failure_regardless == 1) {
        free(file_name);
        return CESTER_RESULT_FAILURE;
    }
    free(file_name);
    return superTestInstance.current_execution_status;
}

/* Assertions, Tests */


/**
    Does nothing just an empty placeholder. Can be used in the 
    CESTER_SKIP_TEST and CESTER_TODO_TEST when compiling with 
    -ansi and -pedantic-errors flag
*/
#define cester_assert_nothing()


/**
    Send the parameter into a black hole.
*/
#define cester_swallow(param) 

/**
    Compare two argument using the provided operator
    Prints the expression as in the source code
    
    \param w a value to compare to y
    \param x the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param y a value to compare to w
    \param z the expression to print in output
*/
#define cester_assert_cmp_msg(w,x,y,z) cester_evaluate_expression(w x y, z, __FILE__, __LINE__)

/**
    Compare two argument using the provided operator
    Prints the expression as in the source code
    
    \param x a value to compare to z
    \param y the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param z a value to compare to x
*/
#define cester_assert_cmp(x,y,z) cester_assert_cmp_msg(x, y, z, "(" #x " " #y " " #z ")")

/**
    Check if the expression evaluates to true. 
    Prints the expression as in the source code.
    
    \param x the expression to check if true
*/
#define cester_assert_true(x) cester_assert_cmp_msg(x, ==, 1, "(" #x ")")

/**
    Check if the expression evaluates to true. 
    Prints the second argument to the macro as the 
    expression in output.
    
    \param x the expression to check if true
    \param y the text to print out in output
*/
#define cester_assert_true_msg(x,y) cester_assert_cmp_msg(x, ==, 1, y)

/**
    Check if the expression evaluates to false. 
    Prints the expression as in the source code.
    
    \param x the expression to check if false
*/
#define cester_assert_false(x) cester_assert_cmp_msg(x, ==, 0, "(" #x ")")

/**
    Check if the expression evaluates to false. 
    Prints the second argument to the macro as the 
    expression in output.
    
    \param x the expression to check if false
    \param y the text to print out in output
*/
#define cester_assert_false_msg(x,y) cester_assert_cmp_msg(x, ==, 0, y)

/**
    Assertion macro that passes if an expression is CESTER_NULL. 
    Prints the expression as in the source code.
    
    \param x the expression to check if it CESTER_NULL.
*/
#define cester_assert_null(x) cester_assert_cmp_msg(x, ==, CESTER_NULL, "(" #x ")")

/**
    Assertion macro that passes if an expression is not CESTER_NULL. 
    Prints the expression as in the source code.
    
    \param x the expression to check if it not CESTER_NULL.
*/
#define cester_assert_not_null(x) cester_assert_cmp_msg(x, !=, CESTER_NULL, "!(" #x ")")

/**
    Assertion macro that passes if the two expression is equal. 
    Prints the expression as in the source code
    
    \param x the first expression to compare
    \param y the second expression to compare to the first expression
*/
#define cester_assert_equal(x,y) cester_evaluate_expect_actual(x==y, 1, #x, #y, __FILE__, __LINE__)

/**
    Assertion macro that passes if the two expression is not equal. 
    Prints the expression as in the source code
    
    \param x the first expression to compare
    \param y the second expression to compare to the first expression
*/
#define cester_assert_not_equal(x,y) cester_evaluate_expect_actual(x!=y, 0, #x, #y, __FILE__, __LINE__)

/**
    Compare two strings. If the comparison fails the test case 
    is marked as failed. The advantage of this macro is that it display 
    the actual values of the two strings.
    
    \param x a string to compare
    \param y another string to compare with the first string
*/
#define cester_assert_str_equal(x,y) cester_evaluate_expect_actual_str(x, y, #x, #y, 1, __FILE__, __LINE__)

/**
    Compare two strings. If the comparison passes the test case 
    is marked as failed. The advantage of this macro is that it display 
    the actual values of the two strings.
    
    \param x a string to compare
    \param y another string to compare with the first string
*/
#define cester_assert_str_not_equal(x,y) cester_evaluate_expect_actual_str(x, y, #x, #y, 0, __FILE__, __LINE__)

/**
    Compare two pointers. If the comparison fails the test case 
    is marked as failed. The advantage of this macro is that it display 
    the actual values of the two pointers.
    
    \param x a pointer to compare
    \param y another pointer to compare with the first pointer
*/
#define cester_assert_ptr_equal(x,y) cester_evaluate_expect_actual_ptr(x, y, #x, #y, 1, __FILE__, __LINE__)

/**
    Compare two pointers. If the comparison passes the test case 
    is marked as failed. The advantage of this macro is that it display 
    the actual values of the two pointers.
    
    \param x a pointer to compare
    \param y another pointer to compare with the first pointer
*/
#define cester_assert_ptr_not_equal(x,y) cester_evaluate_expect_actual_ptr(x, y, #x, #y, 0, __FILE__, __LINE__)

/* document the following, add 'compile time only' */
#define __internal_cester_assert_cmp(w,x,y,z) (w x y, z, w, y, #x, __FILE__, __LINE__)
#define __internal_cester_assert_eq(x,y,z) (CESTER_COMPARATOR_EQUAL, "expected " #z ",%s received " #z, y, x, "", __FILE__, __LINE__)
#define __internal_cester_assert_ne(x,y,z) (CESTER_COMPARATOR_NOT_EQUAL, "not expecting " #z ",%s found " #z, x, y, "", __FILE__, __LINE__)
#define __internal_cester_assert_gt(x,y,z) (CESTER_COMPARATOR_GREATER_THAN, "expected value to be greater than " #z ",%s received " #z, x, y, "", __FILE__, __LINE__)
#define __internal_cester_assert_ge(x,y,z) (CESTER_COMPARATOR_GREATER_THAN_OR_EQUAL, "expected value to be greater than or equal to " #z ",%s received " #z, x, y, "", __FILE__, __LINE__)
#define __internal_cester_assert_lt(x,y,z) (CESTER_COMPARATOR_LESSER_THAN, "expected value to be lesser than " #z ",%s received " #z, x, y, "", __FILE__, __LINE__)
#define __internal_cester_assert_le(x,y,z) (CESTER_COMPARATOR_LESSER_THAN_OR_EQUAL, "expected value to be lesser than or equal to " #z ",%s received " #z, x, y, "", __FILE__, __LINE__)

/**
    Compare two char using the provided operator
    This macro prints out the actual values of the two 
    chars.
    
    \param w a char
    \param x the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param y another char
    \param z the string formated for output
*/
#define cester_assert_cmp_char(w,x,y,z) CESTER_CONCAT(cester_compare_char_pre_evaluated, __internal_cester_assert_cmp(w,x,y,z))

/**
    Check if the two characters are the same.
    This macro prints out the actual values of the two 
    characters.
    
    \param x a char
    \param y another char
*/
#define cester_assert_char_eq(x,y) CESTER_CONCAT(cester_compare_char, __internal_cester_assert_eq(x,y,%c))

/**
    Check if the two char are not the same.
    This macro prints out the actual values of the two 
    chars.
    
    \param x a char
    \param y another char
*/
#define cester_assert_char_ne(x,y) CESTER_CONCAT(cester_compare_char, __internal_cester_assert_ne(x,y,%c))

/**
    Check if the a char is greater than the other.
    This macro prints out the actual values of the two 
    chars.
    
    \param x a char
    \param y another char
*/
#define cester_assert_char_gt(x,y) CESTER_CONCAT(cester_compare_char, __internal_cester_assert_gt(x,y,%c))

/**
    Check if the a char is greater than or equal to the other.
    This macro prints out the actual values of the two 
    chars.
    
    \param x a char
    \param y another char
*/
#define cester_assert_char_ge(x,y) CESTER_CONCAT(cester_compare_char, __internal_cester_assert_ge(x,y,%c))

/**
    Check if the a char is lesser than the other.
    This macro prints out the actual values of the two 
    chars.
    
    \param x a char
    \param y another char
*/
#define cester_assert_char_lt(x,y) CESTER_CONCAT(cester_compare_char, __internal_cester_assert_lt(x,y,%c))

/**
    Check if the a char is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    chars.
    
    \param x a char
    \param y another char
*/
#define cester_assert_char_le(x,y) CESTER_CONCAT(cester_compare_char, __internal_cester_assert_le(x,y,%c))

/**
    Compare two unsigned char using the provided operator
    This macro prints out the actual values of the two 
    unsigned char.
    
    \param w an unsigned char
    \param x the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param y another unsigned char
    \param z the string formated for output
*/
#define cester_assert_cmp_uchar(w,x,y,z) CESTER_CONCAT(cester_compare_uchar_pre_evaluated, __internal_cester_assert_cmp(w,x,y,z))

/**
    Check if the two unsigned char are the same.
    This macro prints out the actual values of the two 
    unsigned char.
    
    \param x an unsigned char
    \param y another unsigned char
*/
#define cester_assert_uchar_eq(x,y) CESTER_CONCAT(cester_compare_uchar, __internal_cester_assert_eq(x,y,%c))

/**
    Check if the two unsigned char are not the same.
    This macro prints out the actual values of the two 
    unsigned char.
    
    \param x an unsigned char
    \param y another unsigned char
*/
#define cester_assert_uchar_ne(x,y) CESTER_CONCAT(cester_compare_uchar, __internal_cester_assert_ne(x,y,%c))

/**
    Check if the a unsigned char is greater than the other.
    This macro prints out the actual values of the two 
    unsigned char.
    
    \param x an unsigned char
    \param y another unsigned char
*/
#define cester_assert_uchar_gt(x,y) CESTER_CONCAT(cester_compare_uchar, __internal_cester_assert_gt(x,y,%c))

/**
    Check if the a unsigned char is greater than or equal to the other.
    This macro prints out the actual values of the two 
    unsigned char.
    
    \param x an unsigned char
    \param y another unsigned char
*/
#define cester_assert_uchar_ge(x,y) CESTER_CONCAT(cester_compare_uchar, __internal_cester_assert_ge(x,y,%c))

/**
    Check if the a unsigned char is lesser than the other.
    This macro prints out the actual values of the two 
    unsigned char.
    
    \param x an unsigned char
    \param y another unsigned char
*/
#define cester_assert_uchar_lt(x,y) CESTER_CONCAT(cester_compare_uchar, __internal_cester_assert_lt(x,y,%c))

/**
    Check if the a unsigned char is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    unsigned char.
    
    \param x an unsigned char
    \param y another unsigned char
*/
#define cester_assert_uchar_le(x,y) CESTER_CONCAT(cester_compare_uchar, __internal_cester_assert_le(x,y,%c))

/**
    Compare two short using the provided operator
    This macro prints out the actual values of the two 
    short.
    
    \param w a short
    \param x the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param y another short
    \param z the string formated for output
*/
#define cester_assert_cmp_short(w,x,y,z) CESTER_CONCAT(cester_compare_short_pre_evaluated, __internal_cester_assert_cmp(w,x,y,z))

/**
    Check if the two short are the same.
    This macro prints out the actual values of the two 
    short.
    
    \param x a short
    \param y another short
*/
#define cester_assert_short_eq(x,y) CESTER_CONCAT(cester_compare_short, __internal_cester_assert_eq(x,y,%hi))

/**
    Check if the two short are not the same.
    This macro prints out the actual values of the two 
    short.
    
    \param x a short
    \param y another short
*/
#define cester_assert_short_ne(x,y) CESTER_CONCAT(cester_compare_short, __internal_cester_assert_ne(x,y,%hi))

/**
    Check if the a short is greater than the other.
    This macro prints out the actual values of the two 
    short.
    
    \param x a short
    \param y another short
*/
#define cester_assert_short_gt(x,y) CESTER_CONCAT(cester_compare_short, __internal_cester_assert_gt(x,y,%hi))

/**
    Check if the a short is greater than or equal to the other.
    This macro prints out the actual values of the two 
    short.
    
    \param x a short
    \param y another short
*/
#define cester_assert_short_ge(x,y) CESTER_CONCAT(cester_compare_short, __internal_cester_assert_ge(x,y,%hi))

/**
    Check if the a short is lesser than the other.
    This macro prints out the actual values of the two 
    short.
    
    \param x a short
    \param y another short
*/
#define cester_assert_short_lt(x,y) CESTER_CONCAT(cester_compare_short, __internal_cester_assert_lt(x,y,%hi))

/**
    Check if the a short is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    short.
    
    \param x a short
    \param y another short
*/
#define cester_assert_short_le(x,y) CESTER_CONCAT(cester_compare_short, __internal_cester_assert_le(x,y,%hi))

/**
    Compare two unsigned short using the provided operator
    This macro prints out the actual values of the two 
    unsigned short.
    
    \param w an unsigned short
    \param x the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param y another unsigned short
    \param z the string formated for output
*/
#define cester_assert_cmp_ushort(w,x,y,z) CESTER_CONCAT(cester_compare_ushort_pre_evaluated, __internal_cester_assert_cmp(w,x,y,z))

/**
    Check if the two unsigned short are the same.
    This macro prints out the actual values of the two 
    unsigned short.
    
    \param x an unsigned short
    \param y another unsigned short
*/
#define cester_assert_ushort_eq(x,y) CESTER_CONCAT(cester_compare_ushort, __internal_cester_assert_eq(x,y,%hu))

/**
    Check if the two unsigned short are not the same.
    This macro prints out the actual values of the two 
    unsigned short.
    
    \param x an unsigned short
    \param y another unsigned short
*/
#define cester_assert_ushort_ne(x,y) CESTER_CONCAT(cester_compare_ushort, __internal_cester_assert_ne(x,y,%hu))

/**
    Check if the a unsigned short is greater than the other.
    This macro prints out the actual values of the two 
    unsigned short.
    
    \param x an unsigned short
    \param y another unsigned short
*/
#define cester_assert_ushort_gt(x,y) CESTER_CONCAT(cester_compare_ushort, __internal_cester_assert_gt(x,y,%hu))

/**
    Check if the a unsigned short is greater than or equal to the other.
    This macro prints out the actual values of the two 
    unsigned short.
    
    \param x an unsigned short
    \param y another unsigned short
*/
#define cester_assert_ushort_ge(x,y) CESTER_CONCAT(cester_compare_ushort, __internal_cester_assert_ge(x,y,%hu))

/**
    Check if the a unsigned short is lesser than the other.
    This macro prints out the actual values of the two 
    unsigned short.
    
    \param x an unsigned short
    \param y another unsigned short
*/
#define cester_assert_ushort_lt(x,y) CESTER_CONCAT(cester_compare_ushort, __internal_cester_assert_lt(x,y,%hu))

/**
    Check if the a unsigned short is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    unsigned short.
    
    \param x an unsigned short
    \param y another unsigned short
*/
#define cester_assert_ushort_le(x,y) CESTER_CONCAT(cester_compare_ushort, __internal_cester_assert_le(x,y,%hu))

/**
    Compare two int using the provided operator
    This macro prints out the actual values of the two 
    int.
    
    \param w an int
    \param x the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param y another int
    \param z the string formated for output
*/
#define cester_assert_cmp_int(w,x,y,z) CESTER_CONCAT(cester_compare_int_pre_evaluated, __internal_cester_assert_cmp(w,x,y,z))

/**
    Check if the two int are the same.
    This macro prints out the actual values of the two 
    int.
    
    \param x an int
    \param y another int
*/
#define cester_assert_int_eq(x,y) CESTER_CONCAT(cester_compare_int, __internal_cester_assert_eq(x,y,%d))

/**
    Check if the two int are not the same.
    This macro prints out the actual values of the two 
    int.
    
    \param x an int
    \param y another int
*/
#define cester_assert_int_ne(x,y)  CESTER_CONCAT(cester_compare_int, __internal_cester_assert_ne(x,y,%d))

/**
    Check if the a int is greater than the other.
    This macro prints out the actual values of the two 
    int.
    
    \param x an int
    \param y another int
*/
#define cester_assert_int_gt(x,y) CESTER_CONCAT(cester_compare_int, __internal_cester_assert_gt(x,y,%d))

/**
    Check if the a int is greater than or equal to the other.
    This macro prints out the actual values of the two 
    int.
    
    \param x an int
    \param y another int
*/
#define cester_assert_int_ge(x,y) CESTER_CONCAT(cester_compare_int, __internal_cester_assert_ge(x,y,%d))

/**
    Check if the a int is lesser than the other.
    This macro prints out the actual values of the two 
    int.
    
    \param x an int
    \param y another int
*/
#define cester_assert_int_lt(x,y) CESTER_CONCAT(cester_compare_int, __internal_cester_assert_lt(x,y,%d))

/**
    Check if the a int is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    int.
    
    \param x an int
    \param y another int
*/
#define cester_assert_int_le(x,y) CESTER_CONCAT(cester_compare_int, __internal_cester_assert_le(x,y,%d))

/**
    Compare two unsigned int using the provided operator
    This macro prints out the actual values of the two 
    unsigned int.
    
    \param w an unsigned int
    \param x the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param y another unsigned int
    \param z the string formated for output
*/
#define cester_assert_cmp_uint(w,x,y,z) CESTER_CONCAT(cester_compare_uint_pre_evaluated, __internal_cester_assert_cmp(w,x,y,z))

/**
    Check if the two unsigned int are the same.
    This macro prints out the actual values of the two 
    unsigned int.
    
    \param x an unsigned int
    \param y another unsigned int
*/
#define cester_assert_uint_eq(x,y) CESTER_CONCAT(cester_compare_uint, __internal_cester_assert_eq(x,y,%u))

/**
    Check if the two unsigned int are not the same.
    This macro prints out the actual values of the two 
    unsigned int.
    
    \param x an unsigned int
    \param y another unsigned int
*/
#define cester_assert_uint_ne(x,y) CESTER_CONCAT(cester_compare_uint, __internal_cester_assert_ne(x,y,%u))

/**
    Check if the a unsigned int is greater than the other.
    This macro prints out the actual values of the two 
    unsigned int.
    
    \param x an unsigned int
    \param y another unsigned int
*/
#define cester_assert_uint_gt(x,y) CESTER_CONCAT(cester_compare_uint, __internal_cester_assert_gt(x,y,%u))

/**
    Check if the a unsigned int is greater than or equal to the other.
    This macro prints out the actual values of the two 
    unsigned int.
    
    \param x an unsigned int
    \param y another unsigned int
*/
#define cester_assert_uint_ge(x,y) CESTER_CONCAT(cester_compare_uint, __internal_cester_assert_ge(x,y,%u))

/**
    Check if the a unsigned int is lesser than the other.
    This macro prints out the actual values of the two 
    unsigned int.
    
    \param x an unsigned int
    \param y another unsigned int
*/
#define cester_assert_uint_lt(x,y) CESTER_CONCAT(cester_compare_uint, __internal_cester_assert_lt(x,y,%u))

/**
    Check if the a unsigned int is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    unsigned int.
    
    \param x an unsigned int
    \param y another unsigned int
*/
#define cester_assert_uint_le(x,y) CESTER_CONCAT(cester_compare_uint, __internal_cester_assert_le(x,y,%u))

/**
    Compare two long using the provided operator
    This macro prints out the actual values of the two 
    long.
    
    \param w a long
    \param x the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param y another long
    \param z the string formated for output
*/
#define cester_assert_cmp_long(w,x,y,z) CESTER_CONCAT(cester_compare_long_pre_evaluated, __internal_cester_assert_cmp(w,x,y,z))

/**
    Check if the two long are the same.
    This macro prints out the actual values of the two 
    long.
    
    \param x a long
    \param y another long
*/
#define cester_assert_long_eq(x,y) CESTER_CONCAT(cester_compare_long, __internal_cester_assert_eq(x,y,%li))

/**
    Check if the two long are not the same.
    This macro prints out the actual values of the two 
    long.
    
    \param x a long
    \param y another long
*/
#define cester_assert_long_ne(x,y) CESTER_CONCAT(cester_compare_long, __internal_cester_assert_ne(x,y,%li))

/**
    Check if the a long is greater than the other.
    This macro prints out the actual values of the two 
    long.
    
    \param x a long
    \param y another long
*/
#define cester_assert_long_gt(x,y) CESTER_CONCAT(cester_compare_long, __internal_cester_assert_gt(x,y,%li))

/**
    Check if the a long is greater than or equal to the other.
    This macro prints out the actual values of the two 
    long.
    
    \param x a long
    \param y another long
*/
#define cester_assert_long_ge(x,y) CESTER_CONCAT(cester_compare_long, __internal_cester_assert_ge(x,y,%li))

/**
    Check if the a long is lesser than the other.
    This macro prints out the actual values of the two 
    long.
    
    \param x a long
    \param y another long
*/
#define cester_assert_long_lt(x,y) CESTER_CONCAT(cester_compare_long, __internal_cester_assert_lt(x,y,%li))

/**
    Check if the a long is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    long.
    
    \param x a long
    \param y another long
*/
#define cester_assert_long_le(x,y) CESTER_CONCAT(cester_compare_long, __internal_cester_assert_le(x,y,%li))

/**
    Compare two unsigned long using the provided operator
    This macro prints out the actual values of the two 
    unsigned long.
    
    \param w a unsigned long
    \param x the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param y another unsigned long
    \param z the string formated for output
*/
#define cester_assert_cmp_ulong(w,x,y,z) CESTER_CONCAT(cester_compare_ulong_pre_evaluated, __internal_cester_assert_cmp(w,x,y,z))

/**
    Check if the two unsigned long are the same.
    This macro prints out the actual values of the two 
    unsigned long.
    
    \param x a unsigned long
    \param y another unsigned long
*/
#define cester_assert_ulong_eq(x,y) CESTER_CONCAT(cester_compare_ulong, __internal_cester_assert_eq(x,y,%lu))

/**
    Check if the two unsigned long are not the same.
    This macro prints out the actual values of the two 
    unsigned long.
    
    \param x a unsigned long
    \param y another unsigned long
*/
#define cester_assert_ulong_ne(x,y) CESTER_CONCAT(cester_compare_ulong, __internal_cester_assert_ne(x,y,%lu))

/**
    Check if the a unsigned long is greater than the other.
    This macro prints out the actual values of the two 
    unsigned long.
    
    \param x a unsigned long
    \param y another unsigned long
*/
#define cester_assert_ulong_gt(x,y) CESTER_CONCAT(cester_compare_ulong, __internal_cester_assert_gt(x,y,%lu))

/**
    Check if the a unsigned long is greater than or equal to the other.
    This macro prints out the actual values of the two 
    unsigned long.
    
    \param x a unsigned long
    \param y another unsigned long
*/
#define cester_assert_ulong_ge(x,y) CESTER_CONCAT(cester_compare_ulong, __internal_cester_assert_ge(x,y,%lu))

/**
    Check if the a unsigned long is lesser than the other.
    This macro prints out the actual values of the two 
    unsigned long.
    
    \param x a unsigned long
    \param y another unsigned long
*/
#define cester_assert_ulong_lt(x,y) CESTER_CONCAT(cester_compare_ulong, __internal_cester_assert_lt(x,y,%lu))

/**
    Check if the a unsigned long is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    unsigned long.
    
    \param x a unsigned long
    \param y another unsigned long
*/
#define cester_assert_ulong_le(x,y) CESTER_CONCAT(cester_compare_ulong, __internal_cester_assert_le(x,y,%lu))

/**
    Compare two long long using the provided operator
    This macro prints out the actual values of the two 
    long long.
    
    \param w a long long
    \param x the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param y another long long
    \param z the string formated for output
*/
#define cester_assert_cmp_llong(w,x,y,z) CESTER_CONCAT(cester_compare_llong_pre_evaluated, __internal_cester_assert_cmp(w,x,y,z))

/**
    Check if the two long long are the same.
    This macro prints out the actual values of the two 
    long long.
    
    \param x a long long
    \param y another long long
*/
#ifndef __CESTER_STDC_VERSION__
#define cester_assert_llong_eq(x,y) CESTER_CONCAT(cester_compare_llong, __internal_cester_assert_eq(x,y,%li))
#else
#define cester_assert_llong_eq(x,y) CESTER_CONCAT(cester_compare_llong, __internal_cester_assert_eq(x,y,%lli))
#endif

/**
    Check if the two long long are not the same.
    This macro prints out the actual values of the two 
    long long.
    
    \param x a long long
    \param y another long long
*/
#ifndef __CESTER_STDC_VERSION__
#define cester_assert_llong_ne(x,y) CESTER_CONCAT(cester_compare_llong, __internal_cester_assert_ne(x,y,%li))
#else
#define cester_assert_llong_ne(x,y) CESTER_CONCAT(cester_compare_llong, __internal_cester_assert_ne(x,y,%lli))
#endif

/**
    Check if the a long long is greater than the other.
    This macro prints out the actual values of the two 
    long long.
    
    \param x a long long
    \param y another long long
*/
#ifndef __CESTER_STDC_VERSION__
#define cester_assert_llong_gt(x,y) CESTER_CONCAT(cester_compare_llong, __internal_cester_assert_gt(x,y,%li))
#else
#define cester_assert_llong_gt(x,y) CESTER_CONCAT(cester_compare_llong, __internal_cester_assert_gt(x,y,%lli))
#endif

/**
    Check if the a long long is greater than or equal to the other.
    This macro prints out the actual values of the two 
    long long.
    
    \param x a long long
    \param y another long long
*/
#ifndef __CESTER_STDC_VERSION__
#define cester_assert_llong_ge(x,y) CESTER_CONCAT(cester_compare_llong, __internal_cester_assert_ge(x,y,%li))
#else
#define cester_assert_llong_ge(x,y) CESTER_CONCAT(cester_compare_llong, __internal_cester_assert_ge(x,y,%lli))
#endif

/**
    Check if the a long long is lesser than the other.
    This macro prints out the actual values of the two 
    long long.
    
    \param x a long long
    \param y another long long
*/
#ifndef __CESTER_STDC_VERSION__
#define cester_assert_llong_lt(x,y) CESTER_CONCAT(cester_compare_llong, __internal_cester_assert_lt(x,y,%li))
#else
#define cester_assert_llong_lt(x,y) CESTER_CONCAT(cester_compare_llong, __internal_cester_assert_lt(x,y,%lli))
#endif

/**
    Check if the a long long is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    long long.
    
    \param x a long long
    \param y another long long
*/
#ifndef __CESTER_STDC_VERSION__
#define cester_assert_llong_le(x,y) CESTER_CONCAT(cester_compare_llong, __internal_cester_assert_ge(x,y,%li))
#else
#define cester_assert_llong_le(x,y) CESTER_CONCAT(cester_compare_llong, __internal_cester_assert_ge(x,y,%lli))
#endif

/**
    Compare two unsigned long long using the provided operator
    This macro prints out the actual values of the two 
    unsigned long long.
    
    \param w a unsigned long long
    \param x the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param y another unsigned long long
    \param z the string formated for output
*/
#define cester_assert_cmp_ullong(w,x,y,z) CESTER_CONCAT(cester_compare_ullong_pre_evaluated, __internal_cester_assert_cmp(w,x,y,z))

/**
    Check if the two unsigned long long are the same.
    This macro prints out the actual values of the two 
    unsigned long long.
    
    \param x a unsigned long long
    \param y another unsigned long long
*/
#define cester_assert_ullong_eq(x,y) CESTER_CONCAT(cester_compare_ullong, __internal_cester_assert_eq(x,y,%llu))

/**
    Check if the two unsigned long long are not the same.
    This macro prints out the actual values of the two 
    unsigned long long.
    
    \param x a unsigned long long
    \param y another unsigned long long
*/
#define cester_assert_ullong_ne(x,y) CESTER_CONCAT(cester_compare_ullong, __internal_cester_assert_ne(x,y,%llu))

/**
    Check if the a unsigned long long is greater than the other.
    This macro prints out the actual values of the two 
    unsigned long long.
    
    \param x a unsigned long long
    \param y another unsigned long long
*/
#define cester_assert_ullong_gt(x,y) CESTER_CONCAT(cester_compare_ullong, __internal_cester_assert_gt(x,y,%llu))

/**
    Check if the a unsigned long long is greater than or equal to the other.
    This macro prints out the actual values of the two 
    unsigned long long.
    
    \param x a unsigned long long
    \param y another unsigned long long
*/
#define cester_assert_ullong_ge(x,y) CESTER_CONCAT(cester_compare_ullong, __internal_cester_assert_ge(x,y,%llu))

/**
    Check if the a unsigned long long is lesser than the other.
    This macro prints out the actual values of the two 
    unsigned long long.
    
    \param x a unsigned long long
    \param y another unsigned long long
*/
#define cester_assert_ullong_lt(x,y) CESTER_CONCAT(cester_compare_ullong, __internal_cester_assert_lt(x,y,%llu))

/**
    Check if the a unsigned long long is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    unsigned long long.
    
    \param x a unsigned long long
    \param y another unsigned long long
*/
#define cester_assert_ullong_le(x,y) CESTER_CONCAT(cester_compare_ullong, __internal_cester_assert_le(x,y,%llu))

/**
    Compare two float using the provided operator
    This macro prints out the actual values of the two 
    float.
    
    \param w a float
    \param x the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param y another float
    \param z the string formated for output
*/
#define cester_assert_cmp_float(w,x,y,z) CESTER_CONCAT(cester_compare_float_pre_evaluated, __internal_cester_assert_cmp(w,x,y,z))

/**
    Check if the two float are the same.
    This macro prints out the actual values of the two 
    float.
    
    \param x a float
    \param y another float
*/
#define cester_assert_float_eq(x,y) CESTER_CONCAT(cester_compare_float, __internal_cester_assert_eq(x,y,%f))

/**
    Check if the two float are not the same.
    This macro prints out the actual values of the two 
    float.
    
    \param x a float
    \param y another float
*/
#define cester_assert_float_ne(x,y) CESTER_CONCAT(cester_compare_float, __internal_cester_assert_ne(x,y,%f))

/**
    Check if the a float is greater than the other.
    This macro prints out the actual values of the two 
    float.
    
    \param x a float
    \param y another float
*/
#define cester_assert_float_gt(x,y) CESTER_CONCAT(cester_compare_float, __internal_cester_assert_gt(x,y,%f))

/**
    Check if the a float is greater than or equal to the other.
    This macro prints out the actual values of the two 
    float.
    
    \param x a float
    \param y another float
*/
#define cester_assert_float_ge(x,y) CESTER_CONCAT(cester_compare_float, __internal_cester_assert_ge(x,y,%f))

/**
    Check if the a float is lesser than the other.
    This macro prints out the actual values of the two 
    float.
    
    \param x a float
    \param y another float
*/
#define cester_assert_float_lt(x,y) CESTER_CONCAT(cester_compare_float, __internal_cester_assert_lt(x,y,%f))

/**
    Check if the a float is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    float.
    
    \param x a float
    \param y another float
*/
#define cester_assert_float_le(x,y) CESTER_CONCAT(cester_compare_float, __internal_cester_assert_le(x,y,%f))

/**
    Compare two double using the provided operator
    This macro prints out the actual values of the two 
    double.
    
    \param w a double
    \param x the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param y another double
    \param z the string formated for output
*/
#define cester_assert_cmp_double(w,x,y,z) CESTER_CONCAT(cester_compare_double_pre_evaluated, __internal_cester_assert_cmp(w,x,y,z))

/**
    Check if the two double are the same.
    This macro prints out the actual values of the two 
    double.
    
    \param x a double
    \param y another double
*/
#define cester_assert_double_eq(x,y) CESTER_CONCAT(cester_compare_double, __internal_cester_assert_eq(x,y,%lf))

/**
    Check if the two double are not the same.
    This macro prints out the actual values of the two 
    double.
    
    \param x a double
    \param y another double
*/
#define cester_assert_double_ne(x,y) CESTER_CONCAT(cester_compare_double, __internal_cester_assert_ne(x,y,%lf))

/**
    Check if the a double is greater than the other.
    This macro prints out the actual values of the two 
    double.
    
    \param x a double
    \param y another double
*/
#define cester_assert_double_gt(x,y) CESTER_CONCAT(cester_compare_double, __internal_cester_assert_gt(x,y,%lf))

/**
    Check if the a double is greater than or equal to the other.
    This macro prints out the actual values of the two 
    double.
    
    \param x a double
    \param y another double
*/
#define cester_assert_double_ge(x,y) CESTER_CONCAT(cester_compare_double, __internal_cester_assert_ge(x,y,%lf))

/**
    Check if the a double is lesser than the other.
    This macro prints out the actual values of the two 
    double.
    
    \param x a double
    \param y another double
*/
#define cester_assert_double_lt(x,y) CESTER_CONCAT(cester_compare_double, __internal_cester_assert_lt(x,y,%lf))

/**
    Check if the a double is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    double.
    
    \param x a double
    \param y another double
*/
#define cester_assert_double_le(x,y) CESTER_CONCAT(cester_compare_double, __internal_cester_assert_le(x,y,%lf))

/**
    Compare two long double using the provided operator
    This macro prints out the actual values of the two 
    long double.
    
    \param w a long double
    \param x the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param y another long double
    \param z the string formated for output
*/
#define cester_assert_cmp_ldouble(w,x,y,z) CESTER_CONCAT(cester_compare_ldouble_pre_evaluated, __internal_cester_assert_cmp(w,x,y,z))

/**
    Check if the two long double are the same.
    This macro prints out the actual values of the two 
    long double.
    
    \param x a long double
    \param y another long double
*/
#define cester_assert_ldouble_eq(x,y) CESTER_CONCAT(cester_compare_ldouble, __internal_cester_assert_eq(x,y,%e))

/**
    Check if the two long double are not the same.
    This macro prints out the actual values of the two 
    long double.
    
    \param x a long double
    \param y another long double
*/
#define cester_assert_ldouble_ne(x,y) CESTER_CONCAT(cester_compare_ldouble, __internal_cester_assert_ne(x,y,%e))

/**
    Check if the a long double is greater than the other.
    This macro prints out the actual values of the two 
    long double.
    
    \param x a long double
    \param y another long double
*/
#define cester_assert_ldouble_gt(x,y) CESTER_CONCAT(cester_compare_ldouble, __internal_cester_assert_gt(x,y,%e))

/**
    Check if the a long double is greater than or equal to the other.
    This macro prints out the actual values of the two 
    long double.
    
    \param x a long double
    \param y another long double
*/
#define cester_assert_ldouble_ge(x,y) CESTER_CONCAT(cester_compare_ldouble, __internal_cester_assert_ge(x,y,%e))

/**
    Check if the a long double is lesser than the other.
    This macro prints out the actual values of the two 
    long double.
    
    \param x a long double
    \param y another long double
*/
#define cester_assert_ldouble_lt(x,y) CESTER_CONCAT(cester_compare_ldouble, __internal_cester_assert_lt(x,y,%e))

/**
    Check if the a long double is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    long double.
    
    \param x a long double
    \param y another long double
*/
#define cester_assert_ldouble_le(x,y) CESTER_CONCAT(cester_compare_ldouble, __internal_cester_assert_le(x,y,%e))

static __CESTER_INLINE__ void cester_evaluate_expression(unsigned eval_result, char const* const expression, char const* const file_path, unsigned const line_num) {
    if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "# ");
        
    } else if (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "    - ");
    }
    if (eval_result == 0) {
        superTestInstance.current_execution_status = CESTER_RESULT_FAILURE;
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "EvaluationError ");
    } else if (superTestInstance.verbose_level >= 1 && superTestInstance.print_error_only == 0) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "Passed ");
    }
    /*my brain failed to work in this if condition. I beleive the if condition can be simplified*/
    if ((superTestInstance.verbose_level >= 1 || eval_result == 0) && ((superTestInstance.print_error_only == 1 && eval_result == 0) || superTestInstance.print_error_only == 0)) {
        cester_print_assertion(expression, file_path, line_num);
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "\n");
    }
}

static __CESTER_INLINE__ void cester_evaluate_expect_actual(unsigned eval_result, unsigned expecting, char const* const expected, char const* const actual, 
                                                char const* const file_path, unsigned const line_num) {
                                                    
    
    if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "# ");
        
    } else if (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "    - ");
    }
    if (eval_result == 0) {
        superTestInstance.current_execution_status = CESTER_RESULT_FAILURE;
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "AssertionError ");
    } else if (superTestInstance.verbose_level >= 1 && superTestInstance.print_error_only == 0) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "Passed ");
    }
    if ((superTestInstance.verbose_level >= 1 || eval_result == 0) && ((superTestInstance.print_error_only == 1 && eval_result == 0) || superTestInstance.print_error_only == 0)) {
        cester_print_expect_actual(expecting, expected, actual, file_path, line_num);
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "\n");
    }
}

static __CESTER_INLINE__ void cester_evaluate_expect_actual_str(char const* const expected_in, char const* const actual_in, char const* const expected_expr, 
                                                                char const* const actual_expr, unsigned expecting, char const* const file_path, unsigned const line_num) {
                                                                    
    unsigned eval_result;
    char *expected;
    char *actual;
    
    
    expected = (char*) "";
    actual = (char*) "";
    eval_result = cester_string_equals((char*)expected_in, (char*)actual_in);
    if (superTestInstance.verbose_level >= 3) {
        cester_concat_str(&expected, expected_expr);
        cester_concat_str(&actual, actual_expr);
        
        cester_concat_char(&expected, '=');
        cester_concat_char(&actual, '=');
    }
    cester_concat_str(&expected, expected_in);
    cester_concat_str(&actual, actual_in);
    
    if (eval_result != expecting) {
        superTestInstance.current_execution_status = CESTER_RESULT_FAILURE;
        if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1) {
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "# ");
            
        } else if (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1) {
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "    - ");
        }
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "AssertionError ");
    } else if (superTestInstance.verbose_level >= 1 && superTestInstance.print_error_only == 0) {
        if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1) {
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "# ");
            
        } else if (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1) {
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "    - ");
        }
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "Passed ");
    }  
    if ((superTestInstance.verbose_level >= 1 || eval_result != expecting) && ((superTestInstance.print_error_only == 1 && eval_result != expecting) || superTestInstance.print_error_only == 0)) {
        cester_print_expect_actual(expecting, expected, actual, file_path, line_num);
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "\n");
    }
    free(expected);
    free(actual);
}

static __CESTER_INLINE__ void cester_evaluate_expect_actual_ptr(void* ptr1, void* ptr2, char const* const expected_expr, char const* const actual_expr,
                                                                unsigned expecting, char const* const file_path, unsigned const line_num) {
                                                                    
    unsigned eval_result;
    char *expected;
    char *actual;
    
    eval_result = ptr1 == ptr2; 
    if (superTestInstance.verbose_level >= 3) {
        expected = (char*) "";
        actual = (char*) "";
        cester_concat_str(&expected, expected_expr);
        cester_concat_str(&actual, actual_expr);
        
        cester_concat_char(&expected, '=');
        cester_concat_char(&actual, '=');
        
        cester_concat_ptr(&expected, ptr1);
        cester_concat_ptr(&actual, ptr2);
    } else {
        cester_ptr_to_str(&expected, ptr1);
        cester_ptr_to_str(&actual, ptr2);
    }
    if (eval_result != expecting) {
        superTestInstance.current_execution_status = CESTER_RESULT_FAILURE;
        if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1) {
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "# ");
            
        } else if (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1) {
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "    - ");
        }
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "AssertionError ");
    } else if (superTestInstance.verbose_level >= 1 && superTestInstance.print_error_only == 0) {
        if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1) {
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "# ");
            
        } else if (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1) {
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "    - ");
        }
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "Passed ");
    }  
    if ((superTestInstance.verbose_level >= 1 || eval_result != expecting) && ((superTestInstance.print_error_only == 1 && eval_result != expecting) || superTestInstance.print_error_only == 0)) {
        cester_print_expect_actual(expecting, expected, actual, file_path, line_num);
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "\n");
    }
    free(expected);
    free(actual);
}

/*
    Use the cester_assertion_caparator type to determine what comparission 
    operation to perform on the two values
*/
#define CESTER_INTERNAL_EVALUATE(comparator_type, x, y, result) {\
    if (comparator_type == CESTER_COMPARATOR_EQUAL) {\
        result = (x == y);\
    } else if (comparator_type == CESTER_COMPARATOR_NOT_EQUAL) {\
        result = (x != y);\
    } else if (comparator_type == CESTER_COMPARATOR_GREATER_THAN) {\
        result = (x > y);\
    } else if (comparator_type == CESTER_COMPARATOR_GREATER_THAN_OR_EQUAL) {\
        result = (x >= y);\
    } else if (comparator_type == CESTER_COMPARATOR_LESSER_THAN) {\
        result = (x < y);\
    } else if (comparator_type == CESTER_COMPARATOR_LESSER_THAN_OR_EQUAL) {\
        result = (x <= y);\
    } else {\
        result = (x == y);\
    }\
}

static __CESTER_INLINE__ void cester_compare_char_pre_evaluated(int eval_result, char const* const expr, char first, char second, char const* const op, char const* const file_path, unsigned const line_num) {
    char expression[2048] = "";
    cester_sprintf3(expression, 2048, expr, second, op, first);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_char(enum cester_assertion_caparator comparator_type, char const* const expr, char first, char second, char const* const op, char const* const file_path, unsigned const line_num) {
    int eval_result = 0;
    CESTER_INTERNAL_EVALUATE(comparator_type, first, second, eval_result);
    cester_compare_char_pre_evaluated(eval_result, expr, first, second, op, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_uchar_pre_evaluated(int eval_result, char const* const expr, unsigned char first, unsigned char second, char const* const op, char const* const file_path, unsigned const line_num) {
    char expression[2048] = "";
    cester_sprintf3(expression, 2048, expr, second, op, first);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_uchar(enum cester_assertion_caparator comparator_type, char const* const expr, unsigned char first, unsigned char second, char const* const op, char const* const file_path, unsigned const line_num) {
    int eval_result = 0;
    CESTER_INTERNAL_EVALUATE(comparator_type, first, second, eval_result);
    cester_compare_uchar_pre_evaluated(eval_result, expr, first, second, op, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_int_pre_evaluated(int eval_result, char const* const expr, int first, int second, char const* const op, char const* const file_path, unsigned const line_num) {
    char expression[2048] = "";
    cester_sprintf3(expression, 2048, expr, second, op, first);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_int(enum cester_assertion_caparator comparator_type, char const* const expr, int first, int second, char const* const op, char const* const file_path, unsigned const line_num) {
    int eval_result = 0;
    CESTER_INTERNAL_EVALUATE(comparator_type, first, second, eval_result);
    cester_compare_int_pre_evaluated(eval_result, expr, first, second, op, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_uint_pre_evaluated(int eval_result, char const* const expr, unsigned int first, unsigned int second, char const* const op, char const* const file_path, unsigned const line_num) {
    char expression[2048] = "";
    cester_sprintf3(expression, 2048, expr, second, op, first);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_uint(enum cester_assertion_caparator comparator_type, char const* const expr, unsigned int first, unsigned int second, char const* const op, char const* const file_path, unsigned const line_num) {
    int eval_result = 0;
    CESTER_INTERNAL_EVALUATE(comparator_type, first, second, eval_result);
    cester_compare_uint_pre_evaluated(eval_result, expr, first, second, op, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_short_pre_evaluated(int eval_result, char const* const expr, short first, short second, char const* const op, char const* const file_path, unsigned const line_num) {
    char expression[2048] = "";
    cester_sprintf3(expression, 2048, expr, second, op, first);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_short(enum cester_assertion_caparator comparator_type, char const* const expr, short first, short second, char const* const op, char const* const file_path, unsigned const line_num) {
    int eval_result = 0;
    CESTER_INTERNAL_EVALUATE(comparator_type, first, second, eval_result);
    cester_compare_short_pre_evaluated(eval_result, expr, first, second, op, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_ushort_pre_evaluated(int eval_result, char const* const expr, unsigned short first, unsigned short second, char const* const op, char const* const file_path, unsigned const line_num) {
    char expression[2048] = "";
    cester_sprintf3(expression, 2048, expr, second, op, first);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_ushort(enum cester_assertion_caparator comparator_type, char const* const expr, unsigned short first, unsigned short second, char const* const op, char const* const file_path, unsigned const line_num) {
    int eval_result = 0;
    CESTER_INTERNAL_EVALUATE(comparator_type, first, second, eval_result);
    cester_compare_ushort_pre_evaluated(eval_result, expr, first, second, op, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_long_pre_evaluated(int eval_result, char const* const expr, long first, long second, char const* const op, char const* const file_path, unsigned const line_num) {
    char expression[2048] = "";
    cester_sprintf3(expression, 2048, expr, second, op, first);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_long(enum cester_assertion_caparator comparator_type, char const* const expr, long first, long second, char const* const op, char const* const file_path, unsigned const line_num) {
    int eval_result = 0;
    CESTER_INTERNAL_EVALUATE(comparator_type, first, second, eval_result);
    cester_compare_long_pre_evaluated(eval_result, expr, first, second, op, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_ulong_pre_evaluated(int eval_result, char const* const expr, unsigned long first, unsigned long second, char const* const op, char const* const file_path, unsigned const line_num) {
    char expression[2048] = "";
    cester_sprintf3(expression, 2048, expr, second, op, first);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_ulong(enum cester_assertion_caparator comparator_type, char const* const expr, unsigned long first, unsigned long second, char const* const op, char const* const file_path, unsigned const line_num) {
    int eval_result = 0;
    CESTER_INTERNAL_EVALUATE(comparator_type, first, second, eval_result);
    cester_compare_ulong_pre_evaluated(eval_result, expr, first, second, op, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_llong_pre_evaluated(int eval_result, char const* const expr, __CESTER_LONG_LONG__ first, __CESTER_LONG_LONG__ second, char const* const op, char const* const file_path, unsigned const line_num) {
    char expression[2048] = "";
    cester_sprintf3(expression, 2048, expr, second, op, first);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_llong(enum cester_assertion_caparator comparator_type, char const* const expr, __CESTER_LONG_LONG__ first, __CESTER_LONG_LONG__ second, char const* const op, char const* const file_path, unsigned const line_num) {
    int eval_result = 0;
    CESTER_INTERNAL_EVALUATE(comparator_type, first, second, eval_result);
    cester_compare_llong_pre_evaluated(eval_result, expr, first, second, op, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_ullong_pre_evaluated(int eval_result, char const* const expr, unsigned __CESTER_LONG_LONG__ first, unsigned __CESTER_LONG_LONG__ second, char const* const op, char const* const file_path, unsigned const line_num) {
    char expression[2048] = "";
    cester_sprintf3(expression, 2048, expr, second, op, first);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_ullong(enum cester_assertion_caparator comparator_type, char const* const expr, unsigned __CESTER_LONG_LONG__ first, unsigned __CESTER_LONG_LONG__ second, char const* const op, char const* const file_path, unsigned const line_num) {
    int eval_result = 0;
    CESTER_INTERNAL_EVALUATE(comparator_type, first, second, eval_result);
    cester_compare_ullong_pre_evaluated(eval_result, expr, first, second, op, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_float_pre_evaluated(int eval_result, char const* const expr, float first, float second, char const* const op, char const* const file_path, unsigned const line_num) {
    char expression[2048] = "";
    cester_sprintf3(expression, 2048, expr, second, op, first);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_float(enum cester_assertion_caparator comparator_type, char const* const expr, float first, float second, char const* const op, char const* const file_path, unsigned const line_num) {
    int eval_result = 0;
    CESTER_INTERNAL_EVALUATE(comparator_type, first, second, eval_result);
    cester_compare_float_pre_evaluated(eval_result, expr, first, second, op, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_double_pre_evaluated(int eval_result, char const* const expr, double first, double second, char const* const op, char const* const file_path, unsigned const line_num) {
    char expression[2048] = "";
    cester_sprintf3(expression, 2048, expr, second, op, first);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_double(enum cester_assertion_caparator comparator_type, char const* const expr, double first, double second, char const* const op, char const* const file_path, unsigned const line_num) {
    int eval_result = 0;
    CESTER_INTERNAL_EVALUATE(comparator_type, first, second, eval_result);
    cester_compare_double_pre_evaluated(eval_result, expr, first, second, op, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_ldouble_pre_evaluated(int eval_result, char const* const expr, long double first, long double second, char const* const op, char const* const file_path, unsigned const line_num) {
    char expression[2048] = "";
    cester_sprintf3(expression, 2048, expr, second, op, first);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static __CESTER_INLINE__ void cester_compare_ldouble(enum cester_assertion_caparator comparator_type, char const* const expr, long double first, long double second, char const* const op, char const* const file_path, unsigned const line_num) {
    int eval_result = 0;
    CESTER_INTERNAL_EVALUATE(comparator_type, first, second, eval_result);
    cester_compare_ldouble_pre_evaluated(eval_result, expr, first, second, op, file_path, line_num);
}

#ifndef __CESTER_STDC_VERSION__
/**
    Create a test case, this uses the first arguments as the test
    case name and identifier and the body of the test.
*/
#define CESTER_TEST(x,y,z) static void cester_test_##x(TestInstance* y);

/**
    Create a test case that has not been implemented, It is skipped and
    generates warning. This macro will print message in output to remind
    the developer of it implementation. Good for TDD.

    This uses the first arguments as the test case name and identifier
    and the body of the test.
*/
#define CESTER_TODO_TEST(x,y,z) static void cester_test_##x(TestInstance* y);

/**
    Create a test case that is not run.

    This uses the first arguments as the test case name and identifier
    and the body of the test.
*/
#define CESTER_SKIP_TEST(x,y,z) static void cester_test_##x(TestInstance* y);

/**
    The function that would be invoked once before running
    any test in the test file. You can only have one of this function
    in a test file.
*/
#define CESTER_BEFORE_ALL(x,y) void cester_before_all_test(TestInstance* x);

/**
    The function that would be invoked before each test. You can only 
    have one of this function in a test file.
*/
#define CESTER_BEFORE_EACH(w,x,y,z) void cester_before_each_test(TestInstance* w, char * const x, unsigned y);

/**
    The function that would be invoked once after running 
    all the tests in the test file. You can only have one of this function 
    in a test file.
*/
#define CESTER_AFTER_ALL(x,y) void cester_after_all_test(TestInstance* x);

/**
    The functions that would be invoked after each test is 
    ran. You can only have one of this function in a test file.
*/
#define CESTER_AFTER_EACH(w,x,y,z) void cester_after_each_test(TestInstance* w, char * const x, unsigned y);

/**
    Set the options for cester, anything in this macro will be executed before 
    the tests starts running.
*/
#define CESTER_OPTIONS(x) void cester_options_before_main();

/**
    Absorb the statements and logic in a test file before re including 
    the __BASE_FILE__. This way code can be written in the global space of the 
    test file. 
    
    \note do not put other CESTER_ macros inside this one, this should contain 
    only your C or C++ code.
*/
#define CESTER_BODY(x)

/**
    A multiline comment macro everything in the macro is printed 
    out at the beginning of the test.

    Comma in the content will cause issue in the macro expansion 
    when the code is compiled with C version less than C99.

    It should not begin or end in quote, escape characters is 
    expanded when printed out
*/
#define CESTER_COMMENT(x) void cester_test_file_comment_function();

#ifndef CESTER_NO_MOCK
/**
    Mock a function to just return a value. the first argument is the name 
    of the function to mock, the second argument is the return type of the 
    function, the third parameter is the value that is returned when the 
    function is called. 
    
    This still requires using the -Wl,--wrap option to wrap the parameter 
    to override the initial function. E.g. if the function `multiply_by` 
    is mocked the option `-Wl,--wrap=multiply_by` should be added during 
    compilation. 
    
    Th mocking features only works on GCC for now.
*/
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,z)  __attribute__((weak)) y x; y __real_##x;

/**

*/
#define CESTER_MOCK_FUNCTION(x,y,z) __attribute__((weak)) y x; extern y __real_##x;
#else 
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,z)
#define CESTER_MOCK_FUNCTION(x,y,z)
#endif

#else
    
#define CESTER_TEST(x,y,...) static void cester_test_##x(TestInstance* y);
#define CESTER_TODO_TEST(x,y,...) static void cester_test_##x(TestInstance* y);
#define CESTER_SKIP_TEST(x,y,...) static void cester_test_##x(TestInstance* y);
#define CESTER_BEFORE_ALL(x,...) void cester_before_all_test(TestInstance* x);
#define CESTER_BEFORE_EACH(w,x,y,...) void cester_before_each_test(TestInstance* w, char * const x, unsigned y);
#define CESTER_AFTER_ALL(x,...) void cester_after_all_test(TestInstance* x);
#define CESTER_AFTER_EACH(w,x,y,...) void cester_after_each_test(TestInstance* w, char * const x, unsigned y);
#define CESTER_OPTIONS(...) void cester_options_before_main();
#define CESTER_BODY(...)
#define CESTER_COMMENT(...) void cester_test_file_comment_function();
#ifndef CESTER_NO_MOCK
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,...)  __attribute__((weak)) y x; y __real_##x;
#define CESTER_MOCK_FUNCTION(x,y,...) __attribute__((weak)) y x; extern y __real_##x;
#else 
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,...)
#define CESTER_MOCK_FUNCTION(x,y,...)
#endif
#endif

#ifdef __BASE_FILE__
#ifdef __cplusplus
}
#endif
    #include __BASE_FILE__
#ifdef __cplusplus
extern "C" {
#endif
#else 
    
#endif

#undef CESTER_TEST
#undef CESTER_TODO_TEST
#undef CESTER_SKIP_TEST
#undef CESTER_BEFORE_ALL
#undef CESTER_BEFORE_EACH
#undef CESTER_AFTER_ALL
#undef CESTER_AFTER_EACH
#undef CESTER_OPTIONS
#undef CESTER_BODY
#undef CESTER_COMMENT
#undef CESTER_MOCK_SIMPLE_FUNCTION
#undef CESTER_MOCK_FUNCTION

#ifdef __CESTER_STDC_VERSION__
#ifndef CESTER_NO_TIME
#define CESTER_TEST(x,y,...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) #x, (cester_test_##x), CESTER_NULL, CESTER_NULL, CESTER_NORMAL_TEST },
#define CESTER_TODO_TEST(x,y,...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) #x, (cester_test_##x), CESTER_NULL, CESTER_NULL, CESTER_NORMAL_TODO_TEST },
#define CESTER_SKIP_TEST(x,y,...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) #x, (cester_test_##x), CESTER_NULL, CESTER_NULL, CESTER_NORMAL_SKIP_TEST },
#define CESTER_BEFORE_ALL(x,...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) "cester_before_all_test", (cester_before_all_test), CESTER_NULL, CESTER_NULL, CESTER_BEFORE_ALL_TEST },
#define CESTER_BEFORE_EACH(w,x,y,...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) (char*) "", (char*) "cester_before_each_test", CESTER_NULL, (cester_before_each_test), CESTER_NULL, CESTER_BEFORE_EACH_TEST },
#define CESTER_AFTER_ALL(x,...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) "cester_after_all_test", (cester_after_all_test), CESTER_NULL, CESTER_NULL, CESTER_AFTER_ALL_TEST },
#define CESTER_AFTER_EACH(w,x,y,...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) "cester_after_each_test", CESTER_NULL, (cester_after_each_test), CESTER_NULL, CESTER_AFTER_EACH_TEST },
#define CESTER_OPTIONS(...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) "cester_options_before_main", CESTER_NULL, CESTER_NULL, (cester_options_before_main), CESTER_OPTIONS_FUNCTION },
#define CESTER_COMMENT(...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) "cester_test_file_comment_function", CESTER_NULL, CESTER_NULL, (cester_test_file_comment_function), CESTER_TEST_FILE_COMMENT },
#else
#define CESTER_TEST(x,y,...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) #x, (cester_test_##x), CESTER_NULL, CESTER_NULL, CESTER_NORMAL_TEST },
#define CESTER_TODO_TEST(x,y,...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) #x, (cester_test_##x), CESTER_NULL, CESTER_NULL, CESTER_NORMAL_TODO_TEST },
#define CESTER_SKIP_TEST(x,y,...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) #x, (cester_test_##x), CESTER_NULL, CESTER_NULL, CESTER_NORMAL_SKIP_TEST },
#define CESTER_BEFORE_ALL(x,...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) "cester_before_all_test", (cester_before_all_test), CESTER_NULL, CESTER_NULL, CESTER_BEFORE_ALL_TEST },
#define CESTER_BEFORE_EACH(w,x,y,...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) (char*) "", (char*) "cester_before_each_test", CESTER_NULL, (cester_before_each_test), CESTER_NULL, CESTER_BEFORE_EACH_TEST },
#define CESTER_AFTER_ALL(x,...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) "cester_after_all_test", (cester_after_all_test), CESTER_NULL, CESTER_NULL, CESTER_AFTER_ALL_TEST },
#define CESTER_AFTER_EACH(w,x,y,...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) "cester_after_each_test", CESTER_NULL, (cester_after_each_test), CESTER_NULL, CESTER_AFTER_EACH_TEST },
#define CESTER_OPTIONS(...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) "cester_options_before_main", CESTER_NULL, CESTER_NULL, (cester_options_before_main), CESTER_OPTIONS_FUNCTION },
#define CESTER_COMMENT(...) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) "cester_test_file_comment_function", CESTER_NULL, CESTER_NULL, (cester_test_file_comment_function), CESTER_TEST_FILE_COMMENT },
#endif
#define CESTER_BODY(...)
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,...) 
#define CESTER_MOCK_FUNCTION(x,y,...)
#else
#ifndef CESTER_NO_TIME
#define CESTER_TEST(x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) #x, (cester_test_##x), CESTER_NULL, CESTER_NULL, CESTER_NORMAL_TEST },
#define CESTER_TODO_TEST(x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) #x, (cester_test_##x), CESTER_NULL, CESTER_NULL, CESTER_NORMAL_TODO_TEST },
#define CESTER_SKIP_TEST(x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) #x, (cester_test_##x), CESTER_NULL, CESTER_NULL, CESTER_NORMAL_SKIP_TEST },
#define CESTER_BEFORE_ALL(x,y) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) "cester_before_all_test", (cester_before_all_test), CESTER_NULL, CESTER_NULL, CESTER_BEFORE_ALL_TEST },
#define CESTER_BEFORE_EACH(w,x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) (char*) "", (char*) "cester_before_each_test", CESTER_NULL, (cester_before_each_test), CESTER_NULL, CESTER_BEFORE_EACH_TEST },
#define CESTER_AFTER_ALL(x,y) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) "cester_after_all_test", (cester_after_all_test), CESTER_NULL, CESTER_NULL, CESTER_AFTER_ALL_TEST },
#define CESTER_AFTER_EACH(w,x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) "cester_after_each_test", CESTER_NULL, (cester_after_each_test), CESTER_NULL, CESTER_AFTER_EACH_TEST },
#define CESTER_OPTIONS(x) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) "cester_options_before_main", CESTER_NULL, CESTER_NULL, (cester_options_before_main), CESTER_OPTIONS_FUNCTION },
#define CESTER_COMMENT(x) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, 0.000, 0.000, (char*) "", (char*) "cester_test_file_comment_function", CESTER_NULL, CESTER_NULL, (cester_test_file_comment_function), CESTER_TEST_FILE_COMMENT },
#else
#define CESTER_TEST(x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) #x, (cester_test_##x), CESTER_NULL, CESTER_NULL, CESTER_NORMAL_TEST },
#define CESTER_TODO_TEST(x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) #x, (cester_test_##x), CESTER_NULL, CESTER_NULL, CESTER_NORMAL_TODO_TEST },
#define CESTER_SKIP_TEST(x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) #x, (cester_test_##x), CESTER_NULL, CESTER_NULL, CESTER_NORMAL_SKIP_TEST },
#define CESTER_BEFORE_ALL(x,y) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) "cester_before_all_test", (cester_before_all_test), CESTER_NULL, CESTER_NULL, CESTER_BEFORE_ALL_TEST },
#define CESTER_BEFORE_EACH(w,x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) (char*) "", (char*) "cester_before_each_test", CESTER_NULL, (cester_before_each_test), CESTER_NULL, CESTER_BEFORE_EACH_TEST },
#define CESTER_AFTER_ALL(x,y) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) "cester_after_all_test", (cester_after_all_test), CESTER_NULL, CESTER_NULL, CESTER_AFTER_ALL_TEST },
#define CESTER_AFTER_EACH(w,x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) "cester_after_each_test", CESTER_NULL, (cester_after_each_test), CESTER_NULL, CESTER_AFTER_EACH_TEST },
#define CESTER_OPTIONS(x) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) "cester_options_before_main", CESTER_NULL, CESTER_NULL, (cester_options_before_main), CESTER_OPTIONS_FUNCTION },
#define CESTER_COMMENT(x) { CESTER_RESULT_UNKNOWN, __LINE__, CESTER_RESULT_SUCCESS, (char*) "", (char*) "cester_test_file_comment_function", CESTER_NULL, CESTER_NULL, (cester_test_file_comment_function), CESTER_TEST_FILE_COMMENT },
#endif
#define CESTER_BODY(x)
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,z) 
#define CESTER_MOCK_FUNCTION(x,y,z)
#endif

#ifdef __cplusplus
}
#endif
static TestCase cester_test_cases[] = {
#ifdef __BASE_FILE__
    #include __BASE_FILE__
#endif
#ifndef CESTER_NO_TIME
{ CESTER_RESULT_UNKNOWN, 0, CESTER_RESULT_SUCCESS, 0.000, 0.000, CESTER_NULL, CESTER_NULL, CESTER_NULL, CESTER_NULL, CESTER_NULL, CESTER_TESTS_TERMINATOR }
#else
{ CESTER_RESULT_UNKNOWN, 0, CESTER_RESULT_SUCCESS, CESTER_NULL, CESTER_NULL, CESTER_NULL, CESTER_NULL, CESTER_NULL, CESTER_TESTS_TERMINATOR }
#endif
};
#ifdef __cplusplus
extern "C" {
#endif

#undef CESTER_TEST
#undef CESTER_TODO_TEST
#undef CESTER_SKIP_TEST
#undef CESTER_BEFORE_ALL
#undef CESTER_BEFORE_EACH
#undef CESTER_AFTER_ALL
#undef CESTER_AFTER_EACH
#undef CESTER_OPTIONS
#undef CESTER_BODY
#undef CESTER_COMMENT
#undef CESTER_MOCK_SIMPLE_FUNCTION
#undef CESTER_MOCK_FUNCTION

#ifdef __CESTER_STDC_VERSION__
#define CESTER_TEST(x,y,...) static void cester_test_##x(TestInstance* y) { __VA_ARGS__  } 
#define CESTER_TODO_TEST(x,y,...) static void cester_test_##x(TestInstance* y) { }
#define CESTER_SKIP_TEST(x,y,...) static void cester_test_##x(TestInstance* y) { __VA_ARGS__ } 
#define CESTER_BEFORE_ALL(x,...) void cester_before_all_test(TestInstance* x) { __VA_ARGS__ CESTER_NO_ISOLATION(); } 
#define CESTER_BEFORE_EACH(w,x,y,...) void cester_before_each_test(TestInstance* w, char * const x, unsigned y) { __VA_ARGS__ CESTER_NO_ISOLATION(); }
#define CESTER_AFTER_ALL(x,...) void cester_after_all_test(TestInstance* x) { __VA_ARGS__ CESTER_NO_ISOLATION(); }
#define CESTER_AFTER_EACH(w,x,y,...) void cester_after_each_test(TestInstance* w, char * const x, unsigned y) { __VA_ARGS__ CESTER_NO_ISOLATION(); }
#define CESTER_OPTIONS(...) void cester_options_before_main() { __VA_ARGS__ }
#define CESTER_BODY(...) __VA_ARGS__
#define CESTER_COMMENT(...) void cester_test_file_comment_function() { if (cester_string_equals(superTestInstance.output_format, (char*) "text") == 1) { CESTER_DELEGATE_FPRINT_STR((default_color), "\n"); CESTER_DELEGATE_FPRINT_STR((default_color), #__VA_ARGS__); CESTER_DELEGATE_FPRINT_STR((default_color), "\n"); } }
#ifndef CESTER_NO_MOCK
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,...) y __wrap_##x { return __VA_ARGS__; }
#define CESTER_MOCK_FUNCTION(x,y,...) y __wrap_##x { __VA_ARGS__ }
#else
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,...) 
#define CESTER_MOCK_FUNCTION(x,y,...) 
#endif

#else
    
#define CESTER_TEST(x,y,z) static void cester_test_##x(TestInstance* y) { z } 
#define CESTER_TODO_TEST(x,y,z) static void cester_test_##x(TestInstance* y) { }
#define CESTER_SKIP_TEST(x,y,z) static void cester_test_##x(TestInstance* y) { z } 
#define CESTER_BEFORE_ALL(x,y) void cester_before_all_test(TestInstance* x) { y CESTER_NO_ISOLATION(); } 
#define CESTER_BEFORE_EACH(w,x,y,z) void cester_before_each_test(TestInstance* w, char * const x, unsigned y) { z CESTER_NO_ISOLATION(); }
#define CESTER_AFTER_ALL(x,y) void cester_after_all_test(TestInstance* x) { y CESTER_NO_ISOLATION(); }
#define CESTER_AFTER_EACH(w,x,y,z) void cester_after_each_test(TestInstance* w, char * const x, unsigned y) { z CESTER_NO_ISOLATION(); }
#define CESTER_OPTIONS(x) void cester_options_before_main() { x }
#define CESTER_BODY(x) x
#define CESTER_COMMENT(x) void cester_test_file_comment_function() { if (cester_string_equals(superTestInstance.output_format, (char*) "text") == 1) { CESTER_DELEGATE_FPRINT_STR((default_color), "\n"); CESTER_DELEGATE_FPRINT_STR((default_color), #x); CESTER_DELEGATE_FPRINT_STR((default_color), "\n"); } }
#ifndef CESTER_NO_MOCK
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,z) y __wrap_##x { return z; }
#define CESTER_MOCK_FUNCTION(x,y,z) y __wrap_##x { z }
#else
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,z) 
#define CESTER_MOCK_FUNCTION(x,y,z) 
#endif
#endif

/**
    Manually register a test case in situation where the the test 
    are not auto detected or selected test cases want to be run. 
    
    If a test is registered manually all auto detected test will not 
    be executed. 
*/
#define CESTER_REGISTER_TEST(x) cester_register_test((char*)#x, (cester_test_##x), CESTER_NULL, CESTER_NULL, __LINE__, CESTER_NORMAL_TEST)

/**
    Manually register a test case as a skip test which cases the test case 
    not to run but it will be reported in result and logged under skipped tests.
    
    Reason for skipping a test can be unavailability of resources or any other 
    reason.
*/
#define CESTER_REGISTER_SKIP_TEST(x) cester_register_test((char*)#x, (cester_test_##x), CESTER_NULL, CESTER_NULL, __LINE__, CESTER_NORMAL_SKIP_TEST)

/**
    Manually register a test case that is yet to be implemented so it will be 
    skipped but it will be reported in result and logged under todo tests.
*/
#define CESTER_REGISTER_TODO_TEST(x) cester_register_test((char*)#x, (cester_test_##x), CESTER_NULL, CESTER_NULL, __LINE__, CESTER_NORMAL_TODO_TEST)

/**
    Manually notify cester to execute the BEFORE_ALL function to execute 
    before all the test case are run.
*/
#define CESTER_REGISTER_BEFORE_ALL() cester_register_test("cester_before_all_test", (cester_before_all_test), CESTER_NULL, CESTER_NULL, __LINE__, CESTER_BEFORE_ALL_TEST)

/**
    Manually notify cester to execute the BEFORE_EACH function to execute 
    every time before a test case is run.
*/
#define CESTER_REGISTER_BEFORE_EACH() cester_register_test("cester_before_each_test", CESTER_NULL, (cester_before_each_test), CESTER_NULL, __LINE__, CESTER_BEFORE_EACH_TEST)

/**
    Manually notify cester to execute the AFTER_ALL function to execute 
    after all the test case are run.
*/
#define CESTER_REGISTER_AFTER_ALL() cester_register_test("cester_after_all_test", (cester_after_all_test), CESTER_NULL, CESTER_NULL, __LINE__, CESTER_AFTER_ALL_TEST)

/**
    Manually notify cester to execute the AFTER_EACH function to execute 
    every time after a test case is run.
*/
#define CESTER_REGISTER_AFTER_EACH() cester_register_test("cester_after_each_test", CESTER_NULL, (cester_after_each_test), CESTER_NULL, __LINE__, CESTER_AFTER_EACH_TEST)

/**
    Manually notify cester to execute the CESTER_OPTIONS block before running 
    the tests.
*/
#define CESTER_REGISTER_OPTIONS() cester_register_test("cester_options_before_main", CESTER_NULL, CESTER_NULL, (cester_options_before_main), __LINE__, CESTER_OPTIONS_FUNCTION)

/**
    Manually notify cester to print the CESTER_COMMENT content before running 
    the tests.
*/
#define CESTER_REGISTER_COMMENT() cester_register_test("cester_test_file_comment_function", CESTER_NULL, CESTER_NULL, (cester_test_file_comment_function), __LINE__, CESTER_OPTIONS_FUNCTION)

/**
    Set the expected result of a test case. 
    
    \param x the test case name
    \param y the expected result. Can be one of the ::cester_test_status enum
*/
#define CESTER_TEST_SHOULD(x,y) cester_expected_test_result(#x, y);

/**
    Change the expected result of a test case to Segfault. 
    If the test segfault then it passes. If it does not segfault 
    it is marked as failed.
    
    \param x the test case name
*/
#define CESTER_TEST_SHOULD_SEGFAULT(x) CESTER_TEST_SHOULD(x, CESTER_RESULT_SEGFAULT);

/**
    Change the expected result of a test case to failure. 
    If the test case passed then it marked as failure. If it failed 
    then it consider as passed.
    
    \param x the test case name
*/
#define CESTER_TEST_SHOULD_FAIL(x) CESTER_TEST_SHOULD(x, CESTER_RESULT_FAILURE);

/**
    Change the expected test case result. If the test case is terminated by user 
    or another program then it passes ortherwise it fails.
    
    \param x the test case name
*/
#define CESTER_TEST_SHOULD_BE_TERMINATED(x) CESTER_TEST_SHOULD(x, CESTER_RESULT_TERMINATED);

/**
    Change the expected test case result. If the test case has any un released 
    captured stream it passes. 

    Dont ignore CESTER_RESULT_UNRELEASED_STREAM failure it can result in more 
    erros in other test cases and will leave dangling pointers in memory with 
    no way to tract and free them.
    
    \param x the test case name
*/
#define CESTER_TEST_SHOULD_NOT_RELEASE_STREAM(x) CESTER_TEST_SHOULD(x, CESTER_RESULT_UNRELEASED_STREAM);

#ifndef CESTER_NO_MEM_TEST
/**
    Change the expected test case result to leak memory. If the test case does not 
    leak any memory then the test case is marked as failure.
    
    \param x the test case name
*/
#define CESTER_TEST_SHOULD_LEAK_MEMORY(x) CESTER_TEST_SHOULD(x, CESTER_RESULT_MEMORY_LEAK);
#else
#define CESTER_TEST_SHOULD_LEAK_MEMORY(x)
#endif

#if !defined(__unix__) && !defined(__unix) && !(defined(__APPLE__) && defined(__MACH__)) && !defined(_WIN32)
    #pragma message("Stream capture not supported on this platform, open an issue on the github repo with the platform details")
#endif

/**
    Change the folder to use to store the FILE handle for the captured 
    streams.
    
    \param path1 the folder to used for captured stream
    \param fallback_path the secpnd folder to used for captured stream if path1 is CESTER_NULL
*/
static void cester_set_captured_streams_tmp_folder(char *path1, char *fallback_path) {
    struct stat st = {0};
    if (path1) {
        superTestInstance.captured_streams_tmp_folder = path1;
    } else {
        superTestInstance.captured_streams_tmp_folder = fallback_path;
    }
#if defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)) || defined(_WIN32)
    if (mkdir(superTestInstance.captured_streams_tmp_folder, 0777) != 0 && stat(superTestInstance.captured_streams_tmp_folder, &st) == -1) {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Unable to create the temp folder '");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), superTestInstance.captured_streams_tmp_folder);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "' stream capture tests might fail\n");
    }
#endif
}

/**
    Change the folder to use to store the FILE handle for the captured 
    streams.
    
    \param x the new folder to used for captured stream
*/
#define CESTER_CHANGE_STREAM_CAPTURE_TM_FOLDER(x) cester_set_captured_streams_tmp_folder(x, CESTER_NULL)

/**
    Capture a FILE stream to test it behaviour in realtime.
    This simply opens a temporary file on the system then replaces the 
    stream to capture with the temporary file. n the assertion functions 
    the temporary file content is observed.

    To return the stream back to th original state call the cester_release_stream 
    function. It important to release a stream immediately after assertions 
    else any output to that stream will be capturd also.
    
    \param stream the stream to capture
    \param file_path the name of the file where the test case is written
    \param line_num the line number where the stream is being captured
*/
static void cester_capture_stream(FILE *stream, char const* const file_path, unsigned const line_num) {
    CapturedStream *captured_stream = (CapturedStream *) calloc(1, sizeof(CapturedStream));
    char *replaced_stream_file_path = (char *) "";
    FILE *replaced_stream = CESTER_NULL;
    struct stat st = {0};

    if (superTestInstance.captured_streams == CESTER_NULL) {
	    if (cester_array_init(&superTestInstance.captured_streams) == 0) {
            if (superTestInstance.output_stream==CESTER_NULL) {
                superTestInstance.output_stream = stdout;
                cester_ptr_to_str(&(superTestInstance.output_stream_str), stdout); 
                superTestInstance.output_stream_address = *stdout;
            }
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Unable to initialize the captured stream array. Input and Output Stream test disabled.\n");
            return;
	    }
	}    
#if defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)) || defined(_WIN32)
    if (stat(superTestInstance.captured_streams_tmp_folder, &st) == -1) {
        cester_print_test_case_message("StreamCaptureWarning", "", file_path, line_num);
        cester_concat_str(&superTestInstance.current_test_case->execution_output, "Unable to capture the stream because temp folder '");
        cester_concat_str(&superTestInstance.current_test_case->execution_output, superTestInstance.captured_streams_tmp_folder);
        cester_concat_str(&superTestInstance.current_test_case->execution_output, "' cannot be created.\n");
        return;
    }
#else
    cester_print_test_case_message("StreamCaptureWarning", "", file_path, line_num);
    cester_concat_str(&superTestInstance.current_test_case->execution_output, "Unable to capture the stream because this platform ");
    cester_concat_str(&superTestInstance.current_test_case->execution_output, "is currently not supported, open an issue on the github ");
    cester_concat_str(&superTestInstance.current_test_case->execution_output, "repo with this platform detail.\n");
    return;
#endif
    cester_concat_str(&replaced_stream_file_path, superTestInstance.captured_streams_tmp_folder);
    cester_concat_str(&replaced_stream_file_path, "/");
    cester_concat_ptr(&replaced_stream_file_path, stream);
    cester_concat_str(&replaced_stream_file_path, ".txt");
    replaced_stream = fopen(replaced_stream_file_path, "w+");
    if (!captured_stream || replaced_stream == CESTER_NULL) {
        cester_print_test_case_message("StreamCaptureWarning", "", file_path, line_num);
        cester_concat_str(&superTestInstance.current_test_case->execution_output, "Unable to capture the stream '");
        cester_concat_ptr(&superTestInstance.current_test_case->execution_output, stream);
        cester_concat_str(&superTestInstance.current_test_case->execution_output, "' due to memory allocation error, all assertion will fail for the stream.\n");
        goto cester_capture_stream_cleanup;
        return;
    }
    captured_stream->line_num = line_num;
    captured_stream->original_stream = *stream;
    captured_stream->original_stream_handle = stream;
    captured_stream->replaced_stream_handle = replaced_stream;
    captured_stream->replaced_stream_file_path = replaced_stream_file_path;
    captured_stream->function_name = superTestInstance.current_test_case->name;
    captured_stream->stream_buffer = CESTER_NULL;
    cester_ptr_to_str(&(captured_stream->original_stream_ptr_str), stream);
    cester_ptr_to_str(&(captured_stream->replaced_stream_ptr_str), replaced_stream);
    if (cester_array_add(superTestInstance.captured_streams, captured_stream) == 0) {
        cester_print_test_case_message("StreamCaptureWarning", "", file_path, line_num);
        cester_concat_str(&superTestInstance.current_test_case->execution_output, "Unable to capture the stream '");
        cester_concat_ptr(&superTestInstance.current_test_case->execution_output, stream);
        cester_concat_str(&superTestInstance.current_test_case->execution_output, "' all assertion will fail for the stream.\n");
        goto cester_capture_stream_cleanup;
        return;
    }
    *stream = *(captured_stream->replaced_stream_handle);
    return;

    cester_capture_stream_cleanup:
         if (replaced_stream != CESTER_NULL) {
            fclose(replaced_stream);
            if (remove(replaced_stream_file_path)) {
                cester_print_test_case_message("StreamCaptureCleanupWarning", "", file_path, line_num);
                cester_concat_str(&superTestInstance.current_test_case->execution_output, "Failed to delete residual stream file '");
                cester_concat_str(&superTestInstance.current_test_case->execution_output, replaced_stream_file_path);
                cester_concat_str(&superTestInstance.current_test_case->execution_output, "' manually delete it from your file system.\n");
            }
        }
         if (captured_stream) {
             free(captured_stream);
         }
}

/**
    Release a single captured stream and specify the stream to set back to 
    it original state. 

    Care needs to be taken when using this function because if a captured_stream 
    is specified for a stream the captured_stream will be freed and the stream 
    set to the captured_stream cached stream, so if the stream is not actually 
    for the captured_stream the stream is forecver lost in the memory as the 
    address is compltely dropped.

    \param stream the stream to release
    \param captured_stream the CapturedStream stream object
    \param file_path the name of the file where the test case is written
    \param line_num the line number where the stream is being released
*/
static void cester_release_captured_stream(FILE *stream, CapturedStream *captured_stream, char const* const file_path, unsigned const line_num) {
    if (stream != CESTER_NULL) {
        fflush(stream);
        fclose(captured_stream->replaced_stream_handle);
        if (remove(captured_stream->replaced_stream_file_path)) {
            cester_print_test_case_message("StreamCaptureCleanupWarning", "", file_path, line_num);
            cester_concat_str(&superTestInstance.current_test_case->execution_output, "Failed to delete residual stream file '");
            cester_concat_str(&superTestInstance.current_test_case->execution_output, captured_stream->replaced_stream_file_path);
            cester_concat_str(&superTestInstance.current_test_case->execution_output, "' manually delete it from your file system.\n");
        }
        *stream = captured_stream->original_stream;
    }
    if (captured_stream->stream_buffer != CESTER_NULL) {
        free(captured_stream->stream_buffer);
    }
    free(captured_stream->original_stream_ptr_str);
    free(captured_stream->replaced_stream_ptr_str);
    free(captured_stream->replaced_stream_file_path);
    free(captured_stream);
}

/**
    Reset a stream state and content. This does not return the stream to 
    the original owner, it simply clear the content of the stream.

    \param stream the stream to clear it content
    \param file_path the name of the file where the test case is written
    \param line_num the line number where the stream content is being cleared
*/
static void cester_reset_stream(FILE *stream, char const* const file_path, unsigned const line_num) {
    size_t index;
    char *stream_ptr_str;

    if (superTestInstance.captured_streams == CESTER_NULL) {
        goto cester_reset_stream_cleanup;
    }
    cester_ptr_to_str(&stream_ptr_str, stream);
    if (superTestInstance.captured_streams != CESTER_NULL) {
        CESTER_ARRAY_FOREACH(superTestInstance.captured_streams, index, captured_stream_, {
            CapturedStream *captured_stream;
            if (captured_stream_ != CESTER_NULL) {
                captured_stream = (CapturedStream *) captured_stream_;
                if (cester_string_equals(captured_stream->original_stream_ptr_str, stream_ptr_str) == 1) {
                    if (stream != CESTER_NULL) {
                        fclose(captured_stream->replaced_stream_handle);
                        captured_stream->replaced_stream_handle = fopen(captured_stream->replaced_stream_file_path, "w+");
                        *stream = *(captured_stream->replaced_stream_handle);
                        captured_stream->line_num = line_num;
                    }
                    free(stream_ptr_str);
                    return;
                }
            }
        })
    }
    cester_reset_stream_cleanup:
        cester_print_test_case_message("StreamCaptureWarning", "", file_path, line_num);
        cester_concat_str(&superTestInstance.current_test_case->execution_output, "No stream with the pointer address '");
        cester_concat_str(&superTestInstance.current_test_case->execution_output, stream_ptr_str);
        cester_concat_str(&superTestInstance.current_test_case->execution_output, "' captured so nothing is reset \n");
        free(stream_ptr_str);
}

/**
    Get the content of the stream as string (char *), if the content of the stream 
    is greater than 4GB this will fail.

    Empty string is returned if the stream is not captured.

    \param stream the stream to get it content
    \param file_path the name of the file where the test case is written
    \param line_num the line number where the stream content is being requested
*/
static char *cester_stream_content(FILE *stream, char const* const file_path, unsigned const line_num) {
    size_t index;
    size_t length;
    char *stream_ptr_str;

    if (superTestInstance.captured_streams == CESTER_NULL) {
        return (char *) "";
    }
    cester_ptr_to_str(&stream_ptr_str, stream);
    if (superTestInstance.captured_streams != CESTER_NULL) {
        CESTER_ARRAY_FOREACH(superTestInstance.captured_streams, index, captured_stream_, {
            CapturedStream *captured_stream;
            if (captured_stream_ != CESTER_NULL) {
                captured_stream = (CapturedStream *) captured_stream_;
                if (cester_string_equals(captured_stream->original_stream_ptr_str, stream_ptr_str) == 1) {
                    if (stream != CESTER_NULL) {
                        fflush(stream);
                        fseek(captured_stream->replaced_stream_handle, 0, SEEK_END);
                        length = ftell(captured_stream->replaced_stream_handle);
                        fseek(captured_stream->replaced_stream_handle, 0, SEEK_SET);
                        if (captured_stream->stream_buffer != CESTER_NULL) {
                            free(captured_stream->stream_buffer);
                        }
                        captured_stream->stream_buffer = (char *) malloc(length+1);
                        if (captured_stream->stream_buffer) {
                            length = fread(captured_stream->stream_buffer, 1, length, captured_stream->replaced_stream_handle);
                            captured_stream->stream_buffer[length] = '\0';
                        }
                        free(stream_ptr_str);
                        return captured_stream->stream_buffer;
                    }
                    free(stream_ptr_str);
                    return (char *) "";
                }
            }
        })
    }
    free(stream_ptr_str);
    return (char *) "";
}

/**
    Release already captured FILE handle, if the stream was not captured before 
    a warnning is printed. 

    when the CapturedStream object is released, the temporary file receiving the input 
    is closed and deleted. 

    \param stream the stream to release
    \param file_path the name of the file where the test case is written
    \param line_num the line number where the stream is being released
*/
static void cester_release_stream(FILE *stream, char const* const file_path, unsigned const line_num) {
    size_t index;
    char *stream_ptr_str;

    if (superTestInstance.captured_streams == CESTER_NULL) {
        goto cester_release_stream_cleanup;
    }
    cester_ptr_to_str(&stream_ptr_str, stream);
    if (superTestInstance.captured_streams != CESTER_NULL) {
        CESTER_ARRAY_FOREACH(superTestInstance.captured_streams, index, captured_stream_, {
            CapturedStream *captured_stream;
            if (captured_stream_ != CESTER_NULL) {
                captured_stream = (CapturedStream *) captured_stream_;
                if (cester_string_equals(captured_stream->original_stream_ptr_str, stream_ptr_str) == 1) {
                    if (cester_array_remove_at(superTestInstance.captured_streams, index) == CESTER_NULL) {
                        cester_print_test_case_message("StreamCaptureCleanupWarning", "", file_path, line_num);
                        cester_concat_str(&superTestInstance.current_test_case->execution_output, "Failed to remove captured stream with pointer address '");
                        cester_concat_str(&superTestInstance.current_test_case->execution_output, stream_ptr_str);
                        cester_concat_str(&superTestInstance.current_test_case->execution_output, "' from captured stream array, expect non breaking issues.\n");
                    }
                    free(stream_ptr_str);
                    cester_release_captured_stream(stream, captured_stream, file_path, line_num);
                    captured_stream = CESTER_NULL;
                    return;
                }
            }
        })
    }
    cester_release_stream_cleanup:
        cester_print_test_case_message("StreamCaptureWarning", "", file_path, line_num);
        cester_concat_str(&superTestInstance.current_test_case->execution_output, "No stream with the pointer address '");
        cester_concat_str(&superTestInstance.current_test_case->execution_output, stream_ptr_str);
        cester_concat_str(&superTestInstance.current_test_case->execution_output, "' captured so nothing is realeased \n");
        free(stream_ptr_str);
}

/**
    Check the captured streams after a test case exeution completes and report 
    error if the test case has any un release stream.

    The single most important reason for this check is to release the output 
    stream used to write the test result. stdout in most case.

    \param test_case the test case which execution just end
*/
static unsigned release_forgotten_captured_streams(TestCase *test_case) {
    size_t index;
    unsigned unreleased_stream_count = 0;

    if (superTestInstance.captured_streams == CESTER_NULL) {
        goto release_forgotten_captured_streams_cleanup;
    }
    CESTER_ARRAY_FOREACH(superTestInstance.captured_streams, index, captured_stream_, {
        CapturedStream *captured_stream = (CapturedStream *) captured_stream_;
        if (captured_stream == CESTER_NULL) {
            continue;
        }
        if (cester_string_equals(captured_stream->original_stream_ptr_str, superTestInstance.output_stream_str) == 1) {
            fflush(superTestInstance.output_stream);
            *(superTestInstance.output_stream) = superTestInstance.output_stream_address;
        }
        if (captured_stream != CESTER_NULL && cester_string_equals(captured_stream->function_name, test_case->name) == 1) {
            unreleased_stream_count++;
            cester_print_test_case_message("StreamCaptureError", "", superTestInstance.test_file_path, captured_stream->line_num);
            cester_concat_str(&test_case->execution_output, "You forgot to realease the stream '");
            cester_concat_str(&test_case->execution_output, captured_stream->original_stream_ptr_str);
            cester_concat_str(&test_case->execution_output, "' captured in line ");
            cester_concat_int(&test_case->execution_output, captured_stream->line_num);
            cester_concat_str(&test_case->execution_output, "\n");
        };
        if (cester_array_remove_at(superTestInstance.captured_streams, index) == CESTER_NULL) {
            cester_print_test_case_message("StreamCaptureCleanupWarning", "", superTestInstance.test_file_path, captured_stream->line_num);
            cester_concat_str(&superTestInstance.current_test_case->execution_output, "Failed to remove captured stream with pointer address '");
            cester_concat_str(&superTestInstance.current_test_case->execution_output, captured_stream->original_stream_ptr_str);
            cester_concat_str(&superTestInstance.current_test_case->execution_output, "' from captured stream array, expect non breaking issues.\n");
        } else {
            index--;
        }
	cester_release_captured_stream(captured_stream->original_stream_handle, captured_stream, superTestInstance.test_file_path, captured_stream->line_num);
        captured_stream = CESTER_NULL;
    })
    release_forgotten_captured_streams_cleanup:
        return unreleased_stream_count;
}

/**
    Alias for cester_capture_stream function
*/
#define CESTER_CAPTURE_STREAM(x) cester_capture_stream(x, __FILE__, __LINE__)

/**
    Alias for cester_stream_content function
*/
#define CESTER_STREAM_CONTENT(x) cester_stream_content(x, __FILE__, __LINE__)

/**
    Alias for cester_reset_stream function
*/
#define CESTER_RESET_STREAM(x) cester_reset_stream(x, __FILE__, __LINE__)

/**
    Alias for cester_release_stream function
*/
#define CESTER_RELEASE_STREAM(x) cester_release_stream(x, __FILE__, __LINE__)

/**
    Capture the stdin stream that receive the input for the active 
    program
*/
#define CESTER_CAPTURE_STDIN() CESTER_CAPTURE_STREAM(stdin)

/**
    Get the stdin content.
*/
#define CESTER_STDIN_CONTENT() CESTER_STREAM_CONTENT(stdin)

/**
    Clear the stdin content.
*/
#define CESTER_RESET_STDIN() CESTER_RESET_STREAM(stdin)

/**
    Release the stdin stream that receive the input for the active 
    program
*/
#define CESTER_RELEASE_STDIN() CESTER_RELEASE_STREAM(stdin)

/**
    Capture the stdout stream where everything sent to printf 
    is written into
*/
#define CESTER_CAPTURE_STDOUT() CESTER_CAPTURE_STREAM(stdout)

/**
    Get the stdout content.
*/
#define CESTER_STDOUT_CONTENT() CESTER_STREAM_CONTENT(stdout)

/**
    Clear the stdout content.
*/
#define CESTER_RESET_STDOUT() CESTER_RESET_STREAM(stdout)

/**
    Release the stdout stream where everything sent to printf 
    is written into
*/
#define CESTER_RELEASE_STDOUT() CESTER_RELEASE_STREAM(stdout)

/**
    Capture the stderr stream
*/
#define CESTER_CAPTURE_STDERR() CESTER_CAPTURE_STREAM(stderr)

/**
    Get the stderr content.
*/
#define CESTER_STDERR_CONTENT() CESTER_STREAM_CONTENT(stderr)

/**
    Clear the stderr content.
*/
#define CESTER_RESET_STDERR() CESTER_RESET_STREAM(stderr)

/**
    Release the stderr stream
*/
#define CESTER_RELEASE_STDERR() CESTER_RELEASE_STREAM(stderr)

/**
    Check whether the content of a stream equals a value

    \param x the stream
    \param y the string to check if it same as the stream content
*/
#define cester_assert_stream_content_equal(x,y) cester_assert_str_equal(CESTER_STREAM_CONTENT(x), y)

/**
    Check whether the content of a stream contains a value

    \param x the stream
    \param y the string to check if it present as the stream content
*/
#define cester_assert_stream_content_contain(x, y) cester_assert_true(cester_string_contains(CESTER_STREAM_CONTENT(x), y))

/**
    Check whether the content of a stream does not equal a value

    \param x the stream
    \param y the string to check if it not same as the stream content
*/
#define cester_assert_stream_content_not_equal(x,y) cester_assert_str_not_equal(CESTER_STREAM_CONTENT(x), y)

/**
    Check whether the content of a stream does not contains a value

    \param x the stream
    \param y the string to check if it not present as the stream content
*/
#define cester_assert_stream_content_not_contain(x, y) cester_assert_false(cester_string_contains(CESTER_STREAM_CONTENT(x), y))

/**
    Check whether the content of stdin stream equals a value
*/
#define cester_assert_stdin_stream_content_equal(y) cester_assert_str_equal(CESTER_STDIN_CONTENT(), y)

/**
    Check whether the content of stdin stream contains a value
*/
#define cester_assert_stdin_stream_content_contain(y) cester_assert_true(cester_string_contains(CESTER_STDIN_CONTENT(), y))

/**
    Check whether the content of stdin stream does not equals a value
*/
#define cester_assert_stdin_stream_content_not_equal(y) cester_assert_str_not_equal(CESTER_STDIN_CONTENT(), y)

/**
    Check whether the content of stdin stream does not contains a value
*/
#define cester_assert_stdin_stream_content_not_contain(y) cester_assert_false(cester_string_contains(CESTER_STDIN_CONTENT(), y))

/**
    Check whether the content of stdout stream equals a value
*/
#define cester_assert_stdout_stream_content_equal(y) cester_assert_str_equal(CESTER_STDOUT_CONTENT(), y)

/**
    Alias for cester_assert_stdout_stream_content_equal
*/
#define cester_assert_printf_equal cester_assert_stdout_stream_content_equal

/**
    Check whether the content of stdout stream contains a value
*/
#define cester_assert_stdout_stream_content_contain(y) cester_assert_true(cester_string_contains(CESTER_STDOUT_CONTENT(), y))

/**
    Alias for cester_assert_stdout_stream_content_contain
*/
#define cester_assert_printf_contain cester_assert_stdout_stream_content_contain

/**
    Check whether the content of stdout stream does not equals a value
*/
#define cester_assert_stdout_stream_content_not_equal(y) cester_assert_str_not_equal(CESTER_STDOUT_CONTENT(), y)

/**
    Alias for cester_assert_stdout_stream_content_not_equal
*/
#define cester_assert_printf_not_equal cester_assert_stdout_stream_content_not_equal

/**
    Check whether the content of stdout stream does not contains a value
*/
#define cester_assert_stdout_stream_content_not_contain(y) cester_assert_false(cester_string_contains(CESTER_STDOUT_CONTENT(), y))

/**
    Alias for cester_assert_stdout_stream_content_not_contain
*/
#define cester_assert_printf_not_contain cester_assert_stdout_stream_content_not_contain

/**
    Check whether the content of stderr stream equals a value
*/
#define cester_assert_stderr_stream_content_equal(y) cester_assert_str_equal(CESTER_STDERR_CONTENT(), y)

/**
    Check whether the content of stderr stream contains a value
*/
#define cester_assert_stderr_stream_content_contain(y) cester_assert_true(cester_string_contains(CESTER_STDERR_CONTENT(), y))

/**
    Check whether the content of stderr stream does not equals a value
*/
#define cester_assert_stderr_stream_content_not_equal(y) cester_assert_str_not_equal(CESTER_STDERR_CONTENT(), y)

/**
    Check whether the content of stderr stream does not contains a value
*/
#define cester_assert_stderr_stream_content_not_contain(y) cester_assert_false(cester_string_contains(CESTER_STDERR_CONTENT(), y))

/**
    Manually register a test case
*/
static __CESTER_INLINE__ void cester_register_test(char *test_name, cester_test f1, cester_before_after_each f2, cester_void f3, unsigned line_num, TestType test_type) {
    TestCase* test_case ;
    if (superTestInstance.registered_test_cases == CESTER_NULL) {
	if (cester_array_init(&superTestInstance.registered_test_cases) == 0) {
	    if (superTestInstance.output_stream==CESTER_NULL) {
            superTestInstance.output_stream = stdout;
            cester_ptr_to_str(&(superTestInstance.output_stream_str), stdout); 
            superTestInstance.output_stream_address = *stdout;
	    }
	    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Unable to initialize the test cases array. Cannot run manually registered tests.\n");
	    CESTER_RESET_TERMINAL_ATTR();
        return;
	}
    }
    test_case = (TestCase*) malloc(sizeof(TestCase));
    if (!test_case) {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "memory allocation error: Unable to register the test case '");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), test_name);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "'\n");
        CESTER_RESET_TERMINAL_ATTR();
        return;
    }
    test_case->execution_status = CESTER_RESULT_UNKNOWN;
    test_case->line_num = line_num;
    test_case->expected_result = CESTER_RESULT_SUCCESS;
    #ifndef CESTER_NO_TIME
        test_case->start_tic = 0.000;
        test_case->execution_time = 0.000;
    #endif
    test_case->execution_output = (char*) "";
    test_case->test_function = f1;
    test_case->test_ba_function = f2;
    test_case->test_void_function = f3;
    test_case->name = test_name;
    test_case->test_type = test_type;
    if (cester_array_add(superTestInstance.registered_test_cases, test_case) == 0) {
        if (superTestInstance.output_stream==CESTER_NULL) {
            superTestInstance.output_stream = stdout;
            cester_ptr_to_str(&(superTestInstance.output_stream_str), stdout); 
            superTestInstance.output_stream_address = *stdout;
        }
        free(test_case);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Failed to register '");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), test_name);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "' \n");
        CESTER_RESET_TERMINAL_ATTR();
        superTestInstance.mem_test_active = 0;
    }
}

static __CESTER_INLINE__ void cester_expected_test_result(const char* const test_name, enum cester_test_status expected_result) {
    unsigned i,index;
    if (superTestInstance.registered_test_cases->size == 0) {
        for (i=0;cester_test_cases[i].test_type != CESTER_TESTS_TERMINATOR;++i) {
            if ((cester_test_cases[i].test_type == CESTER_NORMAL_TEST || 
                       cester_test_cases[i].test_type == CESTER_NORMAL_TODO_TEST || 
                       cester_test_cases[i].test_type == CESTER_NORMAL_SKIP_TEST) &&
                       cester_string_equals(cester_test_cases[i].name, (char*)test_name) == 1) {
                           
                cester_test_cases[i].expected_result = expected_result;
            }
            
        }
    }
    
    CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index, test_case, {
        if ((((TestCase*)test_case)->test_type == CESTER_NORMAL_TEST || 
                   ((TestCase*)test_case)->test_type == CESTER_NORMAL_TODO_TEST || 
                   ((TestCase*)test_case)->test_type == CESTER_NORMAL_SKIP_TEST) && 
                   cester_string_equals(((TestCase*)test_case)->name, (char*)test_name) == 1) {
            
            ((TestCase*)test_case)->expected_result = expected_result;
        }
    })
}

static __CESTER_INLINE__ unsigned cester_run_test_no_isolation(TestInstance *, TestCase *, unsigned);

static __CESTER_INLINE__ void cester_report_single_test_result(unsigned last_status, TestCase *a_test_case) {
    char *cleaned_name = (superTestInstance.verbose_level >= 4 ? superTestInstance.test_file_path : cester_extract_name(superTestInstance.test_file_path) );
    #ifndef CESTER_NO_TIME
        clock_t tok ;
    
        tok = clock();
        a_test_case->execution_time = (double)(((double)tok) - ((double)a_test_case->start_tic)) / CLOCKS_PER_SEC;
    #endif
    if ((a_test_case->expected_result == last_status || a_test_case->expected_result == CESTER_RESULT_FAILURE) && 
        (last_status != CESTER_RESULT_SUCCESS)) {
            
        a_test_case->execution_status = CESTER_RESULT_SUCCESS;
        cester_concat_str(&a_test_case->execution_output, "Passed ");
        cester_concat_str(&a_test_case->execution_output, cleaned_name);
        cester_concat_str(&a_test_case->execution_output, ":");
        cester_concat_int(&a_test_case->execution_output, a_test_case->line_num);
        cester_concat_str(&a_test_case->execution_output, ":");
        cester_concat_str(&a_test_case->execution_output, " in '");
        cester_concat_str(&a_test_case->execution_output, a_test_case->name);
        cester_concat_str(&a_test_case->execution_output, "'");
        if (superTestInstance.verbose_level >= 2) {
            cester_concat_str(&a_test_case->execution_output, " => ");
            switch (a_test_case->expected_result) {
                case CESTER_RESULT_FAILURE:
                    cester_concat_str(&a_test_case->execution_output, "Failed as expected");
                    break;
                case CESTER_RESULT_SEGFAULT:
                    cester_concat_str(&a_test_case->execution_output, "Segfault as expected");
                    break;
                case CESTER_RESULT_TERMINATED:
                    cester_concat_str(&a_test_case->execution_output, "Prematurely terminated as expected");
                    break;
                case CESTER_RESULT_TIMED_OUT:
                    cester_concat_str(&a_test_case->execution_output, "Timed out as expected");
                    break;
                case CESTER_RESULT_UNRELEASED_STREAM:
                    cester_concat_str(&a_test_case->execution_output, "Have unreleased stream as expected (ARE YOU SERIOUS? BAD IDEA!!!!)");
                    break;
#ifndef CESTER_NO_MEM_TEST
                case CESTER_RESULT_MEMORY_LEAK:
                    cester_concat_str(&a_test_case->execution_output, "Leaked memory as expected");
                    break;
#endif
                case CESTER_RESULT_SUCCESS:
                case CESTER_RESULT_UNKNOWN:
                    break;
            }
        }
        cester_concat_str(&a_test_case->execution_output, "\n");
        
    } else if (a_test_case->expected_result != last_status && a_test_case->expected_result != CESTER_RESULT_SUCCESS) {
        a_test_case->execution_status = last_status;
        cester_concat_str(&a_test_case->execution_output, "ResultError ");
        cester_concat_str(&a_test_case->execution_output, cleaned_name);
        cester_concat_str(&a_test_case->execution_output, ":");
        cester_concat_int(&a_test_case->execution_output, a_test_case->line_num);
        cester_concat_str(&a_test_case->execution_output, ":");
        cester_concat_str(&a_test_case->execution_output, " in '");
        cester_concat_str(&a_test_case->execution_output, a_test_case->name);
        cester_concat_str(&a_test_case->execution_output, "'");
        if (superTestInstance.verbose_level >= 2) {
            cester_concat_str(&a_test_case->execution_output, " => ");
            switch (a_test_case->expected_result) {
                case CESTER_RESULT_FAILURE:
                    cester_concat_str(&a_test_case->execution_output, "Expected to Fail but passed");
                    break;
                case CESTER_RESULT_SEGFAULT:
                    cester_concat_str(&a_test_case->execution_output, "Expected to Segfault but passed");
                    break;
                case CESTER_RESULT_TERMINATED:
                    cester_concat_str(&a_test_case->execution_output, "Expected to be Prematurely terminated but exit gracefully");
                    break;
                case CESTER_RESULT_TIMED_OUT:
                    cester_concat_str(&a_test_case->execution_output, "Expected to Time out but ends in time");
                    break;
                case CESTER_RESULT_UNRELEASED_STREAM:
                    cester_concat_str(&a_test_case->execution_output, "Expected to have unreleased stream but all streams were released");
                    break;
    #ifndef CESTER_NO_MEM_TEST
                case CESTER_RESULT_MEMORY_LEAK:
                    cester_concat_str(&a_test_case->execution_output, "Expected to Leak memory but no memory was leaked");
                    break;
    #endif
                case CESTER_RESULT_SUCCESS:
                case CESTER_RESULT_UNKNOWN:
                    break;
            }
        }
        cester_concat_str(&a_test_case->execution_output, "\n");
    } else {
        a_test_case->execution_status = last_status;
    }
    if (a_test_case->execution_status == CESTER_RESULT_SUCCESS) {
        ++superTestInstance.total_passed_tests_count;
    } else {
        ++superTestInstance.total_failed_tests_count;
    }
    if (superTestInstance.single_output_only == 1) {
        superTestInstance.current_execution_status = last_status;
    } else {
        superTestInstance.current_execution_status = a_test_case->execution_status;
    }
    if (superTestInstance.verbose_level < 4) {
        free(cleaned_name);
    }
}

static __CESTER_INLINE__ void cester_run_test(TestInstance *test_instance, TestCase *a_test_case, unsigned index) {
    unsigned last_status;

    last_status = CESTER_RESULT_UNKNOWN;
#ifndef CESTER_NO_SIGNAL
    if (setjmp(buf) == 1) {
        goto check_isolation;
    }
#endif
#ifndef CESTER_NO_TIME
    a_test_case->start_tic = clock();
#endif
#ifndef __CESTER_STDC_VERSION__
    #pragma message("Isolated tests not supported in C version less than C99 and C++ version less than C++11. cester will rely on signal for crash reporting")
    superTestInstance.isolate_tests = 0;
#endif
    if (superTestInstance.isolate_tests == 1 && last_status == CESTER_RESULT_UNKNOWN) {
#ifdef __CESTER_STDC_VERSION__
#if defined(_WIN32) && !defined(CESTER_EXCLUDE_WINDOWS_H)
        HANDLE stdout_pipe_read;
        HANDLE stdout_pipe_write;
        SECURITY_ATTRIBUTES sa;
        sa.nLength = sizeof(SECURITY_ATTRIBUTES);
        sa.bInheritHandle = TRUE;
        sa.lpSecurityDescriptor = CESTER_NULL;

        CreatePipe(&stdout_pipe_read, &stdout_pipe_write, &sa, 0);
#ifdef __cplusplus
        PROCESS_INFORMATION pi;
        STARTUPINFO si;
        si = {
            .cb = sizeof(STARTUPINFO),
            .dwFlags = STARTF_USESTDHANDLES,
            .hStdOutput = stdout_pipe_write
        };
        pi = {0};
#else
        STARTUPINFO si = {
            .cb = sizeof(STARTUPINFO),
            .dwFlags = STARTF_USESTDHANDLES,
            .hStdOutput = stdout_pipe_write
        };
        PROCESS_INFORMATION pi = {0};
#endif

        

        CHAR command[1500];
        snprintf(command, 1500, "%s --cester-test=%s  --cester-singleoutput --cester-noisolation --cester-verbose-level=%d %s %s %s %s %s",
                    test_instance->argv[0],
                    a_test_case->name,
                    (superTestInstance.verbose_level),
                    (superTestInstance.mem_test_active == 0 ? "--cester-nomemtest" : ""),
                    (superTestInstance.format_test_name == 0 ? "--cester-dontformatname" : ""),
                    (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1 ? "--cester-output=tap" : ""),
                    (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1 ? "--cester-output=tapV13" : ""),
                    superTestInstance.flattened_cmd_argv);

        CreateProcess(
            CESTER_NULL,
            command,
            CESTER_NULL,
            CESTER_NULL,
            TRUE,
            0,
            CESTER_NULL,
            CESTER_NULL,
            &si,
            &pi);

        CloseHandle(stdout_pipe_write);

        DWORD len;
        DWORD maxlen;
        CHAR buffer[700];

        maxlen = 700;
        do {
            ReadFile(stdout_pipe_read, buffer, maxlen, &len, CESTER_NULL);
            buffer[len] = '\0';
            cester_concat_str(&a_test_case->execution_output, buffer);
        } while (len > 0);

        WaitForSingleObject(pi.hProcess, INFINITE);

        DWORD status;
        GetExitCodeProcess(pi.hProcess, &status);

        if ((status & 0x80000000)) {
            last_status = CESTER_RESULT_SEGFAULT;
        } else if (status == 1 && strlen(a_test_case->execution_output) == 0) {
            last_status = CESTER_RESULT_TERMINATED;
        } else {
            last_status = status;
        }

        end_sub_process:
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
        pid_t pid;
        int pipefd[2];
        char *selected_test_unix;
        char *verbose_level_str;

        pipe(pipefd);
        pid = fork();

        if (pid == -1) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Unable to create a seperate process for the '");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), a_test_case->name);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "'. Running the test on main process.");
            last_status = cester_run_test_no_isolation(test_instance, a_test_case, index);

        } else if (pid == 0) {
            selected_test_unix = (char*) "";
            verbose_level_str = (char *) "";
            cester_concat_str(&selected_test_unix, "--cester-test=");
            cester_concat_str(&selected_test_unix, a_test_case->name);
            cester_concat_str(&verbose_level_str, "--cester-verbose-level=");
            cester_concat_int(&verbose_level_str, superTestInstance.verbose_level);

            close(pipefd[0]);
            dup2(pipefd[1], STDOUT_FILENO);
            execl(test_instance->argv[0],
                    test_instance->argv[0],
                    selected_test_unix,
                    "--cester-singleoutput",
                    "--cester-noisolation",
                    verbose_level_str,
                    (superTestInstance.mem_test_active == 0 ? "--cester-nomemtest" : ""),
                    (superTestInstance.format_test_name == 0 ? "--cester-dontformatname" : ""),
                    (superTestInstance.no_color == 1 ? "--cester-nocolor" : ""),
                    (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1 ? "--cester-output=tap" : ""),
                    (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1 ? "--cester-output=tapV13" : ""),
                    superTestInstance.flattened_cmd_argv,
                    (char*)CESTER_NULL);
            free(selected_test_unix);
            free(verbose_level_str);
            exit(CESTER_RESULT_FAILURE);

        } else {
            int status;
            char buffer[700];
            size_t len;

            close(pipefd[1]);
            while ((len = read(pipefd[0], buffer, 700)) != 0) {
                buffer[len] = '\0';
                cester_concat_str(&a_test_case->execution_output, buffer);
            }
            waitpid(pid, &status, 0);
            close(pipefd[0]);
            last_status = WEXITSTATUS(status);
            end_sub_process:
                kill(pid, SIGTERM);
        }
#else
        #pragma message("Isolated tests not supported in this environment. The tests will be run on the main process")
        last_status = cester_run_test_no_isolation(test_instance, a_test_case, index);
#define CESTER_NO_SUBPROCESS 1
#endif
#endif
    } else if (last_status == CESTER_RESULT_UNKNOWN) {
        last_status = cester_run_test_no_isolation(test_instance, a_test_case, index);
    }
    resolve_test_result:
        cester_report_single_test_result(last_status, a_test_case);
        return;
    
    check_isolation:
        last_status = superTestInstance.current_execution_status;
#ifdef __CESTER_STDC_VERSION__
#ifndef CESTER_NO_SUBPROCESS
        if (superTestInstance.isolate_tests == 1) {
            goto end_sub_process;
        }
#endif
#endif
        goto resolve_test_result;
}

static __CESTER_INLINE__ unsigned cester_run_test_no_isolation(TestInstance *test_instance, TestCase *a_test_case, unsigned index) {
    unsigned i, index1, index2, ret_val;
    char *prefix = (char *) "";
    superTestInstance.current_execution_status = CESTER_RESULT_SUCCESS;
    if (superTestInstance.registered_test_cases->size == 0) {
        for (i=0;cester_test_cases[i].test_type != CESTER_TESTS_TERMINATOR;++i) {
            if (cester_test_cases[i].test_type == CESTER_BEFORE_EACH_TEST) {
                superTestInstance.current_cester_function_type = CESTER_BEFORE_EACH_TEST;
                ((cester_before_after_each)cester_test_cases[i].test_ba_function)(test_instance, a_test_case->name, index);
            }
        }
    }
    CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index1, test_case, {
        if (((TestCase*)test_case)->test_type == CESTER_BEFORE_EACH_TEST) {
            superTestInstance.current_cester_function_type = CESTER_BEFORE_EACH_TEST;
            ((cester_before_after_each)((TestCase*)test_case)->test_ba_function)(test_instance, a_test_case->name, index);
        }
    })
    superTestInstance.current_cester_function_type = CESTER_NORMAL_TEST;
    superTestInstance.current_test_case = a_test_case;
    ((cester_test)a_test_case->test_function)(test_instance);
    if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1) {
        prefix = (char *) "# ";
        
    } else if (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1) {
        prefix = (char *) "    - ";
        
    }

    if (release_forgotten_captured_streams(a_test_case) > 0) {
        superTestInstance.current_execution_status = CESTER_RESULT_UNRELEASED_STREAM;
    }
#ifndef CESTER_NO_MEM_TEST
    if (check_memory_allocated_for_functions(a_test_case->name, CESTER_NULL, prefix, &(superTestInstance.current_test_case)->execution_output) > 0) {
        superTestInstance.current_execution_status = CESTER_RESULT_MEMORY_LEAK;
    }
#endif

    if (superTestInstance.registered_test_cases->size == 0) {
        for (i=0;cester_test_cases[i].test_type != CESTER_TESTS_TERMINATOR;++i) {
            if (cester_test_cases[i].test_type == CESTER_AFTER_EACH_TEST) {
                superTestInstance.current_cester_function_type = CESTER_AFTER_EACH_TEST;
                ((cester_before_after_each)cester_test_cases[i].test_ba_function)(test_instance, a_test_case->name, index);
            }
        }
    }
    CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index2, test_case, {
        if (((TestCase*)test_case)->test_type == CESTER_AFTER_EACH_TEST) {
            superTestInstance.current_cester_function_type = CESTER_AFTER_EACH_TEST;
           ((cester_before_after_each)((TestCase*)test_case)->test_ba_function)(test_instance, a_test_case->name, index);
        }
    })
    if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1 || 
        cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1) {
        prefix = (char *) "# ";
    }
    
#ifndef CESTER_NO_MEM_TEST
    ret_val = check_memory_allocated_for_functions((char *)"CESTER_BEFORE_EACH", CESTER_NULL, prefix, &superTestInstance.main_execution_output);
    if (ret_val > 0) {
        superTestInstance.total_test_errors_count += ret_val;
    }
#endif

    ++superTestInstance.total_tests_ran;
    if (superTestInstance.single_output_only == 1) {
        CESTER_DELEGATE_FPRINT_STR((default_color), a_test_case->execution_output);
    }
    return superTestInstance.current_execution_status;
}

#ifndef CESTER_NO_SIGNAL  
/*void (*signal(int , void (*)(int)))(int);*/
void cester_capture_signals();
void cester_recover_on_signal(int sig_num);
#endif

/* use start param to save the state index instead of starting 
loop again or super var */ 
static __CESTER_INLINE__ void cester_run_all_test_iterator(int start) {
    unsigned i, j, index2, index3, test_index;
    unsigned found_test;
    char* selected_test_case_name;
    
    found_test = 0;
    test_index = 0;
    if (superTestInstance.selected_test_cases_size == 0) {
        if (superTestInstance.registered_test_cases->size == 0) {
            for (i=0;cester_test_cases[i].test_type != CESTER_TESTS_TERMINATOR;++i) {
                if (cester_test_cases[i].test_type == CESTER_NORMAL_TEST && cester_test_cases[i].execution_status == CESTER_RESULT_UNKNOWN) {
                    cester_run_test(superTestInstance.test_instance, &cester_test_cases[i], ++test_index);

                } else if (cester_test_cases[i].test_type == CESTER_NORMAL_TODO_TEST) {
                    ++superTestInstance.todo_tests_count;

                } else if (cester_test_cases[i].test_type == CESTER_NORMAL_SKIP_TEST) {
                    ++superTestInstance.skipped_test_count;

                }
            }
        }
        CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index2, test_case, {
            if (((TestCase*)test_case)->test_type == CESTER_NORMAL_TEST && ((TestCase*)test_case)->execution_status == CESTER_RESULT_UNKNOWN) {
                cester_run_test(superTestInstance.test_instance, ((TestCase*)test_case), ++test_index);
                
            } else if (((TestCase*)test_case)->test_type == CESTER_NORMAL_TODO_TEST) {
                ++superTestInstance.todo_tests_count;

            } else if (((TestCase*)test_case)->test_type == CESTER_NORMAL_SKIP_TEST) {
                ++superTestInstance.skipped_test_count;

            }
        })

    } else {
        for (j = superTestInstance.selected_test_cases_found; j < superTestInstance.selected_test_cases_size; ++j) {
            selected_test_case_name = superTestInstance.selected_test_cases_names[j];
            found_test = 0;
            if (superTestInstance.registered_test_cases->size == 0) {
                for (i=0;cester_test_cases[i].test_type != CESTER_TESTS_TERMINATOR;++i) {
                    if ((cester_test_cases[i].test_type == CESTER_NORMAL_TEST || cester_test_cases[i].test_type == CESTER_NORMAL_TODO_TEST ||
                        cester_test_cases[i].test_type == CESTER_NORMAL_SKIP_TEST) &&
                        cester_string_equals(cester_test_cases[i].name, selected_test_case_name) == 1 &&  
                        cester_test_cases[i].execution_status == CESTER_RESULT_UNKNOWN) {

                        found_test = 1;
                        if (cester_test_cases[i].test_type == CESTER_NORMAL_TEST) {
                            ++superTestInstance.selected_test_cases_found;
                            cester_run_test(superTestInstance.test_instance, &cester_test_cases[i], ++test_index);
                        } else {
                            cester_test_cases[i].execution_status = CESTER_RESULT_SUCCESS;
                            if (cester_test_cases[i].test_type == CESTER_NORMAL_SKIP_TEST) {
                                ++superTestInstance.skipped_test_count;
                            } else {
                                ++superTestInstance.todo_tests_count;
                            }
                        }
                    }
                }
            }
            if (found_test == 0) {
                CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index3, test_case, {
                    if ((((TestCase*)test_case)->test_type == CESTER_NORMAL_TEST || ((TestCase*)test_case)->test_type == CESTER_NORMAL_TODO_TEST ||
                        ((TestCase*)test_case)->test_type == CESTER_NORMAL_SKIP_TEST) &&
                        cester_string_equals(((TestCase*)test_case)->name, selected_test_case_name) == 1 && 
                        ((TestCase*)test_case)->execution_status == CESTER_RESULT_UNKNOWN) {

                        found_test = 1;
                        if (((TestCase*)test_case)->test_type == CESTER_NORMAL_TEST) {
                            ++superTestInstance.selected_test_cases_found;
                            cester_run_test(superTestInstance.test_instance, ((TestCase*)test_case), ++test_index);
                        } else {
                            ((TestCase*)test_case)->execution_status = CESTER_RESULT_SUCCESS;
                            if (((TestCase*)test_case)->test_type == CESTER_NORMAL_SKIP_TEST) {
                                ++superTestInstance.skipped_test_count;
                            } else {
                                ++superTestInstance.todo_tests_count;
                            }
                        }
                    }
                })
                if (found_test == 0) {
                    if (superTestInstance.verbose_level > 0 && cester_string_equals(superTestInstance.output_format, (char*) "text") == 1) {
                        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Warning: the test case '");
                        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), superTestInstance.selected_test_cases_names[j]);
                        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "' was not found! \n");
                        CESTER_RESET_TERMINAL_ATTR();
                    }
                }
            }
        }
    }
}

static void cester_cleanup_super_instance()
{
    unsigned index;
    
#ifndef CESTER_NO_MEM_TEST
	if (superTestInstance.mem_alloc_manager != CESTER_NULL) {
        CESTER_ARRAY_FOREACH(superTestInstance.mem_alloc_manager, index, alloc_mem, {
            if (alloc_mem != CESTER_NULL) {
                free(alloc_mem);
            }
            if (cester_array_remove_at(superTestInstance.mem_alloc_manager, index) != CESTER_NULL) {
                index--;
            }
        });
        cester_array_destroy(superTestInstance.mem_alloc_manager);
    }
#endif
    if (superTestInstance.registered_test_cases != CESTER_NULL) {
        index = 0;
        CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index, test_case, {
            if (strlen(((TestCase *)test_case)->execution_output) > 0) {
                free(((TestCase *)test_case)->execution_output);
            }
            free(test_case);
            if (cester_array_remove_at(superTestInstance.registered_test_cases, index) != CESTER_NULL) {
                index--;
            }
        })
        cester_array_destroy(superTestInstance.registered_test_cases);
    }
    if (superTestInstance.selected_test_cases_size > 0) {
        index = 0;
        for (; index < superTestInstance.selected_test_cases_size; ++index) {
            free(superTestInstance.selected_test_cases_names[index]);
        }
        free(superTestInstance.selected_test_cases_names);
    }
    if (superTestInstance.output_stream_str != CESTER_NULL) {
        free(superTestInstance.output_stream_str);
    }
    if (superTestInstance.test_instance != CESTER_NULL) {
        free(superTestInstance.test_instance);
    }
}

static __CESTER_INLINE__ unsigned cester_run_all_test(unsigned argc, char **argv) {
    char *arg;
    char *extra;
    unsigned i, j, index, index1;
    char *cester_option = CESTER_NULL;
#ifdef _WIN32
#ifndef CESTER_EXCLUDE_WINDOWS_H
	CONSOLE_SCREEN_BUFFER_INFO info;
	if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) {
	    default_color = info.wAttributes;
	}
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
#endif
    cester_set_captured_streams_tmp_folder(getenv("TEMP"), (char *)"C:/libcester_tmp/");
#else
    cester_set_captured_streams_tmp_folder(getenv("TMPDIR"), (char *)"/tmp/libcester_tmp/");
#endif

#ifndef CESTER_NO_SIGNAL    
    cester_capture_signals();
#endif

    i = 0; 
    j = 1;
    superTestInstance.output_format = CESTER_NULL;
    if (superTestInstance.output_stream==CESTER_NULL) {
        superTestInstance.output_stream = stdout;
        cester_ptr_to_str(&(superTestInstance.output_stream_str), stdout); 
        superTestInstance.output_stream_address = *stdout;
    }
#ifndef CESTER_NO_MEM_TEST
	if (superTestInstance.mem_alloc_manager == CESTER_NULL) {
	    if (cester_array_init(&superTestInstance.mem_alloc_manager) == 0) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Unable to initialize the memory management array. Memory test disabled.\n");
            superTestInstance.mem_test_active = 0;
	    }
	}
#endif
    if (superTestInstance.registered_test_cases == CESTER_NULL) {
        if (cester_array_init(&superTestInstance.registered_test_cases) == 0) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), "Unable to initialize the registered test cases array. Cannot continue tests.\n");
            return CESTER_RESULT_FAILURE;
        }
    }

    /* resolve command line options */
    for (;j < argc; ++j) {
        arg = argv[j];
        if (cester_str_after_prefix(arg, (char*) "--cester-", 9, &cester_option) == 1) {
            if (cester_string_equals(cester_option, (char*) "minimal") == 1) {
                superTestInstance.verbose_level = 0;

            } else if (cester_string_equals(cester_option, (char*) "verbose") == 1) {
                superTestInstance.verbose_level = 10;
                superTestInstance.print_error_only = 0;

            } else if (cester_string_equals(cester_option, (char*) "nocolor") == 1) {
                superTestInstance.no_color = 1;

            } else if (cester_string_equals(cester_option, (char*) "printversion") == 1) {
                superTestInstance.print_version = 1;

            } else if (cester_string_equals(cester_option, (char*) "singleoutput") == 1) {
                superTestInstance.single_output_only = 1;

            } else if (cester_string_equals(cester_option, (char*) "noisolation") == 1) {
                superTestInstance.isolate_tests = 0;

            } else if (cester_string_equals(cester_option, (char*) "dontformatname") == 1) {
                superTestInstance.format_test_name = 0;
#ifndef CESTER_NO_MEM_TEST
            } else if (cester_string_equals(cester_option, (char*) "nomemtest") == 1) {
                superTestInstance.mem_test_active = 0;
#endif
            } else if (cester_string_equals(cester_option, (char*) "version") == 1) {
                CESTER_NOCOLOR();
                cester_print_version();
                free(cester_option);
                cester_cleanup_super_instance();
                return EXIT_SUCCESS;

            } else if (cester_string_equals(cester_option, (char*) "help") == 1) {
                CESTER_NOCOLOR();
                cester_print_version();
                cester_print_help();
                free(cester_option);
                cester_cleanup_super_instance();
                return EXIT_SUCCESS;

            } else if (cester_string_starts_with(cester_option, (char*) "test=") == 1) {
                unpack_selected_extra_args(cester_option, &superTestInstance.selected_test_cases_names, &superTestInstance.selected_test_cases_size);

            } else if (cester_string_starts_with(cester_option, (char*) "verbose-level=") == 1) {
                cester_str_value_after_first(cester_option, '=', &extra);
                superTestInstance.verbose_level = atoi(extra);
                free(extra);
                if (superTestInstance.verbose_level >= 10) {
                    superTestInstance.print_error_only = 0;
                }

            } else if (cester_string_starts_with(cester_option, (char*) "output=") == 1) {
                cester_str_value_after_first(cester_option, '=', &superTestInstance.output_format);
                if (cester_is_validate_output_option(superTestInstance.output_format) == 0) {
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), "Invalid cester output format: ");
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), superTestInstance.output_format);
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), "\n");
                    if (cester_string_starts_with(superTestInstance.output_format, (char*) "tap")) {
                        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Did you mean 'tap' or 'tapV13?'\n");
                    }
                    CESTER_RESET_TERMINAL_ATTR()
                    free(cester_option);
                    return EXIT_FAILURE;
                }

            } else {
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), "Invalid cester option: --cester-");
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), cester_option);
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), "\n");
                CESTER_RESET_TERMINAL_ATTR()
                free(cester_option);
                return EXIT_FAILURE;
            }
            if (cester_option != CESTER_NULL) {
                free(cester_option);
                cester_option = CESTER_NULL;
            }
        } else {
            if (strlen(argv[j]) != 0) {
                cester_concat_str(&superTestInstance.flattened_cmd_argv, argv[j]);
                cester_concat_str(&superTestInstance.flattened_cmd_argv, " ");
            }
        }
    }

    if (superTestInstance.print_version == 1) {
        cester_print_version();
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
        CESTER_RESET_TERMINAL_ATTR();
    }

    superTestInstance.test_instance = (TestInstance*) malloc(sizeof(TestInstance));
    superTestInstance.test_instance->argc = argc;
    superTestInstance.test_instance->argv = argv;

    /* execute options */
    for (i=0;cester_test_cases[i].test_type != CESTER_TESTS_TERMINATOR;++i) {
        if ((cester_test_cases[i].test_type == CESTER_OPTIONS_FUNCTION || cester_test_cases[i].test_type == CESTER_TEST_FILE_COMMENT) && 
            superTestInstance.single_output_only == 0) {
            superTestInstance.current_cester_function_type = CESTER_OPTIONS_FUNCTION;
            ((cester_void)cester_test_cases[i].test_void_function)();

        } else if ((cester_test_cases[i].test_type == CESTER_NORMAL_TEST ||
               cester_test_cases[i].test_type == CESTER_NORMAL_TODO_TEST ||
               cester_test_cases[i].test_type == CESTER_NORMAL_SKIP_TEST) &&
               superTestInstance.registered_test_cases->size == 0) {

            ++superTestInstance.total_tests_count;
        }

    }

    CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index, test_case, {
        if ((((TestCase*)test_case)->test_type == CESTER_OPTIONS_FUNCTION || ((TestCase*)test_case)->test_type == CESTER_TEST_FILE_COMMENT) && 
            superTestInstance.single_output_only == 0) {
            superTestInstance.current_cester_function_type = CESTER_OPTIONS_FUNCTION;
            ((cester_void)((TestCase*)test_case)->test_void_function)();

        } else if (((TestCase*)test_case)->test_type == CESTER_NORMAL_TEST ||
               ((TestCase*)test_case)->test_type == CESTER_NORMAL_TODO_TEST ||
               ((TestCase*)test_case)->test_type == CESTER_NORMAL_SKIP_TEST) {

            ++superTestInstance.total_tests_count;
        }
    })

    /* before all */
    if (superTestInstance.registered_test_cases->size == 0) {
        for (i=0;cester_test_cases[i].test_type != CESTER_TESTS_TERMINATOR;++i) {
            if (cester_test_cases[i].test_type == CESTER_BEFORE_ALL_TEST && superTestInstance.single_output_only == 0) {
                superTestInstance.current_cester_function_type = CESTER_BEFORE_ALL_TEST;
                ((cester_test)cester_test_cases[i].test_function)(superTestInstance.test_instance);
            }
        }
    }
    CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index1, test_case, {
        if (((TestCase*)test_case)->test_type == CESTER_BEFORE_ALL_TEST && superTestInstance.single_output_only == 0) {
            superTestInstance.current_cester_function_type = CESTER_BEFORE_ALL_TEST;
            ((cester_test)((TestCase*)test_case)->test_function)(superTestInstance.test_instance);
        }
    })
    
    #ifndef CESTER_NO_TIME
        superTestInstance.start_tic = clock();
    #endif
    cester_run_all_test_iterator(0);
    
    return cester_print_result(cester_test_cases, superTestInstance.test_instance);
}

#ifndef CESTER_NO_MAIN
int main(int argc, char **argv) {
    return CESTER_RUN_ALL_TESTS(argc, argv);
}
#endif

#ifndef CESTER_NO_SIGNAL
void cester_capture_signals() {
    signal(SIGINT , cester_recover_on_signal);
    signal(SIGABRT , cester_recover_on_signal);
    signal(SIGILL , cester_recover_on_signal);
    signal(SIGFPE , cester_recover_on_signal);
    signal(SIGSEGV, cester_recover_on_signal);
    signal(SIGTERM , cester_recover_on_signal);
}

/* This is still faulty it works for SIGSEGV 
but SIGINT just crash to my face. So I will 
manually try to recover the test instead of using 
longjmp and setjmp which is behaving 
inconsistently. This still messes up for more 
than 2 crashes 
 */
void cester_recover_on_signal(int sig_num) {
    cester_capture_signals();
    switch (sig_num) {
#ifndef CESTER_NO_MEM_TEST
        case SIGILL:
            superTestInstance.current_execution_status = CESTER_RESULT_MEMORY_LEAK;
            break;
#endif
        case SIGSEGV:
            superTestInstance.current_execution_status = CESTER_RESULT_SEGFAULT;
            break;
        case SIGINT: /* this is one crazy kill signal */
            if (superTestInstance.isolate_tests == 1) {
                return;
            }
            superTestInstance.current_execution_status = CESTER_RESULT_TERMINATED;
            cester_report_single_test_result(superTestInstance.current_execution_status, superTestInstance.current_test_case);
            cester_run_all_test_iterator(0);
            exit(cester_print_result(cester_test_cases, superTestInstance.test_instance));
            break;
        case SIGFPE:
        case SIGTERM:
        case SIGABRT:
            superTestInstance.current_execution_status = CESTER_RESULT_FAILURE;
            break;
    }
    longjmp(buf, 1);
    
}
#endif

/* CesterArray */

static __CESTER_INLINE__ unsigned cester_array_init(CesterArray** out) {
    void **buffer;
    CesterArray* array_local = (CesterArray*) malloc(sizeof(CesterArray));
    if (!array_local) {
        return 0;
    }
    array_local->size = 0;
    array_local->capacity = CESTER_ARRAY_INITIAL_CAPACITY;
    buffer = (void**) malloc(sizeof(void*) * array_local->capacity);
    if (!buffer) {
        free(array_local);
        return 0;
    }
    array_local->buffer = buffer;
    *out = array_local;
    return 1;
}

static __CESTER_INLINE__ unsigned cester_array_add(CesterArray* array, void* item) {
    void** new_buffer;
    if (array->size >= array->capacity) {
        if (array->capacity >= CESTER_ARRAY_MAX_CAPACITY) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Max managable memory allocation reached, cannot expand array. Further Memory test disabled.\n");
            superTestInstance.mem_test_active = 0;
            return 0;
        }
        array->capacity = array->capacity + CESTER_ARRAY_INITIAL_CAPACITY;
        new_buffer = (void**) malloc(sizeof(void*) * array->capacity);
        if (!new_buffer) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Failed to expand the memory allocation array. Further Memory test disabled.\n");
            superTestInstance.mem_test_active = 0;
            return 0;
        }
        memcpy(new_buffer, array->buffer, array->size * sizeof(void*));
        free(array->buffer);
        array->buffer = new_buffer;
    }
    array->buffer[array->size] = item;
    ++array->size;
    return 1;
}

static __CESTER_INLINE__ void* cester_array_remove_at(CesterArray* array, size_t index) {
    void* item;
    if (index >= array->size) {
        return CESTER_NULL;
    }
    item = array->buffer[index];
    if (index != array->size - 1) {
        size_t block_size = (array->size - 1 - index) * sizeof(void*);
        memmove(&(array->buffer[index]),
                &(array->buffer[index + 1]),
                block_size);
    }
    array->size--;
    return item;
}

static __CESTER_INLINE__ void cester_array_destroy(CesterArray* array) {
    free(array->buffer);
    free(array);
}

/* Memory leak Detection procedures */

#ifndef CESTER_NO_MEM_TEST

static __CESTER_INLINE__ void* cester_allocator(size_t nitems, size_t size, unsigned type, const char *file, unsigned line, const char *func) {
    void* p;
    const char* actual_function_name;
#ifndef __CESTER_STDC_VERSION__
    if (superTestInstance.current_test_case != CESTER_NULL) {
        actual_function_name = superTestInstance.current_test_case->name;
    } else {
        actual_function_name = func;
    }
#else 
    actual_function_name = func;
#endif
    if (superTestInstance.current_cester_function_type == CESTER_BEFORE_ALL_TEST) {
        actual_function_name = "CESTER_BEFORE_ALL";
        
    } else if (superTestInstance.current_cester_function_type == CESTER_OPTIONS_FUNCTION) {
        actual_function_name = "CESTER_OPTIONS";
        
    } else if (superTestInstance.current_cester_function_type == CESTER_BEFORE_EACH_TEST) {
        actual_function_name = "CESTER_BEFORE_EACH";
        
    }
    if (superTestInstance.mem_test_active == 1) {
        if (superTestInstance.mem_alloc_manager == CESTER_NULL) {
            if (cester_array_init(&superTestInstance.mem_alloc_manager) == 0) {
                if (superTestInstance.output_stream==CESTER_NULL) {
                    superTestInstance.output_stream = stdout;
                    cester_ptr_to_str(&(superTestInstance.output_stream_str), stdout); 
                    superTestInstance.output_stream_address = *stdout;
                }
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Unable to initialize the memory management array. Memory test disabled.\n");
                superTestInstance.mem_test_active = 0;
            }
        }
    }
    switch (type) {
        case 1:
            p = calloc(nitems, size);
            break;
        case 0:
        default:
            p = malloc(size);
    }
    if (superTestInstance.mem_test_active == 1) {
        AllocatedMemory* allocated_mem = (AllocatedMemory*) malloc(sizeof(AllocatedMemory));
        allocated_mem->line_num = line;
        allocated_mem->allocated_bytes = size;
        allocated_mem->function_name_allocated = 1;
        if (cester_str_after_prefix(actual_function_name, (char*) "cester_test_", 12, (char **) &(allocated_mem->function_name)) == 0) {
            allocated_mem->function_name = (char *) actual_function_name;
            allocated_mem->function_name_allocated = 0;
        }
        allocated_mem->file_name = file;
        cester_ptr_to_str(&allocated_mem->address, p);
        if (cester_array_add(superTestInstance.mem_alloc_manager, allocated_mem) == 0) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Failed to register allocated memory. Memory test disabled.\n");
            superTestInstance.mem_test_active = 0;
        }
    }
    return p;
}

static __CESTER_INLINE__ void cester_free(void *pointer, const char *file, unsigned line, const char *func) {
    unsigned index;
    char *cleaned_name = (char *) (superTestInstance.verbose_level >= 4 ? superTestInstance.test_file_path : cester_extract_name(superTestInstance.test_file_path) );
    if (pointer == CESTER_NULL) {
        if (superTestInstance.mem_test_active == 1 && superTestInstance.current_test_case != CESTER_NULL) {
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "InvalidOperation ");
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, cleaned_name);
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ":");
            cester_concat_int(&(superTestInstance.current_test_case)->execution_output, line);
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ": ");
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "in '");
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, (superTestInstance.current_test_case)->name);
            if (superTestInstance.verbose_level >= 2) {
                cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "' => Attempting to free a CESTER_NULL pointer");
            }
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "\n");
            superTestInstance.current_execution_status = CESTER_RESULT_MEMORY_LEAK;
        }
        if (superTestInstance.verbose_level < 4) {
            free(cleaned_name);
        }
        return;
    }
    if (superTestInstance.mem_test_active == 1) {
        char* address;
        cester_ptr_to_str(&address, pointer);
        CESTER_ARRAY_FOREACH(superTestInstance.mem_alloc_manager, index, alloc_mem, {
            if (cester_string_equals(((AllocatedMemory*)alloc_mem)->address, address) == 1) {
                if (!cester_array_remove_at(superTestInstance.mem_alloc_manager, index)) {
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Memory allocation array corrupted. Further Memory test disabled.\n");
                    superTestInstance.mem_test_active = 0;
                }
                if (((AllocatedMemory*)alloc_mem)->function_name_allocated == 1) {
                    free(((AllocatedMemory*)alloc_mem)->function_name);
                }
                free(((AllocatedMemory*)alloc_mem)->address);
                free(alloc_mem);
                break;
            }
        })
        free(address);
    }
    if (superTestInstance.verbose_level < 4) {
        free(cleaned_name);
    }
    free(pointer);
}

#define malloc(x) cester_allocator( 0, x, 0, __FILE__, __LINE__, __CESTER_FUNCTION__) /**< Override the default malloc function for mem test */
#define calloc(x,y) cester_allocator( x, y, 1, __FILE__, __LINE__, __CESTER_FUNCTION__) /**< Override the default malloc function for mem test */
#define free(x) cester_free( x, __FILE__, __LINE__, __CESTER_FUNCTION__)     /**< Override the default free function for mem test   */
#endif

#ifdef __cplusplus
}
#endif

#endif
