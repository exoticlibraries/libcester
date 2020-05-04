
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2020, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 10 April 2020
    \file cester.h
*/

/**
    Cester is a header only unit testing framework for C. The header 
    file can be downloaded and placed in a project folder or can be 
    used as part of libopen library by including it in the projects 
    like `<libopen/cester.h>`. 
    
    A single test file is considered a test suite in cester, a single 
    test file should contain related tests functions only. 
*/

#ifndef LIBOPEN_CESTER_H
#define LIBOPEN_CESTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#ifndef __BASE_FILE__
#ifdef _MSC_VER
    #pragma message("__BASE_FILE__ not defined. Define the __BASE_FILE__ directive in Properties -> C/C++ -> Preprocessor -> Preprocessor Definition as __BASE_FILE__=\"%(Filename)%(Extension)\" or register your test cases manually.")
#else
    #pragma message("__BASE_FILE__ not defined. Define __BASE_FILE__ during compilation. -D__BASE_FILE__=\"/the/path/to/yout/testfile.c\" or register your test cases manually.")
#endif
#endif

#ifdef _WIN32
#include <windows.h>
/*
**  Windows 
**  Support Windows XP 
**  To avoid error message : procedure entry point **  InitializeConditionVariable could not be located **  in Kernel32.dll 
*/
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif
#define _WIN32_WINNT 0x502
#define LIBOTYPES_WINDLLEXPORT 1
/* Linux */
#else
#define LIBOTYPES_WINDLLEXPORT 0
#endif
#if LIBOTYPES_WINDLLEXPORT
#define LIBEXOTIC_API __declspec(dllexport)
#else
#define LIBEXOTIC_API extern
#endif

#ifdef unix
#include <unistd.h>
#include <sys/wait.h>
#endif

#ifdef _WIN32

#define CESTER_RESET_TERMINAL           15                                                ///< reset the terminal color //Nothing
#define CESTER_BOLD                     15                                                ///< bold text                //Nothing
#define CESTER_FOREGROUND_BLACK         8                                                 ///< gray terminal foreground color
#define CESTER_FOREGROUND_RED           4                                                 ///< red terminal foreground color
#define CESTER_FOREGROUND_GREEN         2                                                 ///< green foreground color
#define CESTER_FOREGROUND_YELLOW        6                                                 ///< yellow terminal foreground color
#define CESTER_FOREGROUND_BLUE          3                                                 ///< blue terminal foreground color
#define CESTER_FOREGROUND_MAGENTA       5                                                 ///< magenta terminal foreground color
#define CESTER_FOREGROUND_CYAN          11                                                ///< cyan terminal foreground color
#define CESTER_FOREGROUND_WHITE         15                                                ///< white terminal foreground color
#define CESTER_FOREGROUND_GRAY          8                                                 ///< gray terminal foreground color
#define CESTER_BACKGROUND_BLACK         0                                                 ///< black terminal background color
#define CESTER_BACKGROUND_RED           64                                                ///< red terminal background color
#define CESTER_BACKGROUND_GREEN         39                                                ///< green terminal background color
#define CESTER_BACKGROUND_YELLOW        96                                                ///< yellow terminal background color
#define CESTER_BACKGROUND_BLUE          48                                                ///< blue terminal background color
#define CESTER_BACKGROUND_MAGENTA       87                                                ///< magenta terminal background color
#define CESTER_BACKGROUND_CYAN          176                                               ///< cyan terminal background color
#define CESTER_BACKGROUND_GRAY          0                                                 ///< gray terminal background color
#define CESTER_BACKGROUND_WHITE         10                                                ///< gray terminal background color
#define CESTER_RESET_TERMINAL_ATTR()    SetConsoleTextAttribute(hConsole, default_color); ///< reset the terminal color

#else
    
#define CESTER_RESET_TERMINAL           "\x1B[0m"     ///< reset the terminal color
#define CESTER_BOLD                     "\x1B[1m"     ///< bold text 
#define CESTER_FOREGROUND_BLACK         "\x1B[30m"    ///< gray terminal foreground color
#define CESTER_FOREGROUND_RED           "\x1B[31m"    ///< red terminal foreground color
#define CESTER_FOREGROUND_GREEN         "\x1B[32m"    ///< green foreground color
#define CESTER_FOREGROUND_YELLOW        "\x1B[33m"    ///< yellow terminal foreground color
#define CESTER_FOREGROUND_BLUE          "\x1B[34m"    ///< blue terminal foreground color
#define CESTER_FOREGROUND_MAGENTA       "\x1B[35m"    ///< magenta terminal foreground color
#define CESTER_FOREGROUND_CYAN          "\x1B[36m"    ///< cyan terminal foreground color
#define CESTER_FOREGROUND_WHITE         "\x1B[37m"    ///< white terminal foreground color
#define CESTER_FOREGROUND_GRAY          "\x1B[90m"    ///< gray terminal foreground color
#define CESTER_BACKGROUND_BLACK         "\x1B[40m"    ///< black terminal background color
#define CESTER_BACKGROUND_RED           "\x1B[41m"    ///< red terminal background color
#define CESTER_BACKGROUND_GREEN         "\x1B[42m"    ///< green terminal background color
#define CESTER_BACKGROUND_YELLOW        "\x1B[43m"    ///< yellow terminal background color
#define CESTER_BACKGROUND_BLUE          "\x1B[44m"    ///< blue terminal background color
#define CESTER_BACKGROUND_MAGENTA       "\x1B[45m"    ///< magenta terminal background color
#define CESTER_BACKGROUND_CYAN          "\x1B[46m"    ///< cyan terminal background color
#define CESTER_BACKGROUND_GRAY          "\x1B[100m"   ///< gray terminal background color
#define CESTER_BACKGROUND_WHITE         "\x1B[47m"    ///< gray terminal background color
#define CESTER_RESET_TERMINAL_ATTR()    ;             ///< reset the terminal color

#endif

/**
    Cester current version
*/
#define CESTER_VERSION "0.2"

/**
    Cester License
*/
#define CESTER_LICENSE "GNU General Public License v3.0"

#define CESTER_HASH_SIGN #
#define CESTER_CONCAT(x, y) x y

enum cheat_test_status {
    CESTER_RESULT_SUCCESS,
    CESTER_RESULT_FAILURE,
    CESTER_RESULT_TERMINATED,
    CESTER_RESULT_SEGFAULT,
    CESTER_RESULT_MEMORY_LEAK,
    CESTER_RESULT_UNKNOWN
};

/**
    The type of test
*/
typedef enum cester_test_type {
    CESTER_NORMAL_TEST,             ///< normal test in global or test suite. For internal use only.
    CESTER_NORMAL_TODO_TEST,        ///< test to be implemented in future. For internal use only.
    CESTER_NORMAL_SKIP_TEST,        ///< test to be skipped. For internal use only.
    CESTER_BEFORE_ALL_TEST,         ///< test to run before all normal tests in global or test suite. For internal use only.
    CESTER_BEFORE_EACH_TEST,        ///< test to run before each normal tests in global or test suite. For internal use only.
    CESTER_AFTER_ALL_TEST,          ///< test to run after all normal tests in global or test suite. For internal use only.
    CESTER_AFTER_EACH_TEST,         ///< test to run after each normal tests in global or test suite. For internal use only.
    CESTER_OPTIONS_FUNCTION,        ///< the cester function for test, this wil be excuted before running the tests. For internal use only.
    CESTER_TESTS_TERMINATOR         ///< the last value in the test cases to terminates the tests. For internal use only.
} TestType;

typedef struct test_case {
    size_t execution_status;     ///< the test execution result status. For internal use only.
    size_t line_num;             ///< the line number where the test case is created. For internal use only.
    double execution_time;       ///< the time taken for the test case to complete. For internal use only.
    char* execution_output;      ///< the test execution output in string. For internal use only.
    void *function;              ///< the function that enclosed the tests. For internal use only.
    char *name;                  ///< the test function name. For internal use only.
    TestType test_type;          ///< the type of the test function
} TestCase;

#ifndef CESTER_NO_MEM_TEST

typedef struct allocated_memory {
    size_t line_num;
    size_t allocated_bytes;
    char* address;
    const char* function_name;
    const char* file_name;
} AllocatedMemory;

#endif

#define CESTER_ARRAY_INITIAL_CAPACITY 30
#define CESTER_ARRAY_MAX_CAPACITY ((size_t) - 5)

typedef struct mem_alloc_man {
    size_t size;
    size_t capacity;
    void** buffer;
} CesterArray;


#define CESTER_ARRAY_FOREACH(w,x,y,z) size_t x;\
                                      for (x = 0; x < w->size; ++x) {\
                                          void* y = w->buffer[x];\
                                          z\
                                      }

