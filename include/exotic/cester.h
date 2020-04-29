
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

#ifndef __BASE_FILE__
#deinfe __BASE_FILE__ __FILE__
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
#define CESTER_FOREGROUND_GRAY          "\x1B[37m"    ///< gray terminal foreground color
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
    CESTER_SUCCESS,
    CESTER_FAILURE,
    CESTER_SEGFAULT,
    CESTER_UNKNOWN
};

/**
    The type of test
*/
typedef enum cester_test_type {
    NORMAL_TEST,             ///< normal test in global or test suite. For internal use only.
    BEFORE_ALL_TEST,         ///< test to run before all normal tests in global or test suite. For internal use only.
    BEFORE_EACH_TEST,        ///< test to run before each normal tests in global or test suite. For internal use only.
    AFTER_ALL_TEST,          ///< test to run after all normal tests in global or test suite. For internal use only.
    AFTER_EACH_TEST,         ///< test to run after each normal tests in global or test suite. For internal use only.
    CESTER_OPTION_FUNCTION,  ///< the cester function for test, this wil be excuted before running the tests. For internal use only.
    TESTS_TERMINATOR         ///< the last value in the test cases to terminates the tests. For internal use only.
} TestType;

typedef struct test_case {
    int execution_status;     ///< the test execution result status. For internal use only.
    int line_num;             ///< the line number where the test case is created. For internal use only.
    double execution_time;    ///< the time taken for the test case to complete. For internal use only.
    char* execution_output;   ///< the test execution output in string. For internal use only.
    void *function;           ///< the function that enclosed the tests. For internal use only.
    char *name;               ///< the test function name. For internal use only.
    TestType test_type;       ///< the type of the test function
} TestCase;

/**
    This structure manages the _BEFORE_ and _AFTER_ functions 
    for the test main ::test_instance. And also accounts for all the 
    registered test cases. This is for Cester internal use only.
*/
typedef struct super_test_instance {
    size_t no_color;                          ///< Do not print to the console with color if one. For internal use only.
    size_t total_tests_count;                 ///< the total number of tests to run, assert, eval e.t.c. To use in your code call CESTER_TOTAL_TESTS_COUNT
    size_t total_failed_tests_count;          ///< the total number of tests that failed. To use in your code call CESTER_TOTAL_FAILED_TESTS_COUNT
    size_t verbose;                           ///< prints as much info as possible into the output stream
    size_t minimal;                           ///< prints minimal output into the output stream
    size_t print_version;                     ///< prints cester version before running tests
    size_t selected_test_cases_size;          ///< the number of selected test casses from command line. For internal use only.
    size_t selected_test_cases_found;         ///< the number of selected test casses from command line that is found in the test file. For internal use only.
    size_t single_output_only;                ///< display the output for a single test only no summary and syntesis. For internal use only.
    size_t current_execution_status;          ///< the current test case status. This is used when the test cases run on a single process. For internal use only.
    size_t isolate_tests;                     ///< Isolate each test case to run in different process to prevent a crashing test case from crahsing others. For internal use only.
    char* flattened_cmd_argv;                 ///< Flattened command line argument for sub process. For internal use only.
    char* test_file_path;                     ///< The main test file full path. For internal use only.
    char* output_format;                      ///< The output format to print the test result in. For internal use only.
    void* output_stream;                      ///< Output stream to write message to, stdout by default. For internal use only.
    char** selected_test_cases_names;         ///< selected test cases from command line. For internal use only. e.g. --cester-test=Test2,Test1
    TestCase** current_test_case;             ///< The currently running test case. For internal use only.
} SuperTestInstance;

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
    "",
    __BASE_FILE__,
    "text",
    NULL,
    NULL,
    NULL
};

/**
    The test instance that contains the command line argument 
    length and values, with void* pointer that can be used to 
    share data between unit tests.
*/
typedef struct test_instance {
    int argc;                   ///< the length of the command line arg
    char **argv;                ///< the command line arguments 
    void *arg;                  ///< pointer to an object that can be passed between unit tests
} TestInstance;

/**
    The function signature for each test case. It accepts the ::test_instance 
    as it only argument. 
*/
typedef void (*cester_test)(TestInstance*);

typedef void (*cester_before_after_each)(TestInstance*, char * const, int);