/**
    This structure manages the _BEFORE_ and _AFTER_ functions 
    for the test main ::test_instance. And also accounts for all the 
    registered test cases. This is for Cester internal use only.
*/
typedef struct super_test_instance {
    size_t no_color;                                    ///< Do not print to the console with color if one. For internal use only.
    size_t total_tests_count;                           ///< the total number of tests to run, assert, eval e.t.c. To use in your code call CESTER_TOTAL_TESTS_COUNT
    size_t total_failed_tests_count;                    ///< the total number of tests that failed. To use in your code call CESTER_TOTAL_FAILED_TESTS_COUNT
    size_t total_passed_tests_count;                    ///< the total number of tests that passed. To use in your code call CESTER_TOTAL_FAILED_TESTS_COUNT
    size_t verbose;                                     ///< prints as much info as possible into the output stream
    size_t minimal;                                     ///< prints minimal output into the output stream
    size_t print_version;                               ///< prints cester version before running tests
    size_t selected_test_cases_size;                    ///< the number of selected test casses from command line. For internal use only.
    size_t selected_test_cases_found;                   ///< the number of selected test casses from command line that is found in the test file. For internal use only.
    size_t single_output_only;                          ///< display the output for a single test only no summary and syntesis. For internal use only.
    size_t mem_test_active;                             ///< Enable or disable memory test at runtime. Enabled by default. For internal use only.
    size_t current_execution_status;                    ///< the current test case status. This is used when the test cases run on a single process. For internal use only.
    size_t isolate_tests;                               ///< Isolate each test case to run in different process to prevent a crashing test case from crahsing others. For internal use only.
    size_t skipped_test_count;                          ///< The number of test cases to be skipped. For internal use only.
    size_t todo_tests_count;                            ///< The number of test cases that would be implemented in future. For internal use only.
    size_t format_test_name;                            ///< Format the test name for fine output e.g. 'test_file_exit' becomes 'test file exist'. For internal use only.
    char* flattened_cmd_argv;                           ///< Flattened command line argument for sub process. For internal use only.
    char* test_file_path;                               ///< The main test file full path. For internal use only.
    char* output_format;                                ///< The output format to print the test result in. For internal use only.
    FILE* output_stream;                                ///< Output stream to write message to, stdout by default. For internal use only.
    char** selected_test_cases_names;                   ///< selected test cases from command line. For internal use only. e.g. --cester-test=Test2,Test1
    TestCase* current_test_case;                        ///< The currently running test case. For internal use only.
    CesterArray *registered_test_cases;                 ///< all the manually registered test cases in the instance. For internal use only.
#ifndef CESTER_NO_MEM_TEST
    CesterArray* mem_alloc_manager;                     ///< the array of allocated memory. For testing and detecting memory leaks. For internal use only.
#endif
} SuperTestInstance;

/**
    The test instance that contains the command line argument 
    length and values, with void* pointer that can be used to 
    share data between unit tests.
*/
typedef struct test_instance {
    size_t argc;                   ///< the length of the command line arg
    char **argv;                   ///< the command line arguments 
    void *arg;                     ///< pointer to an object that can be passed between unit tests
} TestInstance;

/**
    The function signature for each test case. It accepts the ::test_instance 
    as it only argument. 
*/
typedef void (*cester_test)(TestInstance*);
typedef void (*cester_before_after_each)(TestInstance*, char * const, size_t);
typedef void (*cester_void)();

// CesterArray
static inline size_t cester_array_init(CesterArray**);
static inline size_t cester_array_add(CesterArray*, void*);
static inline void* cester_array_remove_at(CesterArray*, size_t);

static inline size_t cester_run_all_test(size_t, char **);
static inline void cester_str_value_after_first(char *, char, char**);


SuperTestInstance superTestInstance = { 
    0,
    0,
    0,
    0,
    0,
    0,
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
    (char*)"",
#ifdef __BASE_FILE__
    (char*)__BASE_FILE__,
#else
    (char*)__FILE__
#endif
    (char*)"text",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL
};

#ifdef _MSC_VER
#define cester_sprintf(x,y,z,...) sprintf_s(x, y, z, __VA_ARGS__);
#else
#define cester_sprintf(x,y,z,...) sprintf(x, z, __VA_ARGS__);
#endif


// cester options

/**
    Change the output stream used by cester to write data. The default is `stdout`. 
    E.g to change the output stream to a file. 
    
    \code{.c} 
    CESTER_CHANGE_STREAM(fopen("./test.txt", "w+"));
    \endcode
    
    The code above changes the stream to a file test.txt, all the output from 
    the test will be written in the file.
**/
#define CESTER_CHANGE_STREAM(x) (superTestInstance.output_stream = x)

/**
    Do not print to the output stream with color. This should be 
    used to prevent writing the color bytes into a file stream (in case).
    
    This option can also be set from the command line with `--cester-nocolor`
*/
#define CESTER_NOCOLOR() (superTestInstance.no_color = 1)

/**
    Print minimal info into the output stream. With this option set the 
    expression evaluated will not be printed in the result output. 
    
    This option can also be set from the command line with `--cester-minimal`
*/
#define CESTER_MINIMAL() (superTestInstance.minimal = 1)

/**
    Print as much info as possible into the output stream. With this option set  
    both passed and failed expression evaluated will be printed in the result. 
    
    This option can also be set from the command line with `--cester-verbose`
*/
#define CESTER_VERBOSE() (superTestInstance.verbose = 1)

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
    Disable memory allocation.
    
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
    Change the output format to junitxml
*/
#define CESTER_OUTPUT_JUNITXML() superTestInstance.output_format = (char*) "junitxml";

/**
    Change the output format to TAP (Test Anything Protocol)
*/
#define CESTER_OUTPUT_TAP() superTestInstance.output_format = (char*) "tap";

/**
    Change the output format to TAP (Test Anything Protocol)
*/
#define CESTER_OUTPUT_TAPV13() superTestInstance.output_format = (char*) "tapV13";

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

// test counts

/**
    The total number of tests that will be run.
*/
#define CESTER_TOTAL_TESTS_COUNT (superTestInstance.total_tests_count)

/**
    The total number of tests that failed.
*/
#define CESTER_TOTAL_FAILED_TESTS_COUNT (superTestInstance.total_failed_tests_count)

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
    The total number of tests that passed. CESTER_TOTAL_TESTS_COUNT - CESTER_TOTAL_FAILED_TESTS_COUNT
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

#ifdef _WIN32
    int default_color = CESTER_RESET_TERMINAL;
    HANDLE hConsole;
#else
    const char* default_color = CESTER_RESET_TERMINAL;
#endif

static inline char *cester_extract_name(char const* const file_path) {
    size_t i = 0, j = 0;
    size_t found_seperator = 0;
    char *file_name_only = (char*) malloc (sizeof (char) * 30);
    while (file_path[i] != '\0') {
        if (file_path[i] == '\\' || file_path[i] == '/') {
            found_seperator = 1;
            j = 0;
        } else {
            found_seperator = 0;
            file_name_only[j] = file_path[i];
            j++;
        }
        ++i;
    }
    file_name_only[j] = '\0';
    return file_name_only;
}

static inline char *cester_extract_name_only(char const* const file_path) {
    size_t i = 0;
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

static inline size_t cester_str_after_prefix(const char* arg, char* prefix, size_t prefix_size, char** out) {
    size_t i = 0;
    *out = (char*) malloc (sizeof (char) * 200);
    
    while (1) {
        if (arg[i] == '\0') {
            if (i < prefix_size) {
                free(*out);
                return 0;
            } else {
                break;
            }
        }
        if (arg[i] != prefix[i] && i < prefix_size) {
            free(*out);
            return 0;
        }
        if (i >= prefix_size) {
            (*out)[i-prefix_size] = arg[i];
        }
        ++i;
    }
    (*out)[i-prefix_size] = '\0';
    return 1;
}

static inline char* cester_str_replace(char* str, char old_char, char new_char) {
    char* tmp = (char*) malloc(strlen(str) + 1);
    size_t index = 0;
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

static inline size_t cester_string_equals(char* arg, char* arg1) {
    size_t i = 0;
    if (arg == NULL || arg1 == NULL) {
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

static inline size_t cester_string_starts_with(char* arg, char* arg1) {
    size_t i = 0;
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

static inline void unpack_selected_extra_args(char *arg, char*** out, size_t* out_size) {
    size_t i = 0;
    size_t size = 0, current_index = 0;
    char* prefix = (char*) "test=";
    (*out) = (char**) malloc(sizeof(char**));
    
    (*out)[size] = (char*) malloc(sizeof(char*) * 200);
    while (1) {
        if (arg[i] == '\0') {
            ++size;
            break;
        }
        if (arg[i] != prefix[i] && i < 5) {
            break;
        }
        if (arg[i] == ',') {
            (*out)[size][current_index] = '\0';
            current_index = 0;
            ++size;
            (*out)[size] = (char*) malloc(sizeof(char*) * 200);
            goto continue_loop;
        }
        if (i >= 5) {
            (*out)[size][current_index] = arg[i];
            ++current_index;
        }
        continue_loop:
                      ++i;
    }
    (*out)[size-1][current_index] = '\0';
    *out_size = size;
}

static inline void cester_str_value_after_first(char *arg, char from, char** out) {
    size_t i = 0, index = 0;
    size_t found_char = 0;
    *out = (char*) malloc(sizeof(char) * 200);
    while (1) {
        if (arg[i] == '\0') {
            break;
        }
        if (arg[i] == from) {
            found_char = 1;
            goto continue_loop;
        }
        if (found_char == 1) {
            (*out)[index] = arg[i];
            ++index;
        }
        continue_loop:
                      ++i;
    }
    (*out)[index] = '\0';
}

static inline void cester_concat_str(char **out, const char * extra) {
    size_t i = 0, index = strlen(*out);
    if (index == 0) {
        (*out) = (char*) malloc(sizeof(char) * 80000 );
    }
    if (extra == NULL) {
        extra = "(null)";
    }
    while (1) {
        if (extra[i] == '\0') {
            break;
        }
        (*out)[index] = extra[i];
        ++index;
        ++i;
    }
    (*out)[index] = '\0';
}

static inline void cester_concat_char(char **out, char extra) {
    size_t i = 0, index = strlen(*out);
    if (index == 0) {
        (*out) = (char*) malloc(sizeof(char) * 80000 );
    }
    cester_sprintf((*out), (index + 5), "%s%c", (*out), extra);
}

static inline void cester_concat_int(char **out, size_t extra) {
    size_t i = 0, index = strlen(*out);
    if (index == 0) {
        (*out) = (char*) malloc(sizeof(char) * 80000 );
    }
    cester_sprintf((*out), (index + 20), "%s%zu", (*out), extra);
}

static inline void cester_ptr_to_str(char **out, void* extra) {
    size_t i = 0;
    (*out) = (char*) malloc(sizeof(char) * 30 );
    cester_sprintf((*out), (30), "%s%p", (*out), extra);
}

static inline size_t cester_is_validate_output_option(char *format_option) {
    return (cester_string_equals(format_option, (char*) "junitxml") ||  
            cester_string_equals(format_option, (char*) "tap") ||  
            cester_string_equals(format_option, (char*) "tapV13") ||  
            cester_string_equals(format_option, (char*) "text"));
}

#define CESTER_SELECTCOLOR(x) (superTestInstance.no_color == 1 ? default_color : x)
#define CESTER_GET_RESULT_AGGR (superTestInstance.total_failed_tests_count == 0 ? "SUCCESS" : "FAILURE")
#define CESTER_GET_RESULT_AGGR_COLOR (superTestInstance.total_failed_tests_count == 0 ? (CESTER_FOREGROUND_GREEN) : (CESTER_FOREGROUND_RED))

#ifdef _WIN32
#define CESTER_DELEGATE_FPRINT_STR(x,y) SetConsoleTextAttribute(hConsole, CESTER_SELECTCOLOR(x)); fprintf(superTestInstance.output_stream, "%s", y)
#define CESTER_DELEGATE_FPRINT_INT(x,y) SetConsoleTextAttribute(hConsole, CESTER_SELECTCOLOR(x)); fprintf(superTestInstance.output_stream, "%zu", y)
#define CESTER_DELEGATE_FPRINT_DOUBLE(x,y) SetConsoleTextAttribute(hConsole, CESTER_SELECTCOLOR(x)); fprintf(superTestInstance.output_stream, "%f", y)
#define CESTER_DELEGATE_FPRINT_DOUBLE_2(x,y) SetConsoleTextAttribute(hConsole, CESTER_SELECTCOLOR(x)); fprintf(superTestInstance.output_stream, "%.2f", y)
#else
#define CESTER_DELEGATE_FPRINT_STR(x,y) fprintf(superTestInstance.output_stream, "%s%s%s", CESTER_SELECTCOLOR(x), y, CESTER_RESET_TERMINAL)
#define CESTER_DELEGATE_FPRINT_INT(x,y) fprintf(superTestInstance.output_stream, "%s%zu%s", CESTER_SELECTCOLOR(x), y, CESTER_RESET_TERMINAL)
#define CESTER_DELEGATE_FPRINT_DOUBLE(x,y) fprintf(superTestInstance.output_stream, "%s%f%s", CESTER_SELECTCOLOR(x), y, CESTER_RESET_TERMINAL) 
#define CESTER_DELEGATE_FPRINT_DOUBLE_2(x,y) fprintf(superTestInstance.output_stream, "%s%.2f%s", CESTER_SELECTCOLOR(x), y, CESTER_RESET_TERMINAL) 
#endif

static inline size_t cester_string_equals(char* arg, char* arg1);

static inline void cester_print_version() {
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "CESTER v");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), CESTER_VERSION);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), CESTER_LICENSE);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
}

static inline void cester_print_help() {
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "Usage: ./testfile [-options] [args...]\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\nwhere options include:\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-minimal         print minimal info into the output stream\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-verbose         print as much info as possible into the output stream\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-nocolor         do not print info with coloring\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-singleoutput    display cester version and exit\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-nomemtest       disable memory leak detection in the tests\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-noisolation     run all the test on a single process. Prevents recovery from crash.\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-printversion    display cester version before running the tests\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-dontformatname  leave the test case name as declared in the source file in the output\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-test=Test1,...  run only selected tests. Seperate the test cases by comma\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-output=[FORMAT] change the format in which the test results are printed\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-version         display cester version and exit\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-help            display this help info version and exit\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "See https://exoticlibraries.github.io/libcester/docs/options.html for more details\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\nSupported output formats. [FORMAT]:\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    text\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    junitxml\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    tap\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    tapV13\n");
}

static inline void cester_print_assertion(char const* const expression, char const* const file_path, size_t const line_num) {
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, (superTestInstance.minimal == 0 ? file_path : cester_extract_name(file_path) ));
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ":");
    cester_concat_int(&(superTestInstance.current_test_case)->execution_output, line_num);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ":");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, " in '");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, (superTestInstance.current_test_case)->name);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "' expr => '");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, expression);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "'");
    
    /*CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), (superTestInstance.verbose == 1 ? file_path : cester_extract_name(file_path) ));
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ":");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_YELLOW), line_num);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ":");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " in '");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), (superTestInstance.current_test_case)->name);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "' expr => '");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), expression);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "'");**/
}

static inline void cester_print_expect_actual(size_t expecting, char const* const expect, char const* const found, char const* const file_path, size_t const line_num) {
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, (superTestInstance.minimal == 0 ? file_path : cester_extract_name(file_path) ));
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ":");
    cester_concat_int(&(superTestInstance.current_test_case)->execution_output, line_num);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ":");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, " in '");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, (superTestInstance.current_test_case)->name);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "' =>");
    if (expecting == 0) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, " not expecting ");
    } else {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, " expected ");
    }
    
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "'");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, expect);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "'");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ", found ");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "'");
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, found);
    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "'");
    
    /*CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), (superTestInstance.verbose == 1 ? file_path : cester_extract_name(file_path) ));
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
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), found);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ", found ");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), expect);*/
}

static inline void print_test_result(double time_spent) {
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\nRan ");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_WHITE), superTestInstance.total_tests_count);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " test(s) in ");
    CESTER_DELEGATE_FPRINT_DOUBLE_2((CESTER_FOREGROUND_WHITE), (time_spent > 60 ? (time_spent / 60) : time_spent) );
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), (time_spent > 60 ? " Minutes\n" : " Seconds\n" ));
    
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "Synthesis: ");
    CESTER_DELEGATE_FPRINT_STR(CESTER_GET_RESULT_AGGR_COLOR, CESTER_GET_RESULT_AGGR);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " Tests: ");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_YELLOW), CESTER_TOTAL_TESTS_COUNT);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " | Passing: ");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GREEN), CESTER_TOTAL_PASSED_TESTS_COUNT);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " | Failing: ");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_RED), CESTER_TOTAL_FAILED_TESTS_COUNT);
    if (CESTER_TOTAL_TESTS_SKIPPED > 0) {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " | Skipped: ");
        CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_YELLOW), CESTER_TOTAL_TESTS_SKIPPED);
    }
    if (CESTER_TOTAL_TODO_TESTS > 0) {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " | Todo: ");
        CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_YELLOW), CESTER_TOTAL_TODO_TESTS);
    }
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n"); 
}

static inline void print_test_case_result(TestCase* test_case) {
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "  ");
    if (test_case->test_type == CESTER_NORMAL_TODO_TEST || test_case->test_type == CESTER_NORMAL_SKIP_TEST) {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "o ");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "(");
        CESTER_DELEGATE_FPRINT_DOUBLE_2((CESTER_FOREGROUND_GRAY), test_case->execution_time);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), ") ");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), (superTestInstance.format_test_name == 1 ? cester_str_replace(test_case->name, '_', ' ') : test_case->name ));
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), (test_case->test_type == CESTER_NORMAL_TODO_TEST ? " TODO " : " SKIP "));
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
    } else {
        if (test_case->execution_status == CESTER_RESULT_SUCCESS) {
            #ifdef _WIN32
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GREEN), "+ ");
            #else
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GREEN), "\u2713 ");
            #endif
        } else {
            #ifdef _WIN32
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), "- ");
            #else
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), "X ");
            #endif
        }
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "(");
        CESTER_DELEGATE_FPRINT_DOUBLE_2((CESTER_FOREGROUND_GRAY), test_case->execution_time);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), ") ");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), (superTestInstance.format_test_name == 1 ? cester_str_replace(test_case->name, '_', ' ') : test_case->name ));
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
    }
}

static inline void print_test_case_outputs(TestCase* test_case) {
    if (test_case->execution_status == CESTER_RESULT_SEGFAULT || test_case->execution_status == CESTER_RESULT_TERMINATED) {
        if (test_case->execution_status == CESTER_RESULT_SEGFAULT) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "SegfaultError ");
        } else {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "PrematureTermination ");
        }
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), (superTestInstance.minimal == 0 ? superTestInstance.test_file_path : cester_extract_name(superTestInstance.test_file_path) ));
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
}

static inline void write_testcase_tap(TestCase *a_test_case, char* file_name, int index) {
    #ifdef _WIN32
        size_t print_color = CESTER_FOREGROUND_YELLOW;
    #else 
        char* print_color = CESTER_FOREGROUND_YELLOW;
    #endif
    if (a_test_case->execution_status == CESTER_RESULT_SUCCESS || 
        a_test_case->test_type == CESTER_NORMAL_SKIP_TEST || 
        a_test_case->test_type == CESTER_NORMAL_TODO_TEST) {
            
        if (a_test_case->execution_status == CESTER_RESULT_SUCCESS) {
            print_color = CESTER_FOREGROUND_GREEN;
        }
        CESTER_DELEGATE_FPRINT_STR((print_color), "ok ");
        
    } else {
        print_color = CESTER_FOREGROUND_RED;
        CESTER_DELEGATE_FPRINT_STR((print_color), "not ok ");
    }
    CESTER_DELEGATE_FPRINT_INT((print_color), index);
    CESTER_DELEGATE_FPRINT_STR((print_color), " - ");
    if (a_test_case->test_type == CESTER_NORMAL_SKIP_TEST) {
        CESTER_DELEGATE_FPRINT_STR((print_color), "# SKIP ");
        
    } else if (a_test_case->test_type == CESTER_NORMAL_TODO_TEST) {
        CESTER_DELEGATE_FPRINT_STR((print_color), "# TODO ");
        
    }
    CESTER_DELEGATE_FPRINT_STR((print_color), (superTestInstance.format_test_name == 1 ? cester_str_replace(a_test_case->name, '_', ' ') : a_test_case->name ));
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
    if (superTestInstance.verbose == 1) {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), a_test_case->execution_output);
    }
}