typedef void (*cester_void)();

// cester options

/**
    Change the output stream used by cester to write data. The default is `stdout`. 
    E.g to change the output stream to a file. 
    
    \code CESTER_CHANGE_STREAM(fopen("./test.txt", "w+"));
    
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
    The total number of tests that passed. CESTER_TOTAL_TESTS_COUNT - CESTER_TOTAL_FAILED_TESTS_COUNT
*/
#define CESTER_TOTAL_PASSED_TESTS_COUNT (superTestInstance.total_tests_count - superTestInstance.total_failed_tests_count)

/**
    Run all the test registered in cester, the TestInstance* pointer 
    will be initalized with the pointer to the string arguments from 
    cli and the length of the arguments. The `void* arg` pointer in the 
    TestInstance* can be initalized in the *_BEFORE_* function to share 
    data between the unit tests.
*/
#define CESTER_RUN_ALL_TESTS(x,y) cester_run_all_test(x,y)

/**
    Shorthand macro for CESTER_NO_AFTER_ALL, CESTER_NO_AFTER_EACH, 
    CESTER_NO_BEFORE_ALL and CESTER_NO_BEFORE_EACH
*/
#define CESTER_NO_BEFORE_AFTER CESTER_NO_AFTER_ALL    \
                                CESTER_NO_AFTER_EACH  \
                                CESTER_NO_BEFORE_ALL  \
                                CESTER_NO_BEFORE_EACH \


// Assertions, Tests

/**

*/
#define cester_assert_true(x) cester_evaluate_expression(x, "(" #x ")", __FILE__, __LINE__)
#define cester_assert_false(x) cester_evaluate_expression(x == 0, "!(" #x ")", __FILE__, __LINE__)
#define cester_assert_null(x) cester_evaluate_expression(x == NULL, "(" #x ")", __FILE__, __LINE__)
#define cester_assert_not_null(x) cester_evaluate_expression(x != NULL, "!(" #x ")", __FILE__, __LINE__)
#define cester_assert_equal(x,y) cester_evaluate_expect_actual(x==y, 1, #x, #y, __FILE__, __LINE__)
#define cester_assert_not_equal(x,y) cester_evaluate_expect_actual(x!=y, 0, #x, #y, __FILE__, __LINE__)

#ifdef _WIN32
    int default_color = CESTER_RESET_TERMINAL;
    HANDLE hConsole;
#else
    void* default_color = CESTER_RESET_TERMINAL;
#endif

static inline void cester_str_value_after_first(char *, char, char**);

static inline char *cester_extract_name(char const* const file_path) {
    int i = 0, j = 0;
    int found_seperator = 0;
    char *file_name_only = malloc (sizeof (char) * 30);
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
    int i = 0;
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

static inline int extract_cester_arg(char* arg, char** out) {
    int i = 0;
    char* cester = "--cester-";
    *out = malloc (sizeof (char) * 200);
    
    while (1) {
        if (arg[i] == '\0') {
            if (i < 9) {
                free(*out);
                return 0;
            } else {
                break;
            }
        }
        if (arg[i] != cester[i] && i < 9) {
            free(*out);
            return 0;
        }
        if (i >= 9) {
            (*out)[i-9] = arg[i];
        }
        ++i;
    }
    (*out)[i-9] = '\0';
    return 1;
}

static inline int cester_string_equals(char* arg, char* arg1) {
    int i = 0;
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

static inline int cester_string_starts_with(char* arg, char* arg1) {
    int i = 0;
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
    int i = 0;
    int size = 0, current_index = 0;
    char* prefix = "test=";
    (*out) = malloc(sizeof(char**));
    
    (*out)[size] = malloc(sizeof(char*) * 200);
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
            (*out)[size] = malloc(sizeof(char*) * 200);
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
    int i = 0, index = 0;
    int found_char = 0;
    *out = malloc(sizeof(char) * 200);
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

static inline void cester_concat_str(char **out, const char * const extra) {
    int i = 0, index = strlen(*out);
    if (index == 0) {
        (*out) = malloc(sizeof(char) * 80000 );
    }
    while (1) {
        if (extra[i] == '\0') {
            break;
        }
        (*out)[index] = extra[i];
        continue_loop:
                      ++index;
                      ++i;
    }
    (*out)[index] = '\0';
}

#define CESTER_SELECTCOLOR(x) (superTestInstance.no_color == 1 ? default_color : x)
#define CESTER_GET_RESULT_AGGR (superTestInstance.total_failed_tests_count == 0 ? "SUCCESS" : "FAILURE")
#define CESTER_GET_RESULT_AGGR_COLOR (superTestInstance.total_failed_tests_count == 0 ? (CESTER_FOREGROUND_GREEN) : (CESTER_FOREGROUND_RED))

#ifdef _WIN32
#define CESTER_DELEGATE_FPRINT_STR(x,y) SetConsoleTextAttribute(hConsole, CESTER_SELECTCOLOR(x)); fprintf(superTestInstance.output_stream, "%s", y)
#define CESTER_DELEGATE_FPRINT_INT(x,y) SetConsoleTextAttribute(hConsole, CESTER_SELECTCOLOR(x)); fprintf(superTestInstance.output_stream, "%d", y)
#define CESTER_DELEGATE_FPRINT_DOUBLE(x,y) SetConsoleTextAttribute(hConsole, CESTER_SELECTCOLOR(x)); fprintf(superTestInstance.output_stream, "%f", y)
#define CESTER_DELEGATE_FPRINT_DOUBLE_2(x,y) SetConsoleTextAttribute(hConsole, CESTER_SELECTCOLOR(x)); fprintf(superTestInstance.output_stream, "%.2f", y)
#else
#define CESTER_DELEGATE_FPRINT_STR(x,y) fprintf(superTestInstance.output_stream, "%s%s%s", CESTER_SELECTCOLOR(x), y, CESTER_RESET_TERMINAL)
#define CESTER_DELEGATE_FPRINT_INT(x,y) fprintf(superTestInstance.output_stream, "%s%d%s", CESTER_SELECTCOLOR(x), y, CESTER_RESET_TERMINAL)
#define CESTER_DELEGATE_FPRINT_DOUBLE(x,y) fprintf(superTestInstance.output_stream, "%s%f%s", CESTER_SELECTCOLOR(x), y, CESTER_RESET_TERMINAL) 
#define CESTER_DELEGATE_FPRINT_DOUBLE_2(x,y) fprintf(superTestInstance.output_stream, "%s%.2f%s", CESTER_SELECTCOLOR(x), y, CESTER_RESET_TERMINAL) 
#endif

static inline int cester_string_equals(char* arg, char* arg1);

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
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-printversion    display cester version before running the tests\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-test=Test1,...  run only selected tests. Seperate the test cases by comma\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-version         display cester version and exit\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "    --cester-help            display this help info version and exit\n");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "See https://exoticlibraries.github.io/libcester/cmdlineargs.html for more details");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
}

static inline void cester_print_assertion(char const* const expression, char const* const file_path, size_t const line_num) {
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), (superTestInstance.verbose == 1 ? file_path : cester_extract_name(file_path) ));
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ":");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_YELLOW), line_num);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ":");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " in test case => '");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), (*superTestInstance.current_test_case)->name);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "'");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " with expr: '");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), expression);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "'");
}