static inline void write_testcase_tap_v13(TestCase *a_test_case, char* file_name, int index) {
    #ifdef _WIN32
        size_t print_color = CESTER_FOREGROUND_YELLOW;
    #else 
        char* print_color = CESTER_FOREGROUND_YELLOW;
    #endif
    if (a_test_case->execution_status == CESTER_RESULT_SUCCESS || 
        a_test_case->test_type == CESTER_NORMAL_SKIP_TEST || 
        a_test_case->test_type == CESTER_NORMAL_TODO_TEST) {
            
        if (a_test_case->execution_status == CESTER_RESULT_SUCCESS) {
            print_color = CESTER_FOREGROUND_GREEN;
        }
        CESTER_DELEGATE_FPRINT_STR((print_color), "ok ");
        
    } else {
        print_color = CESTER_FOREGROUND_RED;
        CESTER_DELEGATE_FPRINT_STR((print_color), "not ok ");
    }
    CESTER_DELEGATE_FPRINT_INT((print_color), index);
    CESTER_DELEGATE_FPRINT_STR((print_color), " - ");
    if (a_test_case->test_type == CESTER_NORMAL_SKIP_TEST) {
        CESTER_DELEGATE_FPRINT_STR((print_color), "# SKIP ");
        
    } else if (a_test_case->test_type == CESTER_NORMAL_TODO_TEST) {
        CESTER_DELEGATE_FPRINT_STR((print_color), "# TODO ");
        
    }
    CESTER_DELEGATE_FPRINT_STR((print_color), (superTestInstance.format_test_name == 1 ? cester_str_replace(a_test_case->name, '_', ' ') : a_test_case->name ));
    CESTER_DELEGATE_FPRINT_STR((print_color), "\n");
    if (superTestInstance.verbose == 1 && a_test_case->test_type != CESTER_NORMAL_SKIP_TEST && 
        a_test_case->test_type != CESTER_NORMAL_TODO_TEST) {
        if (a_test_case->execution_status == CESTER_RESULT_SUCCESS && superTestInstance.minimal == 1) {
            return;
        }
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "  ---\n");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "  at:\n");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "    file: ");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), (superTestInstance.minimal == 0 ? superTestInstance.test_file_path : cester_extract_name(superTestInstance.test_file_path)));
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "\n    test_case: ");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), a_test_case->name);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "\n    line: ");
        CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), a_test_case->line_num);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "\n    column: 1");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "\n");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "  outputs:\n");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), a_test_case->execution_output);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "  message: ");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), (superTestInstance.format_test_name == 1 ? cester_str_replace(a_test_case->name, '_', ' ') : a_test_case->name ));
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
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "\n  time: ");
        CESTER_DELEGATE_FPRINT_DOUBLE_2((CESTER_FOREGROUND_GRAY), a_test_case->execution_time);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "\n  ...\n");
    }
}

static inline void write_testcase_junitxml(TestCase *a_test_case, char* file_name) {
    CESTER_DELEGATE_FPRINT_STR((default_color), "    <testcase classname=\"");
    CESTER_DELEGATE_FPRINT_STR((default_color), file_name);
    CESTER_DELEGATE_FPRINT_STR((default_color), "\" name=\"");
    CESTER_DELEGATE_FPRINT_STR((default_color), a_test_case->name);
    CESTER_DELEGATE_FPRINT_STR((default_color), "\" time=\"");
    CESTER_DELEGATE_FPRINT_DOUBLE_2((default_color), a_test_case->execution_time);
    CESTER_DELEGATE_FPRINT_STR((default_color), "\"");
    switch (a_test_case->execution_status) {
        case CESTER_RESULT_SUCCESS:
            CESTER_DELEGATE_FPRINT_STR((default_color), "/>\n");
            break;
        case CESTER_RESULT_SEGFAULT:
        case CESTER_RESULT_TERMINATED:
            if (a_test_case->execution_status == CESTER_RESULT_SEGFAULT) {
                CESTER_DELEGATE_FPRINT_STR((default_color), ">\n        <failure message=\"the test case crashed\" type=\"SegmentationFault\">");
                CESTER_DELEGATE_FPRINT_STR((default_color), "SegfaultError ");
            } else {
                CESTER_DELEGATE_FPRINT_STR((default_color), ">\n        <failure message=\"the test case was terminated\" type=\"PrematureTermination\">");
                CESTER_DELEGATE_FPRINT_STR((default_color), "PrematureTermination ");
            }
            CESTER_DELEGATE_FPRINT_STR((default_color), (superTestInstance.minimal == 0 ? superTestInstance.test_file_path : cester_extract_name(superTestInstance.test_file_path)));
            CESTER_DELEGATE_FPRINT_STR((default_color), ":");
            CESTER_DELEGATE_FPRINT_INT((default_color), a_test_case->line_num);
            CESTER_DELEGATE_FPRINT_STR((default_color), ": ");
            if (a_test_case->execution_status == CESTER_RESULT_SEGFAULT) {
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "Segmentation fault ");
            } else {
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "Premature Termination ");
            }
            CESTER_DELEGATE_FPRINT_STR((default_color), "in '");
            CESTER_DELEGATE_FPRINT_STR((default_color), a_test_case->name);
            CESTER_DELEGATE_FPRINT_STR((default_color), "' \n");
            CESTER_DELEGATE_FPRINT_STR((default_color), a_test_case->execution_output);
            CESTER_DELEGATE_FPRINT_STR((default_color), "        </failure>\n    </testcase>\n");
            break;
#ifndef CESTER_NO_MEM_TEST
        case CESTER_RESULT_MEMORY_LEAK:
            CESTER_DELEGATE_FPRINT_STR((default_color), ">\n        <failure message=\"the test case leaks memory\" type=\"MemoryLeakError\">");
            CESTER_DELEGATE_FPRINT_STR((default_color), a_test_case->execution_output);
            CESTER_DELEGATE_FPRINT_STR((default_color), "        </failure>\n    </testcase>\n");
            break;
#endif
        default:
            CESTER_DELEGATE_FPRINT_STR((default_color), ">\n        <failure message=\"the test case failed\" type=\"TestFailed\">");
            CESTER_DELEGATE_FPRINT_STR((default_color), a_test_case->execution_output);
            CESTER_DELEGATE_FPRINT_STR((default_color), "        </failure>\n    </testcase>\n");
            break;
    }
    
}


// Assertions, Tests

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
    Check if the expression evaluates to false. 
    Prints the expression as in the source code.
    
    \param x the expression to check if false
*/
#define cester_assert_false(x) cester_assert_cmp_msg(x, ==, 0, "(" #x ")")

/**
    Assertion macro that passes if an expression is NULL. 
    Prints the expression as in the source code.
    
    \param x the expression to check if it NULL.
*/
#define cester_assert_null(x) cester_assert_cmp_msg(x, ==, NULL, "(" #x ")")

/**
    Assertion macro that passes if an expression is not NULL. 
    Prints the expression as in the source code.
    
    \param x the expression to check if it not NULL.
*/
#define cester_assert_not_null(x) cester_assert_cmp_msg(x, !=, NULL, "!(" #x ")")

/**
    Assertion macro that passes if the two expression is equal. 
    Prints the expression as in the source code
    
    \param x the first expression to compare
    \param y the second expression to compare
*/
#define cester_assert_equal(x,y) cester_evaluate_expect_actual(x==y, 1, #x, #y, __FILE__, __LINE__)

/**
    Assertion macro that passes if the two expression is not equal. 
    Prints the expression as in the source code
    
    \param x the first expression to compare
    \param y the second expression to compare
*/
#define cester_assert_not_equal(x,y) cester_evaluate_expect_actual(x!=y, 0, #x, #y, __FILE__, __LINE__)

/**
    Compare two strings. If the comparison fails the test case 
    is marked as failed. The advantage of this macro is that it display 
    the actual values of the two strings.
    
    \param x a string to compare
    \param x another string to compare with the first string
*/
#define cester_assert_str_equal(x,y) cester_evaluate_expect_actual_str(x, y, 1, __FILE__, __LINE__)

/**
    Compare two strings. If the comparison passes the test case 
    is marked as failed. The advantage of this macro is that it display 
    the actual values of the two strings.
    
    \param x a string to compare
    \param x another string to compare with the first string
*/
#define cester_assert_str_not_equal(x,y) cester_evaluate_expect_actual_str(x, y, 0, __FILE__, __LINE__)

/**
    Compare two char using the provided operator
    This macro prints out the actual values of the two 
    chars.
    
    \param x a char
    \param y the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param z another char
*/
#define cester_assert_cmp_char(x,y,z) cester_compare_char(x y z, "(%c %s %c)", x, z, #y, __FILE__, __LINE__)

/**
    Check if the two char are the same.
    This macro prints out the actual values of the two 
    chars.
    
    \param x a char
    \param z another char
*/
#define cester_assert_char_eq(x,y) cester_assert_cmp_char(x, ==, y)

/**
    Check if the two char are not the same.
    This macro prints out the actual values of the two 
    chars.
    
    \param x a char
    \param z another char
*/
#define cester_assert_char_ne(x,y) cester_assert_cmp_char(x, !=, y)

/**
    Check if the a char is greater than the other.
    This macro prints out the actual values of the two 
    chars.
    
    \param x a char
    \param z another char
*/
#define cester_assert_char_gt(x,y) cester_assert_cmp_char(x, >, y)

/**
    Check if the a char is greater than or equal to the other.
    This macro prints out the actual values of the two 
    chars.
    
    \param x a char
    \param z another char
*/
#define cester_assert_char_ge(x,y) cester_assert_cmp_char(x, >=, y)

/**
    Check if the a char is lesser than the other.
    This macro prints out the actual values of the two 
    chars.
    
    \param x a char
    \param z another char
*/
#define cester_assert_char_lt(x,y) cester_assert_cmp_char(x, <, y)

/**
    Check if the a char is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    chars.
    
    \param x a char
    \param z another char
*/
#define cester_assert_char_le(x,y) cester_assert_cmp_char(x, <=, y)

/**
    Compare two unsigned char using the provided operator
    This macro prints out the actual values of the two 
    unsigned char.
    
    \param x an unsigned char
    \param y the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param z another unsigned char
*/
#define cester_assert_cmp_uchar(x,y,z) cester_compare_uchar(x y z, "(%u %s %u)", x, z, #y, __FILE__, __LINE__)