static inline void cester_print_expect_actual(int expecting, char const* const expect, char const* const found, char const* const file_path, size_t const line_num) {
    cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, (superTestInstance.verbose == 1 ? file_path : cester_extract_name(file_path) ));
    cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, ":");
    cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, "line_num");
    cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, ":");
    cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, " in test case => '");
    cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, (*superTestInstance.current_test_case)->name);
    cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, "'");
    if (expecting == 0) {
        cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, " not expecting ");
    } else {
        cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, " expected ");
    }
    
    cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, expect);
    cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, ", found ");
    cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, found);
    
    /*CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), (superTestInstance.verbose == 1 ? file_path : cester_extract_name(file_path) ));
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ":");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_YELLOW), line_num);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ":");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " in test case => '");
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), (*superTestInstance.current_test_case)->name);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "'");
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
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " Tested: ");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_YELLOW), CESTER_TOTAL_TESTS_COUNT);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " | Passing: ");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_GREEN), CESTER_TOTAL_PASSED_TESTS_COUNT);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " | Failing: ");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_RED), CESTER_TOTAL_FAILED_TESTS_COUNT);
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), " | Skipped: ");
    CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_YELLOW), (superTestInstance.selected_test_cases_size > 0 ? superTestInstance.total_tests_count - superTestInstance.selected_test_cases_found : 0));
    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n"); 
}

static inline void cester_evaluate_expression(int eval_result, char const* const expression, char const* const file_path, size_t const line_num) {
    if (eval_result == 0) {
        superTestInstance.current_execution_status = CESTER_FAILURE;
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_RED), "FAILED ");
    } else {
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GREEN), "PASSED ");
    }
    cester_print_assertion(expression, file_path, line_num);
        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
    CESTER_RESET_TERMINAL_ATTR();
}

static inline void cester_evaluate_expect_actual(int eval_result, int expecting, char const* const expected, char const* const actual, 
                                                char const* const file_path, size_t const line_num) {
    if (eval_result == 0) {
        superTestInstance.current_execution_status = CESTER_FAILURE;
        cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, "FAILED ");
    } else if (superTestInstance.verbose == 1) {
        cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, "PASSED ");
    }
    cester_print_expect_actual(expecting, actual, expected, file_path, line_num);
    cester_concat_str(&(*superTestInstance.current_test_case)->execution_output, "\n");
}

/**
    Create a test case, this uses the first arguments as the test 
    case name and identifier and the body of the test. 
*/
#define CESTER_TEST(x,y,z) static void cester_test_##x(TestInstance* y);

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
#define CESTER_BEFORE_EACH(w,x,y,z) void cester_before_each_test(TestInstance* w, char * const x, int y);

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
#define CESTER_AFTER_EACH(w,x,y,z) void cester_after_each_test(TestInstance* w, char * const x, int y);

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

#include __BASE_FILE__

#undef CESTER_TEST
#undef CESTER_BEFORE_ALL
#undef CESTER_BEFORE_EACH
#undef CESTER_AFTER_ALL
#undef CESTER_AFTER_EACH
#undef CESTER_OPTIONS
#undef CESTER_BODY
#undef CESTER_MOCK_SIMPLE_FUNCTION
#undef CESTER_MOCK_FUNCTION


#define CESTER_TEST(x,y,z) { CESTER_UNKNOWN, __LINE__, 0.000, "", (cester_test_##x), #x, NORMAL_TEST },
#define CESTER_BEFORE_ALL(x,y) { CESTER_UNKNOWN, __LINE__, 0.000, "", (cester_before_all_test), "cester_before_all_test", BEFORE_ALL_TEST },
#define CESTER_BEFORE_EACH(w,x,y,z) { CESTER_UNKNOWN, __LINE__, 0.000, "", (cester_before_each_test), "cester_before_each_test", BEFORE_EACH_TEST },
#define CESTER_AFTER_ALL(x,y) { CESTER_UNKNOWN, __LINE__, 0.000, "", (cester_after_all_test), "cester_after_all_test", AFTER_ALL_TEST },
#define CESTER_AFTER_EACH(w,x,y,z) { CESTER_UNKNOWN, __LINE__, 0.000, "", (cester_after_each_test), "cester_after_each_test", AFTER_EACH_TEST },
#define CESTER_OPTIONS(x) { CESTER_UNKNOWN, __LINE__, 0.000, "", (cester_options_before_main), "cester_options_before_main", CESTER_OPTION_FUNCTION },
#define CESTER_BODY(x)
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,z) 
#define CESTER_MOCK_FUNCTION(x,y,z)

static TestCase cester_test_cases[] = {
#include __BASE_FILE__
{ CESTER_UNKNOWN, 0, 0.000, NULL, NULL, NULL, TESTS_TERMINATOR }
};

#undef CESTER_TEST
#undef CESTER_BEFORE_ALL
#undef CESTER_BEFORE_EACH
#undef CESTER_AFTER_ALL
#undef CESTER_AFTER_EACH
#undef CESTER_OPTIONS
#undef CESTER_BODY
#undef CESTER_MOCK_SIMPLE_FUNCTION
#undef CESTER_MOCK_FUNCTION