/**
    Check if the two unsigned char are the same.
    This macro prints out the actual values of the two 
    unsigned char.
    
    \param x an unsigned char
    \param z another unsigned char
*/
#define cester_assert_uchar_eq(x,y) cester_assert_cmp_uchar(x, ==, y)

/**
    Check if the two unsigned char are not the same.
    This macro prints out the actual values of the two 
    unsigned char.
    
    \param x an unsigned char
    \param z another unsigned char
*/
#define cester_assert_uchar_ne(x,y) cester_assert_cmp_uchar(x, !=, y)

/**
    Check if the a unsigned char is greater than the other.
    This macro prints out the actual values of the two 
    unsigned char.
    
    \param x an unsigned char
    \param z another unsigned char
*/
#define cester_assert_uchar_gt(x,y) cester_assert_cmp_uchar(x, >, y)

/**
    Check if the a unsigned char is greater than or equal to the other.
    This macro prints out the actual values of the two 
    unsigned char.
    
    \param x an unsigned char
    \param z another unsigned char
*/
#define cester_assert_uchar_ge(x,y) cester_assert_cmp_uchar(x, >=, y)

/**
    Check if the a unsigned char is lesser than the other.
    This macro prints out the actual values of the two 
    unsigned char.
    
    \param x a unsigned char
    \param z another unsigned char
*/
#define cester_assert_uchar_lt(x,y) cester_assert_cmp_uchar(x, <, y)

/**
    Check if the a int is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    int.
    
    \param x an int
    \param z another int
*/
#define cester_assert_int_le(x,y) cester_assert_cmp_int(x, <=, y)

/**
    Compare two int using the provided operator
    This macro prints out the actual values of the two 
    int.
    
    \param x an int
    \param y the operator to use for the comparison. One of ==, !=, <, >, <=, >=
    \param z another int
*/
#define cester_assert_cmp_int(x,y,z) cester_compare_int(x y z, "(%d %s %d)", x, z, #y, __FILE__, __LINE__)

/**
    Check if the two int are the same.
    This macro prints out the actual values of the two 
    int.
    
    \param x an int
    \param z another int
*/
#define cester_assert_int_eq(x,y) cester_assert_cmp_int(x, ==, y)

/**
    Check if the two int are not the same.
    This macro prints out the actual values of the two 
    int.
    
    \param x an int
    \param z another int
*/
#define cester_assert_int_ne(x,y) cester_assert_cmp_int(x, !=, y)

/**
    Check if the a int is greater than the other.
    This macro prints out the actual values of the two 
    int.
    
    \param x an int
    \param z another int
*/
#define cester_assert_int_gt(x,y) cester_assert_cmp_int(x, >, y)

/**
    Check if the a int is greater than or equal to the other.
    This macro prints out the actual values of the two 
    int.
    
    \param x an int
    \param z another int
*/
#define cester_assert_int_ge(x,y) cester_assert_cmp_int(x, >=, y)

/**
    Check if the a int is lesser than the other.
    This macro prints out the actual values of the two 
    int.
    
    \param x an int
    \param z another int
*/
#define cester_assert_int_lt(x,y) cester_assert_cmp_int(x, <, y)

/**
    Check if the a int is lesser than or equal to the other.
    This macro prints out the actual values of the two 
    int.
    
    \param x an int
    \param z another int
*/
#define cester_assert_int_le(x,y) cester_assert_cmp_int(x, <=, y)

static inline void cester_evaluate_expression(size_t eval_result, char const* const expression, char const* const file_path, size_t const line_num) {
    if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "# ");
    }
    if (eval_result == 0) {
        superTestInstance.current_execution_status = CESTER_RESULT_FAILURE;
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "EvaluationError ");
    } else if (superTestInstance.verbose == 1) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "Passed ");
    }
    if (eval_result == 0 || superTestInstance.verbose == 1) {
        cester_print_assertion(expression, file_path, line_num);
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "\n");
    }
}

static inline void cester_evaluate_expect_actual(size_t eval_result, size_t expecting, char const* const expected, char const* const actual, 
                                                char const* const file_path, size_t const line_num) {
                                                    
    if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "# ");
        
    } else if (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "    - ");
    }
    if (eval_result == 0) {
        superTestInstance.current_execution_status = CESTER_RESULT_FAILURE;
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "AssertionError ");
    } else if (superTestInstance.verbose == 1) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "Passed ");
    }
    if (eval_result == 0 || superTestInstance.verbose == 1) {
        cester_print_expect_actual(expecting, actual, expected, file_path, line_num);
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "\n");
    }
}

static inline void cester_evaluate_expect_actual_str(char const* const expected, char const* const actual, size_t expecting, char const* const file_path, size_t const line_num) {
    size_t eval_result = cester_string_equals((char*)expected, (char*)actual);  
    if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "# ");
        
    } else if (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "    - ");
    }
    if (eval_result != expecting) {
        superTestInstance.current_execution_status = CESTER_RESULT_FAILURE;
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "AssertionError ");
    } else if (superTestInstance.verbose == 1) {
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "Passed ");
    }  
    if (eval_result != expecting || superTestInstance.verbose == 1) {
        cester_print_expect_actual(expecting, actual, expected, file_path, line_num);
        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "\n");
    }
}

static inline void cester_compare_char(int eval_result, char* expr, char first, char second, char* op, char const* const file_path, size_t const line_num) {
    char expression[2048] = "";
    cester_sprintf(expression, 2048, expr, first, op, second);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static inline void cester_compare_int(int eval_result, char* expr, int first, int second, char* op, char const* const file_path, size_t const line_num) {
    char expression[2048] ;
    cester_sprintf(expression, 2048, expr, first, op, second);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static inline void cester_compare_uchar(int eval_result, char* expr, unsigned char first, unsigned char second, char* op, char const* const file_path, size_t const line_num) {
    char expression[2048] ;
    cester_sprintf(expression, 2048, expr, first, op, second);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

static inline void cester_compare_int(int eval_result, char* expr, int first, int second, char* op, char const* const file_path, size_t const line_num) {
    char expression[2048] ;
    cester_sprintf(expression, 2048, expr, first, op, second);
    cester_evaluate_expression(eval_result, (char*)expression, file_path, line_num);
}

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
#define CESTER_BEFORE_EACH(w,x,y,z) void cester_before_each_test(TestInstance* w, char * const x, size_t y);

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
#define CESTER_AFTER_EACH(w,x,y,z) void cester_after_each_test(TestInstance* w, char * const x, size_t y);

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
    A multiline comment macro everything in the macro is totally 
    ignored during macro expansion.
*/
#define CESTER_COMMENT(x)

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

/**
    Manual
*/
#define CESTER_REGISTER_TEST(x) cester_register_test(#x, (cester_test_##x), __LINE__, CESTER_NORMAL_TEST)

/**
    Manual
*/
#define CESTER_REGISTER_SKIP_TEST(x) cester_register_test(#x, (cester_test_##x), __LINE__, CESTER_NORMAL_SKIP_TEST)

/**
    Manual
*/
#define CESTER_REGISTER_TODO_TEST(x) cester_register_test(#x, (cester_test_##x), __LINE__, CESTER_NORMAL_TODO_TEST)

/**
    Manual
*/
#define CESTER_REGISTER_BEFORE_ALL() cester_register_test("cester_before_all_test", (cester_before_all_test), __LINE__, CESTER_BEFORE_ALL_TEST)

/**
    Manual
*/
#define CESTER_REGISTER_BEFORE_EACH() cester_register_test("cester_before_each_test", (cester_before_each_test), __LINE__, CESTER_BEFORE_EACH_TEST)

/**
    Manual
*/
#define CESTER_REGISTER_AFTER_ALL() cester_register_test("cester_after_all_test", (cester_after_all_test), __LINE__, CESTER_AFTER_ALL_TEST)

/**
    Manual
*/
#define CESTER_REGISTER_AFTER_EACH() cester_register_test("cester_after_each_test", (cester_after_each_test), __LINE__, CESTER_AFTER_EACH_TEST)

/**
    Manual
*/
#define CESTER_REGISTER_OPTIONS() cester_register_test("cester_options_before_main", (cester_options_before_main), __LINE__, CESTER_OPTIONS_FUNCTION)

#ifdef __BASE_FILE__
    #include __BASE_FILE__
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
#undef CESTER_MOCK_SIMPLE_FUNCTION
#undef CESTER_MOCK_FUNCTION


#define CESTER_TEST(x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, 0.000, (char*) "", (void*) (cester_test_##x), (char*) #x, CESTER_NORMAL_TEST },
#define CESTER_TODO_TEST(x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, 0.000, (char*) "", (void*) (cester_test_##x), (char*) #x, CESTER_NORMAL_TODO_TEST },
#define CESTER_SKIP_TEST(x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, 0.000, (char*) "", (void*) (cester_test_##x), (char*) #x, CESTER_NORMAL_SKIP_TEST },
#define CESTER_BEFORE_ALL(x,y) { CESTER_RESULT_UNKNOWN, __LINE__, 0.000, (char*) "", (void*) (cester_before_all_test), (char*) "cester_before_all_test", CESTER_BEFORE_ALL_TEST },
#define CESTER_BEFORE_EACH(w,x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, 0.000, (char*) (char*) "", (void*) (cester_before_each_test), (char*) "cester_before_each_test", CESTER_BEFORE_EACH_TEST },
#define CESTER_AFTER_ALL(x,y) { CESTER_RESULT_UNKNOWN, __LINE__, 0.000, (char*) "", (void*) (cester_after_all_test), (char*) "cester_after_all_test", CESTER_AFTER_ALL_TEST },
#define CESTER_AFTER_EACH(w,x,y,z) { CESTER_RESULT_UNKNOWN, __LINE__, 0.000, (char*) "", (void*) (cester_after_each_test), (char*) "cester_after_each_test", CESTER_AFTER_EACH_TEST },
#define CESTER_OPTIONS(x) { CESTER_RESULT_UNKNOWN, __LINE__, 0.000, (char*) "", (void*) (cester_options_before_main), (char*) "cester_options_before_main", CESTER_OPTIONS_FUNCTION },
#define CESTER_BODY(x)
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,z) 
#define CESTER_MOCK_FUNCTION(x,y,z)

static TestCase cester_test_cases[] = {
#ifdef __BASE_FILE__
    #include __BASE_FILE__
#endif
{ CESTER_RESULT_UNKNOWN, 0, 0.000, NULL, NULL, NULL, CESTER_TESTS_TERMINATOR }
};

#undef CESTER_TEST
#undef CESTER_TODO_TEST
#undef CESTER_SKIP_TEST
#undef CESTER_BEFORE_ALL
#undef CESTER_BEFORE_EACH
#undef CESTER_AFTER_ALL
#undef CESTER_AFTER_EACH
#undef CESTER_OPTIONS
#undef CESTER_BODY
#undef CESTER_MOCK_SIMPLE_FUNCTION
#undef CESTER_MOCK_FUNCTION

#define CESTER_TEST(x,y,z) static void cester_test_##x(TestInstance* y) { z  } 
#define CESTER_TODO_TEST(x,y,z) static void cester_test_##x(TestInstance* y) { z }
#define CESTER_SKIP_TEST(x,y,z) static void cester_test_##x(TestInstance* y) { z } 
#define CESTER_BEFORE_ALL(x,y) void cester_before_all_test(TestInstance* x) { y } 
#define CESTER_BEFORE_EACH(w,x,y,z) void cester_before_each_test(TestInstance* w, char * const x, size_t y) { z }
#define CESTER_AFTER_ALL(x,y) void cester_after_all_test(TestInstance* x) { y } 
#define CESTER_AFTER_EACH(w,x,y,z) void cester_after_each_test(TestInstance* w, char * const x, size_t y) { z }
#define CESTER_OPTIONS(x) void cester_options_before_main() { x }
#define CESTER_BODY(x) x;
#ifndef CESTER_NO_MOCK
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,z) y __wrap_##x { return z; }
#define CESTER_MOCK_FUNCTION(x,y,z) y __wrap_##x { z }
#else
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,z) 
#define CESTER_MOCK_FUNCTION(x,y,z) 
#endif