#define CESTER_TEST(x,y,z) static void cester_test_##x(TestInstance* y) { z  } 
#define CESTER_BEFORE_ALL(x,y) void cester_before_all_test(TestInstance* x) { y } 
#define CESTER_BEFORE_EACH(w,x,y,z) void cester_before_each_test(TestInstance* w, char * const x, int y) { z }
#define CESTER_AFTER_ALL(x,y) void cester_after_all_test(TestInstance* x) { y } 
#define CESTER_AFTER_EACH(w,x,y,z) void cester_after_each_test(TestInstance* w, char * const x, int y) { z }
#define CESTER_OPTIONS(x) void cester_options_before_main() { x }
#define CESTER_BODY(x) x;
#ifndef CESTER_NO_MOCK
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,z) y __wrap_##x { return z; }
#define CESTER_MOCK_FUNCTION(x,y,z) y __wrap_##x { z }
#else
#define CESTER_MOCK_SIMPLE_FUNCTION(x,y,z) 
#define CESTER_MOCK_FUNCTION(x,y,z) 
#endif

static inline int cester_run_test_no_isolation(TestInstance *, TestCase *, size_t);

static inline void write_testcase_junitxml(TestCase *a_test_case, char* file_name) {
    CESTER_DELEGATE_FPRINT_STR((default_color), "    <testcase classname=\"");
    CESTER_DELEGATE_FPRINT_STR((default_color), file_name);
    CESTER_DELEGATE_FPRINT_STR((default_color), "\" name=\"");
    CESTER_DELEGATE_FPRINT_STR((default_color), a_test_case->name);
    CESTER_DELEGATE_FPRINT_STR((default_color), "\" time=\"");
    CESTER_DELEGATE_FPRINT_DOUBLE_2((default_color), a_test_case->execution_time);
    CESTER_DELEGATE_FPRINT_STR((default_color), "\"");
    switch (a_test_case->execution_status) {
        case CESTER_SUCCESS:
            CESTER_DELEGATE_FPRINT_STR((default_color), "/>\n");
            break;
        case CESTER_SEGFAULT:
            CESTER_DELEGATE_FPRINT_STR((default_color), ">\n        <failure message=\"the test failed\" type=\"SegmentationFault\">");
            CESTER_DELEGATE_FPRINT_STR((default_color), a_test_case->execution_output);
            CESTER_DELEGATE_FPRINT_STR((default_color), "        </failure>\n    </testcase>\n");
            break;
        default:
            CESTER_DELEGATE_FPRINT_STR((default_color), ">\n        <failure message=\"the test failed\" type=\"TestFailed\">");
            CESTER_DELEGATE_FPRINT_STR((default_color), a_test_case->execution_output);
            CESTER_DELEGATE_FPRINT_STR((default_color), "        </failure>\n    </testcase>\n");
            break;
    }
    
}

static inline void cester_run_test(TestInstance *test_instance, TestCase *a_test_case, size_t index) {
    clock_t tic = clock();
    int last_status = CESTER_UNKNOWN;
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
        snprintf(command, 1500, "%s --cester-test=%s  --cester-singleoutput --cester-noisolation %s", test_instance->argv[0], a_test_case->name, superTestInstance.flattened_cmd_argv);

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

        last_status = (status & 0x80000000) ? CESTER_SEGFAULT : status;

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
#elif defined unix

#else
#warning "Isolated tests not supported in this environment. The tests will be run on a single process"
        last_status = cester_run_test_no_isolation(test_instance, a_test_case, index);
#endif
    } else {
        last_status = cester_run_test_no_isolation(test_instance, a_test_case, index);
    }
    if (last_status != CESTER_SUCCESS) {
        ++superTestInstance.total_failed_tests_count;
    }
    clock_t tok = clock();
    a_test_case->execution_time = (double)(tok - tic) / CLOCKS_PER_SEC;
    a_test_case->execution_status = last_status;
    
}