/**
    Manually register a test case
*/
static inline void cester_register_test(char *test_name, void* function, size_t line_num, TestType test_type) {
    if (superTestInstance.registered_test_cases == NULL) {
        if (cester_array_init(&superTestInstance.registered_test_cases) == 0) {
            if (superTestInstance.output_stream==NULL) {
                superTestInstance.output_stream = stdout;
            }
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Unable to initialize the test cases array. Cannot run manually registered tests.\n");
            return;
        }
    }
    TestCase* test_case = (TestCase*) malloc(sizeof(TestCase));
    test_case->execution_status = CESTER_RESULT_UNKNOWN;
    test_case->line_num = line_num;
    test_case->execution_time = 0.000;
    test_case->execution_output = (char*) "";
    test_case->function = function;
    test_case->name = test_name;
    test_case->test_type = test_type;
    if (cester_array_add(superTestInstance.registered_test_cases, test_case) == 0) {
        if (superTestInstance.output_stream==NULL) {
            superTestInstance.output_stream = stdout;
        }
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Failed to register '");
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), test_name);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "' \n");
        superTestInstance.mem_test_active = 0;
    }
}

static inline size_t cester_run_test_no_isolation(TestInstance *, TestCase *, size_t);

static inline void cester_run_test(TestInstance *test_instance, TestCase *a_test_case, size_t index) {
    clock_t tic = clock();
    size_t last_status = CESTER_RESULT_UNKNOWN;
    if (superTestInstance.isolate_tests == 1) {
#ifdef _WIN32
        SECURITY_ATTRIBUTES sa;
        sa.nLength = sizeof(SECURITY_ATTRIBUTES);
        sa.bInheritHandle = TRUE;
        sa.lpSecurityDescriptor = NULL;

        HANDLE stdout_pipe_read;
        HANDLE stdout_pipe_write;
        CreatePipe(&stdout_pipe_read, &stdout_pipe_write, &sa, 0);

        STARTUPINFO si = {
            .cb = sizeof(STARTUPINFO),
            .dwFlags = STARTF_USESTDHANDLES,
            .hStdOutput = stdout_pipe_write
        };

        PROCESS_INFORMATION pi = {0};

        CHAR command[1500];
        snprintf(command, 1500, "%s --cester-test=%s  --cester-singleoutput --cester-noisolation %s %s %s %s %s %s %s", 
                                test_instance->argv[0], 
                                a_test_case->name, 
                                (superTestInstance.mem_test_active == 0 ? "--cester-nomemtest" : ""), 
                                (superTestInstance.minimal == 1 ? "--cester-minimal" : ""),
                                (superTestInstance.verbose == 1 ? "--cester-verbose" : ""),
                                (superTestInstance.format_test_name == 0 ? "--cester-dontformatname" : ""),
                                (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1 ? "--cester-output=tap" : ""),
                                (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1 ? "--cester-output=tapV13" : ""),
                                superTestInstance.flattened_cmd_argv);

        CreateProcess(
            NULL,
            command,
            NULL,
            NULL,
            TRUE,
            0,
            NULL,
            NULL,
            &si,
            &pi);

        CloseHandle(stdout_pipe_write);

        DWORD len;
        DWORD maxlen = 700;
        CHAR buffer[700];

        do {
            ReadFile(stdout_pipe_read, buffer, maxlen, &len, NULL);
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

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
#elif defined unix
	pid_t pid;
	int pipefd[2];
	char *selected_test_unix = (char*) "";

	pipe(pipefd);
	pid = fork();

	if (pid == -1) {
		CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Unable to create a seperate process for the '");
		CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), a_test_case->name);
		CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "'. Running the test on main process.");
		last_status = cester_run_test_no_isolation(test_instance, a_test_case, index);
	
	} else if (pid == 0) {
		cester_concat_str(&selected_test_unix, "--cester-test=");
		cester_concat_str(&selected_test_unix, a_test_case->name);
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		execl(test_instance->argv[0], 
				test_instance->argv[0], 
				selected_test_unix,
				"--cester-singleoutput",
				"--cester-noisolation",	
				(superTestInstance.mem_test_active == 0 ? "--cester-nomemtest" : ""),
				(superTestInstance.minimal == 1 ? "--cester-minimal" : ""),
				(superTestInstance.verbose == 1 ? "--cester-verbose" : ""),
				(superTestInstance.format_test_name == 0 ? "--cester-dontformatname" : ""),
				(cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1 ? "--cester-output=tap" : ""),
				(cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1 ? "--cester-output=tapV13" : ""),
				superTestInstance.flattened_cmd_argv,
				(char*)NULL);
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
	}
#else
	#pragma message("Isolated tests not supported in this environment. The tests will be run on the main process")
        last_status = cester_run_test_no_isolation(test_instance, a_test_case, index);
#endif
    } else {
        last_status = cester_run_test_no_isolation(test_instance, a_test_case, index);
    }
    if (last_status == CESTER_RESULT_SUCCESS) {
        ++superTestInstance.total_passed_tests_count;
    } else {
        ++superTestInstance.total_failed_tests_count;
    }
    clock_t tok = clock();
    a_test_case->execution_time = (double)(((double)tok) - ((double)tic)) / CLOCKS_PER_SEC;
    a_test_case->execution_status = last_status;
    
}

static inline size_t cester_run_test_no_isolation(TestInstance *test_instance, TestCase *a_test_case, size_t index) {
    size_t i;
    superTestInstance.current_test_case = a_test_case;
    superTestInstance.current_execution_status = CESTER_RESULT_SUCCESS;
    if (superTestInstance.registered_test_cases->size == 0) {
        for (i=0;cester_test_cases[i].function != NULL;++i) {
            if (cester_test_cases[i].test_type == CESTER_BEFORE_EACH_TEST) {
                ((cester_before_after_each)cester_test_cases[i].function)(test_instance, a_test_case->name, index);
            }
        }
    }
    CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index1, test_case, {
        if (((TestCase*)test_case)->test_type == CESTER_BEFORE_EACH_TEST) {
            ((cester_before_after_each)((TestCase*)test_case)->function)(test_instance, a_test_case->name, index);
        }
    })
    ((cester_test)a_test_case->function)(test_instance);
    if (superTestInstance.registered_test_cases->size == 0) {
        for (i=0;cester_test_cases[i].function != NULL;++i) {
            if (cester_test_cases[i].test_type == CESTER_AFTER_EACH_TEST) {
                ((cester_before_after_each)cester_test_cases[i].function)(test_instance, a_test_case->name, index);
            }
        }
    }
    CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index2, test_case, {
        if (((TestCase*)test_case)->test_type == CESTER_AFTER_EACH_TEST) {
            ((cester_before_after_each)((TestCase*)test_case)->function)(test_instance, a_test_case->name, index);
        }
    })
#ifndef CESTER_NO_MEM_TEST
    if (superTestInstance.mem_test_active == 1) {
        size_t leaked_bytes = 0;
        CESTER_ARRAY_FOREACH(superTestInstance.mem_alloc_manager, mem_index, alloc_mem, {
            if (cester_string_equals((char*)((AllocatedMemory*)alloc_mem)->function_name, a_test_case->name)) {
                leaked_bytes += ((AllocatedMemory*)alloc_mem)->allocated_bytes;
                if (superTestInstance.current_test_case != NULL) {
                    if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1) {
                        cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "# ");
                    }
                    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "MemoryLeakError ");
                    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, (superTestInstance.minimal == 0 ? superTestInstance.test_file_path : cester_extract_name(superTestInstance.test_file_path) ));
                    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ":");
                    cester_concat_int(&(superTestInstance.current_test_case)->execution_output, ((AllocatedMemory*)alloc_mem)->line_num);
                    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ": ");
                    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "in '");
                    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, (superTestInstance.current_test_case)->name);
                    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "' => Memory allocated in line '");
                    cester_concat_int(&(superTestInstance.current_test_case)->execution_output, ((AllocatedMemory*)alloc_mem)->line_num);
                    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "' not freed. Leaking '");
                    cester_concat_int(&(superTestInstance.current_test_case)->execution_output, ((AllocatedMemory*)alloc_mem)->allocated_bytes);
                    cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "' Bytes \n");
                }
            }
        })
        
        if (leaked_bytes > 0) {
            superTestInstance.current_execution_status = CESTER_RESULT_MEMORY_LEAK;
        }
    }
#endif
    if (superTestInstance.single_output_only == 1) {
        CESTER_DELEGATE_FPRINT_STR((default_color), a_test_case->execution_output);
    }
    return superTestInstance.current_execution_status;
}

static inline size_t cester_run_all_test(size_t argc, char **argv) {
    size_t i = 0; 
    size_t j = 1; 
    size_t index_sub;
    size_t found_test = 0;
    char* selected_test_case_name;
    #ifdef _WIN32
        CONSOLE_SCREEN_BUFFER_INFO info;
        if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info)) {
            default_color = info.wAttributes;
        }
        hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    #endif
    
    if (superTestInstance.output_stream==NULL) {
        superTestInstance.output_stream = stdout;
    }
    #ifndef CESTER_NO_MEM_TEST
        if (superTestInstance.mem_alloc_manager == NULL) {
            if (cester_array_init(&superTestInstance.mem_alloc_manager) == 0) {
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Unable to initialize the memory management array. Memory test disabled.\n");
                superTestInstance.mem_test_active = 0;
            }
        }
    #endif
    if (superTestInstance.registered_test_cases == NULL) {
        if (cester_array_init(&superTestInstance.registered_test_cases) == 0) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), "Unable to initialize the registered test cases array. Cannot continue tests.\n");
            return CESTER_RESULT_FAILURE;
        }
    }
    
    // execute options
    if (superTestInstance.registered_test_cases->size == 0) {
        for (size_t i=0;cester_test_cases[i].test_type != CESTER_TESTS_TERMINATOR;++i) {
            if (cester_test_cases[i].test_type == CESTER_OPTIONS_FUNCTION) {
                ((cester_void)cester_test_cases[i].function)();
                
            } else if (cester_test_cases[i].test_type == CESTER_NORMAL_TEST || 
                       cester_test_cases[i].test_type == CESTER_NORMAL_TODO_TEST || 
                       cester_test_cases[i].test_type == CESTER_NORMAL_SKIP_TEST) {
                           
                ++superTestInstance.total_tests_count;
            }
            
        }
    }
    
    CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index, test_case, {
        if (((TestCase*)test_case)->test_type == CESTER_OPTIONS_FUNCTION) {
            ((cester_void)((TestCase*)test_case)->function)();
            
        } else if (((TestCase*)test_case)->test_type == CESTER_NORMAL_TEST || 
                   ((TestCase*)test_case)->test_type == CESTER_NORMAL_TODO_TEST || 
                   ((TestCase*)test_case)->test_type == CESTER_NORMAL_SKIP_TEST) {
                       
            ++superTestInstance.total_tests_count;
        }
    })
    
    
    
    // resolve command line options
    for (;j < argc; ++j) {
        char* arg = argv[j];
        char* cester_option;
        if (cester_str_after_prefix(arg, (char*) "--cester-", 9, &cester_option) == 1) {
            if (cester_string_equals(cester_option, (char*) "minimal") == 1) {
                superTestInstance.minimal = 1;
                
            } else if (cester_string_equals(cester_option, (char*) "verbose") == 1) {
                superTestInstance.verbose = 1;
                
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
                
            } else if (cester_string_equals(cester_option, (char*) "nomemtest") == 1) {
                superTestInstance.mem_test_active = 0;
                
            } else if (cester_string_equals(cester_option, (char*) "version") == 1) {
                CESTER_NOCOLOR();
                cester_print_version();
                return EXIT_SUCCESS;
                
            } else if (cester_string_equals(cester_option, (char*) "help") == 1) {
                CESTER_NOCOLOR();
                cester_print_version();
                cester_print_help();
                return EXIT_SUCCESS;
                
            } else if (cester_string_starts_with(cester_option, (char*) "test=") == 1) {
                unpack_selected_extra_args(cester_option, &superTestInstance.selected_test_cases_names, &superTestInstance.selected_test_cases_size);
                
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
                    return EXIT_FAILURE;
                }
                
            } else {
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), "Invalid cester option: --cester-");
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), cester_option);
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), "\n");
                CESTER_RESET_TERMINAL_ATTR()
                return EXIT_FAILURE;
            }
        } else {
            cester_concat_str(&superTestInstance.flattened_cmd_argv, argv[j]);
            cester_concat_str(&superTestInstance.flattened_cmd_argv, " ");
        }
    }
    
    if (superTestInstance.print_version == 1) {
        cester_print_version();
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
        CESTER_RESET_TERMINAL_ATTR();
    }
    
    TestInstance *test_instance = (TestInstance*) malloc(sizeof(TestInstance*));
    test_instance->argc = argc;
    test_instance->argv = argv;
    
    // before all
    if (superTestInstance.registered_test_cases->size == 0) {
        for (i=0;cester_test_cases[i].function != NULL;++i) {
            if (cester_test_cases[i].test_type == CESTER_BEFORE_ALL_TEST) {
                ((cester_test)cester_test_cases[i].function)(test_instance);
            }
        }
    }
    CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index1, test_case, {
        if (((TestCase*)test_case)->test_type == CESTER_BEFORE_ALL_TEST) {
            ((cester_test)((TestCase*)test_case)->function)(test_instance);
        }
    })
    
    
    clock_t tic = clock();
    if (superTestInstance.selected_test_cases_size == 0) {
        if (superTestInstance.registered_test_cases->size == 0) {
            for (i=0;cester_test_cases[i].function != NULL;++i) {
                if (cester_test_cases[i].test_type == CESTER_NORMAL_TEST) {
                    cester_run_test(test_instance, &cester_test_cases[i], i);
                    
                } else if (cester_test_cases[i].test_type == CESTER_NORMAL_TODO_TEST) {
                    ++superTestInstance.todo_tests_count;
                    
                } else if (cester_test_cases[i].test_type == CESTER_NORMAL_SKIP_TEST) {
                    ++superTestInstance.skipped_test_count;
                    
                }
            }
        }
        CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index2, test_case, {
            if (((TestCase*)test_case)->test_type == CESTER_NORMAL_TEST) {
                cester_run_test(test_instance, ((TestCase*)test_case), i);
                
            } else if (((TestCase*)test_case)->test_type == CESTER_NORMAL_TODO_TEST) {
                ++superTestInstance.todo_tests_count;
                
            } else if (((TestCase*)test_case)->test_type == CESTER_NORMAL_SKIP_TEST) {
                ++superTestInstance.skipped_test_count;
                
            }
        })
        
    } else {
        for (j = 0; j < superTestInstance.selected_test_cases_size; ++j) {
            selected_test_case_name = superTestInstance.selected_test_cases_names[j];
            found_test = 0;
            if (superTestInstance.registered_test_cases->size == 0) {
                for (i=0;cester_test_cases[i].function != NULL;++i) {
                    if ((cester_test_cases[i].test_type == CESTER_NORMAL_TEST || cester_test_cases[i].test_type == CESTER_NORMAL_TODO_TEST || 
                        cester_test_cases[i].test_type == CESTER_NORMAL_SKIP_TEST) && 
                        cester_string_equals(cester_test_cases[i].name, selected_test_case_name) == 1) {
                            
                        found_test = 1;
                        if (cester_test_cases[i].test_type == CESTER_NORMAL_TEST) {
                            ++superTestInstance.selected_test_cases_found;
                            cester_run_test(test_instance, &cester_test_cases[i], i);
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
                        cester_string_equals(((TestCase*)test_case)->name, selected_test_case_name) == 1) {
                            
                        found_test = 1;
                        if (((TestCase*)test_case)->test_type == CESTER_NORMAL_TEST) {
                            ++superTestInstance.selected_test_cases_found;
                            cester_run_test(test_instance, ((TestCase*)test_case), i);
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
                    if (superTestInstance.minimal == 0 && cester_string_equals(superTestInstance.output_format, (char*) "text") == 1) {
                        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Warning: the '");
                        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), superTestInstance.selected_test_cases_names[j]);
                        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "' was not found! \n");
                    }
                }
            }
        }
    }
    clock_t tok = clock();
    double time_spent = (double)(tok - tic) / CLOCKS_PER_SEC;
    
    if (superTestInstance.registered_test_cases->size == 0) {
        for (i=0;cester_test_cases[i].function != NULL;++i) {
            if (cester_test_cases[i].test_type == CESTER_AFTER_ALL_TEST) {
                ((cester_test)cester_test_cases[i].function)(test_instance);
            }
        }
    }
    CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index4, test_case, {
        if (((TestCase*)test_case)->test_type == CESTER_AFTER_ALL_TEST) {
            ((cester_test)((TestCase*)test_case)->function)(test_instance);
        }
    })
    if (superTestInstance.single_output_only == 0) {
        if (cester_string_equals(superTestInstance.output_format, (char*) "junitxml") == 1) {
            CESTER_DELEGATE_FPRINT_STR((default_color), "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
            CESTER_DELEGATE_FPRINT_STR((default_color), "<testsuite tests=\"");
            CESTER_DELEGATE_FPRINT_INT((default_color), superTestInstance.total_tests_count);
            CESTER_DELEGATE_FPRINT_STR((default_color), "\" failures=\"");
            CESTER_DELEGATE_FPRINT_INT((default_color), superTestInstance.total_failed_tests_count);
            CESTER_DELEGATE_FPRINT_STR((default_color), "\" name=\"");
            CESTER_DELEGATE_FPRINT_STR((default_color), cester_extract_name_only(superTestInstance.test_file_path));
            CESTER_DELEGATE_FPRINT_STR((default_color), "\" errors=\"0\" skipped=\"");
            CESTER_DELEGATE_FPRINT_INT((default_color), CESTER_TOTAL_TESTS_SKIPPED + CESTER_TOTAL_TODO_TESTS);
            CESTER_DELEGATE_FPRINT_STR((default_color), "\" time=\"");
            CESTER_DELEGATE_FPRINT_DOUBLE_2((default_color), time_spent);
            CESTER_DELEGATE_FPRINT_STR((default_color), "\">\n");
            if (superTestInstance.registered_test_cases->size == 0) {
                for (i=0;cester_test_cases[i].function != NULL;++i) {
                    if (cester_test_cases[i].test_type == CESTER_NORMAL_TEST && cester_test_cases[i].execution_status != CESTER_RESULT_UNKNOWN) {
                        write_testcase_junitxml(&cester_test_cases[i], cester_extract_name_only(superTestInstance.test_file_path));
                    }
                }
            }
            CESTER_ARRAY_FOREACH(superTestInstance.registered_test_cases, index5, test_case, {
                if (((TestCase*)test_case)->test_type == CESTER_NORMAL_TEST && ((TestCase*)test_case)->execution_status != CESTER_RESULT_UNKNOWN) {
                    write_testcase_junitxml(((TestCase*)test_case), cester_extract_name_only(superTestInstance.test_file_path));
                }
            })
            CESTER_DELEGATE_FPRINT_STR((default_color), "</testsuite>\n");
            
        } else if (cester_string_equals(superTestInstance.output_format, (char*) "tap") == 1) {
            CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_WHITE), 1);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "..");
            CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_WHITE), (superTestInstance.selected_test_cases_size == 0 ? CESTER_TOTAL_TESTS_COUNT : superTestInstance.selected_test_cases_size));
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
            index_sub = 1;
            if (superTestInstance.registered_test_cases->size == 0) {
                for (i=0;cester_test_cases[i].function != NULL;++i) {
                    if ((cester_test_cases[i].test_type == CESTER_NORMAL_TEST || cester_test_cases[i].test_type == CESTER_NORMAL_TODO_TEST || 
                        cester_test_cases[i].test_type == CESTER_NORMAL_SKIP_TEST)) {
                        
                        if (superTestInstance.selected_test_cases_size > 0 && cester_test_cases[i].execution_status == CESTER_RESULT_UNKNOWN) {
                            continue;
                        }
                        write_testcase_tap(&cester_test_cases[i], cester_extract_name_only(superTestInstance.test_file_path), index_sub);
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
                    write_testcase_tap(((TestCase*)test_case), cester_extract_name_only(superTestInstance.test_file_path), index_sub);
                    ++index_sub;
                }
            })
            if (superTestInstance.verbose == 1) {
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "# Failed ");
                CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), CESTER_TOTAL_FAILED_TESTS_COUNT);
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " of ");
                CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), (superTestInstance.selected_test_cases_size == 0 ? CESTER_TOTAL_TESTS_COUNT : superTestInstance.selected_test_cases_size));
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " tests\n# Time ");
                CESTER_DELEGATE_FPRINT_DOUBLE_2((CESTER_FOREGROUND_GRAY), (time_spent > 60 ? (time_spent / 60) : time_spent));
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), (time_spent > 60 ? " Minutes\n" : " Seconds\n" ));
            }
            
        } else if (cester_string_equals(superTestInstance.output_format, (char*) "tapV13") == 1) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_CYAN), "TAP version 13");
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_CYAN), "\n");
            CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_CYAN), 1);
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_CYAN), "..");
            CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_CYAN), (superTestInstance.selected_test_cases_size == 0 ? CESTER_TOTAL_TESTS_COUNT : superTestInstance.selected_test_cases_size));
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_CYAN), "\n");
            index_sub = 1;
            if (superTestInstance.registered_test_cases->size == 0) {
                for (i=0;cester_test_cases[i].function != NULL;++i) {
                    if ((cester_test_cases[i].test_type == CESTER_NORMAL_TEST || cester_test_cases[i].test_type == CESTER_NORMAL_TODO_TEST || 
                        cester_test_cases[i].test_type == CESTER_NORMAL_SKIP_TEST)) {
                        
                        if (superTestInstance.selected_test_cases_size > 0 && cester_test_cases[i].execution_status == CESTER_RESULT_UNKNOWN) {
                            continue;
                        }
                        write_testcase_tap_v13(&cester_test_cases[i], cester_extract_name_only(superTestInstance.test_file_path), index_sub);
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
                    write_testcase_tap_v13(((TestCase*)test_case), cester_extract_name_only(superTestInstance.test_file_path), index_sub);
                    ++index_sub;
                }
            })
            if (superTestInstance.verbose == 1) {
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "# Failed ");
                CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), CESTER_TOTAL_FAILED_TESTS_COUNT);
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " of ");
                CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GRAY), (superTestInstance.selected_test_cases_size == 0 ? CESTER_TOTAL_TESTS_COUNT : superTestInstance.selected_test_cases_size));
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), " tests\n# Time ");
                CESTER_DELEGATE_FPRINT_DOUBLE_2((CESTER_FOREGROUND_GRAY), (time_spent > 60 ? (time_spent / 60) : time_spent));
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), (time_spent > 60 ? " Minutes\n" : " Seconds\n" ));
            }
            
        } else {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
            if (superTestInstance.registered_test_cases->size == 0) {
                for (i=0;cester_test_cases[i].function != NULL;++i) {
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
                for (i=0;cester_test_cases[i].function != NULL;++i) {
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
            
            print_test_result(time_spent);
        }
    }
    CESTER_RESET_TERMINAL_ATTR();
    if (CESTER_TOTAL_FAILED_TESTS_COUNT != 0 && superTestInstance.current_execution_status == CESTER_RESULT_SUCCESS) {
        return CESTER_RESULT_FAILURE;
    }
    return superTestInstance.current_execution_status;
}

#ifndef CESTER_NO_MAIN
int main(int argc, char **argv) {
    return CESTER_RUN_ALL_TESTS(argc, argv);
}
#endif

// CesterArray

static inline size_t cester_array_init(CesterArray** out) {
    CesterArray* array_local = (CesterArray*) malloc(sizeof(CesterArray));
    if (!array_local) {
        return 0;
    }
    array_local->size = 0;
    array_local->capacity = CESTER_ARRAY_INITIAL_CAPACITY;
    void **buffer = (void**) malloc(sizeof(void*) * array_local->capacity);
    if (!buffer) {
        free(array_local);
        return 0;
    }
    array_local->buffer = buffer;
    *out = array_local;
    return 1;
}

static inline size_t cester_array_add(CesterArray* array, void* item) {
    if (array->size >= array->capacity) {
        if (array->capacity >= CESTER_ARRAY_MAX_CAPACITY) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Max managable memory allocation reached, cannot expand array. Further Memory test disabled.\n");
            superTestInstance.mem_test_active = 0;
            return 0;
        }
        array->capacity = array->capacity + CESTER_ARRAY_INITIAL_CAPACITY;
        void **new_buffer = (void**) malloc(sizeof(void*) * array->capacity);
        if (!new_buffer) {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Failed to expand the memoray allocation array. Further Memory test disabled.\n");
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

static inline void* cester_array_remove_at(CesterArray* array, size_t index) {
    void* item = array->buffer[index];
    if (index != array->size - 1) {
        size_t block_size = (array->size - 1 - index) * sizeof(void*);
        memmove(&(array->buffer[index]),
                &(array->buffer[index + 1]),
                block_size);
    }
    return item;
}

// Memory leak Detection procedures 

#ifndef CESTER_NO_MEM_TEST                                      

static inline void* cester_malloc(size_t size, const char *file, size_t line, const char *func) {
    if (superTestInstance.mem_test_active == 1) {
        if (superTestInstance.mem_alloc_manager == NULL) {
            if (cester_array_init(&superTestInstance.mem_alloc_manager) == 0) {
                if (superTestInstance.output_stream==NULL) {
                    superTestInstance.output_stream = stdout;
                }
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Unable to initialize the memory management array. Memory test disabled.\n");
                superTestInstance.mem_test_active = 0;
            }
        }
    }
    void *p = malloc(size);
    if (superTestInstance.mem_test_active == 1) {
        AllocatedMemory* allocated_mem = (AllocatedMemory*) malloc(sizeof(AllocatedMemory));
        allocated_mem->line_num = line;
        allocated_mem->allocated_bytes = size;
        if (cester_str_after_prefix(func, (char*) "cester_test_", 12, (char **) &(allocated_mem->function_name)) == 0) {
            allocated_mem->function_name = func;
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

static inline void cester_free(void *pointer, const char *file, size_t line, const char *func) {
    if (pointer == NULL) {
        if (superTestInstance.mem_test_active == 1 && superTestInstance.current_test_case != NULL) {
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "InvalidOperation ");
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, (superTestInstance.minimal == 0 ? superTestInstance.test_file_path : cester_extract_name(superTestInstance.test_file_path) ));
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ":");
            cester_concat_int(&(superTestInstance.current_test_case)->execution_output, line);
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, ": ");
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "in '");
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, (superTestInstance.current_test_case)->name);
            cester_concat_str(&(superTestInstance.current_test_case)->execution_output, "' => Attempting to free a NULL pointer \n");
            superTestInstance.current_execution_status = CESTER_RESULT_MEMORY_LEAK;
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
                free(alloc_mem);
                --superTestInstance.mem_alloc_manager->size;
                break;
            }
        })
    }
    free(pointer);
}

#define malloc(x) cester_malloc( x, __FILE__, __LINE__, __FUNCTION__)
#define free(x) cester_free( x, __FILE__, __LINE__, __FUNCTION__)
#endif

#ifdef __cplusplus
}
#endif

#endif