static inline int cester_run_test_no_isolation(TestInstance *test_instance, TestCase *a_test_case, size_t index) {
    int i;
    superTestInstance.current_execution_status = CESTER_SUCCESS;
    superTestInstance.current_test_case = &a_test_case;
    for (i=0;cester_test_cases[i].function != NULL;++i) {
        if (cester_test_cases[i].test_type == BEFORE_EACH_TEST) {
            ((cester_before_after_each)cester_test_cases[i].function)(test_instance, a_test_case->name, index);
        }
    }
    ((cester_test)a_test_case->function)(test_instance);
    for (i=0;cester_test_cases[i].function != NULL;++i) {
        if (cester_test_cases[i].test_type == AFTER_EACH_TEST) {
            ((cester_before_after_each)cester_test_cases[i].function)(test_instance, a_test_case->name, index);
        }
    }
    if (superTestInstance.single_output_only == 1) {
        CESTER_DELEGATE_FPRINT_STR((default_color), a_test_case->execution_output);
    }
    return superTestInstance.current_execution_status;
}

static inline int cester_run_all_test(int argc, char **argv) {
    int i = 0; 
    int j = 1; 
    int found_test = 0;
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
    
    // execute options
    for (int i=0;cester_test_cases[i].test_type != TESTS_TERMINATOR;++i) {
        if (cester_test_cases[i].test_type == CESTER_OPTION_FUNCTION) {
            ((cester_void)cester_test_cases[i].function)();
            
        } else if (cester_test_cases[i].test_type == NORMAL_TEST) {
            ++superTestInstance.total_tests_count;
        }
        
    }
    
    // resolve command line options
    for (;j < argc; ++j) {
        char* arg = argv[j];
        char* cester_option;
        if (extract_cester_arg(arg, &cester_option) == 1) {
            if (cester_string_equals(cester_option, "minimal") == 1) {
                superTestInstance.minimal = 1;
                
            } else if (cester_string_equals(cester_option, "verbose") == 1) {
                superTestInstance.verbose = 1;
                
            } else if (cester_string_equals(cester_option, "nocolor") == 1) {
                superTestInstance.no_color = 1;
                
            } else if (cester_string_equals(cester_option, "printversion") == 1) {
                superTestInstance.print_version = 1;
                
            } else if (cester_string_equals(cester_option, "singleoutput") == 1) {
                superTestInstance.single_output_only = 1;
                
            } else if (cester_string_equals(cester_option, "noisolation") == 1) {
                superTestInstance.isolate_tests = 0;
                
            } else if (cester_string_equals(cester_option, "version") == 1) {
                CESTER_NOCOLOR();
                cester_print_version();
                return EXIT_SUCCESS;
                
            } else if (cester_string_equals(cester_option, "help") == 1) {
                CESTER_NOCOLOR();
                cester_print_version();
                cester_print_help();
                return EXIT_SUCCESS;
                
            } else if (cester_string_starts_with(cester_option, "test=") == 1) {
                unpack_selected_extra_args(cester_option, &superTestInstance.selected_test_cases_names, &superTestInstance.selected_test_cases_size);
                
            } else if (cester_string_starts_with(cester_option, "output=") == 1) {
                cester_str_value_after_first(cester_option, '=', &superTestInstance.output_format);
                
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
    
    TestInstance *test_instance = malloc(sizeof(TestInstance*));
    test_instance->argc = argc;
    test_instance->argv = argv;
    
    for (i=0;cester_test_cases[i].function != NULL;++i) {
        if (cester_test_cases[i].test_type == BEFORE_ALL_TEST) {
            ((cester_test)cester_test_cases[i].function)(test_instance);
        }
    }
    clock_t tic = clock();
    if (superTestInstance.selected_test_cases_names == NULL) {
        for (i=0;cester_test_cases[i].function != NULL;++i) {
            if (cester_test_cases[i].test_type == NORMAL_TEST) {
                cester_run_test(test_instance, &cester_test_cases[i], i);
            }
        }
        
    } else {
        for (j = 0; j < superTestInstance.selected_test_cases_size; ++j) {
            selected_test_case_name = superTestInstance.selected_test_cases_names[j];
            found_test = 0;
            for (i=0;cester_test_cases[i].function != NULL;++i) {
                if (cester_test_cases[i].test_type == NORMAL_TEST) {
                    if (cester_string_equals(cester_test_cases[i].name, selected_test_case_name) == 1) {
                        found_test = 1;
                        ++superTestInstance.selected_test_cases_found;
                        cester_run_test(test_instance, &cester_test_cases[i], i);
                    }
                }
            }
            if (found_test == 0) {
                if (superTestInstance.minimal == 0 && cester_string_equals(superTestInstance.output_format, "text") == 1) {
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "Warning: the test case '");
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), superTestInstance.selected_test_cases_names[j]);
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_YELLOW), "' was not found! \n");
                }
            }
        }
    }
    if (superTestInstance.single_output_only == 0) {
        clock_t tok = clock();
        double time_spent = (double)(tok - tic) / CLOCKS_PER_SEC;
        for (i=0;cester_test_cases[i].function != NULL;++i) {
            if (cester_test_cases[i].test_type == AFTER_ALL_TEST) {
                ((cester_test)cester_test_cases[i].function)(test_instance);
            }
        }
        if (cester_string_equals(superTestInstance.output_format, "junitxml") == 1) {
            CESTER_DELEGATE_FPRINT_STR((default_color), "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n");
            CESTER_DELEGATE_FPRINT_STR((default_color), "<testsuite tests=\"");
            CESTER_DELEGATE_FPRINT_INT((default_color), superTestInstance.total_tests_count);
            CESTER_DELEGATE_FPRINT_STR((default_color), "\" failures=\"");
            CESTER_DELEGATE_FPRINT_INT((default_color), superTestInstance.total_failed_tests_count);
            CESTER_DELEGATE_FPRINT_STR((default_color), "\" name=\"");
            CESTER_DELEGATE_FPRINT_STR((default_color), cester_extract_name_only(test_instance->argv[0]));
            CESTER_DELEGATE_FPRINT_STR((default_color), "\" skipped=\"");
            CESTER_DELEGATE_FPRINT_INT((default_color), (superTestInstance.selected_test_cases_size > 0 ? superTestInstance.total_tests_count - superTestInstance.selected_test_cases_found : 0));
            CESTER_DELEGATE_FPRINT_STR((default_color), "\">\n");
            for (i=0;cester_test_cases[i].function != NULL;++i) {
                if (cester_test_cases[i].test_type == NORMAL_TEST && cester_test_cases[i].execution_status != CESTER_UNKNOWN) {
                    write_testcase_junitxml(&cester_test_cases[i], cester_extract_name_only(test_instance->argv[0]));
                }
            }
            CESTER_DELEGATE_FPRINT_STR((default_color), "</testsuite>\n");
        } else {
            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
            for (i=0;cester_test_cases[i].function != NULL;++i) {
                if (cester_test_cases[i].test_type == NORMAL_TEST && cester_test_cases[i].execution_status != CESTER_UNKNOWN) {
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), "  ");
                    if (cester_test_cases[i].execution_status == CESTER_SUCCESS) {
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
                    CESTER_DELEGATE_FPRINT_DOUBLE_2((CESTER_FOREGROUND_GRAY), cester_test_cases[i].execution_time);
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), ") ");
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_GRAY), cester_test_cases[i].name);
                    CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
                }
            }
            
            if (superTestInstance.minimal == 0) {
                CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "\n");
                for (i=0;cester_test_cases[i].function != NULL;++i) {
                    if (cester_test_cases[i].test_type == NORMAL_TEST && cester_test_cases[i].execution_status != CESTER_UNKNOWN) {
                        if (cester_test_cases[i].execution_status == CESTER_SEGFAULT) {
                            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "FAILED ");
                            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), (superTestInstance.verbose == 1 ? superTestInstance.test_file_path : cester_extract_name(superTestInstance.test_file_path) ));
                            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ":");
                            CESTER_DELEGATE_FPRINT_INT((CESTER_FOREGROUND_WHITE), cester_test_cases[i].line_num);
                            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), ": ");
                            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "in test case => '");
                            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), cester_test_cases[i].name);
                            CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), "' Segmentation fault \n");
                        }
                        CESTER_DELEGATE_FPRINT_STR((CESTER_FOREGROUND_WHITE), cester_test_cases[i].execution_output);
                    }
                }
            }
            
            print_test_result(time_spent);
            
            CESTER_RESET_TERMINAL_ATTR();
        }
    }
    if (CESTER_TOTAL_FAILED_TESTS_COUNT != 0) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

#ifndef CESTER_NO_MAIN
int main(int argc, char **argv) {
    return CESTER_RUN_ALL_TESTS(argc, argv);
}
#endif

#ifdef __cplusplus
}
#endif


#endif