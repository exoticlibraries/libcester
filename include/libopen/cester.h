
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
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
#define LIBOPEN_API __declspec(dllexport)
#else
#define LIBOPEN_API extern
#endif

#ifdef _WIN32

#define CESTER_RESET_TERMINAL      15   ///< reset the terminal color //Nothing
#define CESTER_BOLD                15   ///< bold text                //Nothing
#define CESTER_FOREGROUND_BLACK    8    ///< gray terminal foreground color
#define CESTER_FOREGROUND_RED      4    ///< red terminal foreground color
#define CESTER_FOREGROUND_GREEN    2    ///< green foreground color
#define CESTER_FOREGROUND_YELLOW   6    ///< yellow terminal foreground color
#define CESTER_FOREGROUND_BLUE     3    ///< blue terminal foreground color
#define CESTER_FOREGROUND_MAGENTA  5    ///< magenta terminal foreground color
#define CESTER_FOREGROUND_CYAN     11   ///< cyan terminal foreground color
#define CESTER_FOREGROUND_WHITE    15   ///< white terminal foreground color
#define CESTER_BACKGROUND_BLACK    0    ///< black terminal background color
#define CESTER_BACKGROUND_RED      64   ///< red terminal background color
#define CESTER_BACKGROUND_GREEN    39   ///< green terminal background color
#define CESTER_BACKGROUND_YELLOW   96   ///< yellow terminal background color
#define CESTER_BACKGROUND_BLUE     48   ///< blue terminal background color
#define CESTER_BACKGROUND_MAGENTA  87   ///< magenta terminal background color
#define CESTER_BACKGROUND_CYAN     176  ///< cyan terminal background color
#define CESTER_BACKGROUND_GRAY     0    ///< gray terminal background color

#else
    
#define CESTER_RESET_TERMINAL      "\x1B[0m"     ///< reset the terminal color
#define CESTER_BOLD                "\x1B[1m"     ///< bold text 
#define CESTER_FOREGROUND_BLACK    "\x1B[30m"    ///< gray terminal foreground color
#define CESTER_FOREGROUND_RED      "\x1B[31m"    ///< red terminal foreground color
#define CESTER_FOREGROUND_GREEN    "\x1B[32m"    ///< green foreground color
#define CESTER_FOREGROUND_YELLOW   "\x1B[33m"    ///< yellow terminal foreground color
#define CESTER_FOREGROUND_BLUE     "\x1B[34m"    ///< blue terminal foreground color
#define CESTER_FOREGROUND_MAGENTA  "\x1B[35m"    ///< magenta terminal foreground color
#define CESTER_FOREGROUND_CYAN     "\x1B[36m"    ///< cyan terminal foreground color
#define CESTER_FOREGROUND_WHITE    "\x1B[37m"    ///< white terminal foreground color
#define CESTER_BACKGROUND_BLACK    "\x1B[40m"    ///< black terminal background color
#define CESTER_BACKGROUND_RED      "\x1B[41m"    ///< red terminal background color
#define CESTER_BACKGROUND_GREEN    "\x1B[42m"    ///< green terminal background color
#define CESTER_BACKGROUND_YELLOW   "\x1B[43m"    ///< yellow terminal background color
#define CESTER_BACKGROUND_BLUE     "\x1B[44m"    ///< blue terminal background color
#define CESTER_BACKGROUND_MAGENTA  "\x1B[45m"    ///< magenta terminal background color
#define CESTER_BACKGROUND_CYAN     "\x1B[46m"    ///< cyan terminal background color
#define CESTER_BACKGROUND_WHITE    "\x1B[47m"    ///< gray terminal background color

#endif

typedef struct test_case {
    void *function;        ///< the function that enclosed the tests. For internal use only.
    char *name;            ///< the test function name. For internal use only.
} TestCase;

/**
    This structure manages the _BEFORE_ and _AFTER_ functions 
    for the test main ::test_instance. And also accounts for all the 
    registered test cases. This is for Cester internal use only.
*/
typedef struct super_test_instance {
    size_t test_function_count;      ///< the number of tests i the instance. For internal use only.
    size_t no_color;                 ///< Do not print to the console with color if one. For internal use only.
    size_t total_tests_count;        ///< the total number of tests to run, assert, eval e.t.c. To use in your code call CESTER_TOTAL_TESTS_COUNT
    size_t total_failed_tests_count; ///< the total number of tests that failed. To use in your code call CESTER_TOTAL_FAILED_TESTS_COUNT
    size_t minimal;                  ///< prints minimal output into the output stream
    TestCase **test_cases;           ///< all the test cases in the instance. For internal use only.
    void *output_stream;             ///< Output stream to write message to, stdout by default. For internal use only.
} SuperTestInstance;

SuperTestInstance superTestInstance = { 
    0,
    0,
    0,
    0,
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
*/
#define CESTER_NOCOLOR() (superTestInstance.no_color = 1)

/**
    The function that would be invoked once before running 
    any test in the test file. You can only have one of this function 
    in a test file.
*/
#define CESTER_BEFORE_ALL(x) void cester_before_all_test(TestInstance* x)

/**
    Notify cester that there is no function to execute before running 
    all the tests.
*/
#define  CESTER_NO_BEFORE_ALL void cester_before_all_test(TestInstance* x) {}

/**
    The function that would be invoked before each test. You can only 
    have one of this function in a test file.
*/
#define CESTER_BEFORE_EACH(x,y,z) void cester_before_each_test(TestInstance* x, char * const y, int z)

/**
    Notify cester that there is no function to run before each of the 
    tests.
*/
#define CESTER_NO_BEFORE_EACH void cester_before_each_test(TestInstance* x, char * const y, int z) {}

/**
    The function that would be invoked once after running 
    all the tests in the test file. You can only have one of this function 
    in a test file.
*/
#define CESTER_AFTER_ALL(x) void cester_after_all_test(TestInstance* x)

/**
    Notify cester that there is no function to execute after running 
    all the tests.
*/
#define CESTER_NO_AFTER_ALL void cester_after_all_test(TestInstance* x) {}

/**
    The functions that would be invoked after each test is 
    ran. You can only have one of this function in a test file.
*/
#define CESTER_AFTER_EACH(x,y,z) void cester_after_each_test(TestInstance* x, char * const y, int z)

/**
    Notify cester that there is no function to run after each of the 
    tests.
*/
#define CESTER_NO_AFTER_EACH void cester_after_each_test(TestInstance* x, char * const y, int z) {}

/**
    Create a test case, this uses the first arguments as the test 
    case name and identifier. But you still need to call CESTER_REGISTER 
    with the name to make cester aware of the test case. 
    
    The second argument is the test instance object that is shared between 
    the test cases.
*/
#define CESTER_TEST(x,y) char * const Cester_Test_##x = #x ; \
                         void x(TestInstance* y)

/**
    Register a test to make cester aware of the test case. 
    In the future this should not be required.
*/
#define CESTER_REGISTER(x) cester_register_test(x, Cester_Test_##x)

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
#define cester_assert(x) cester_evaluate_expression(x, "(" #x ")", __FILE__, __LINE__)
#define cester_assert_not(x) cester_evaluate_expression(x, "!(" #x ")")

#ifdef _WIN32
    int default_color = CESTER_RESET_TERMINAL;
    HANDLE hConsole;
#else
    void* default_color = CESTER_RESET_TERMINAL;
#endif
            
void cester_before_all_test(TestInstance* x);
void cester_after_all_test(TestInstance* x);
void cester_before_each_test(TestInstance* x, char * const y, int z);
void cester_after_each_test(TestInstance* x, char * const y, int z);

#include <stdio.h>
static inline void cester_register_test(cester_test ctest, char * const test_name) {
    if (superTestInstance.test_cases==NULL) {
        superTestInstance.test_cases = malloc(sizeof(TestCase **));
    }
    TestCase *a_test_case = malloc(sizeof(TestCase*));
    a_test_case->name = test_name;
    a_test_case->function = ctest;
    superTestInstance.test_cases[superTestInstance.test_function_count] = a_test_case;
    superTestInstance.test_function_count++; 
}

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
        i++;
    }
    file_name_only[j] = '\0';
    return file_name_only;
}

#ifdef _WIN32
#define CESTER_DELEGATE_FPRINT_STR(x,y) SetConsoleTextAttribute(hConsole, x); fprintf(superTestInstance.output_stream, "%s", y)
#define CESTER_DELEGATE_FPRINT_INT(x,y) SetConsoleTextAttribute(hConsole, x); fprintf(superTestInstance.output_stream, "%d", y)
#define CESTER_DELEGATE_FPRINT_DOUBLE(x,y) SetConsoleTextAttribute(hConsole, x); fprintf(superTestInstance.output_stream, "%f", y)
#else
#define CESTER_DELEGATE_FPRINT_STR(x,y) fprintf(superTestInstance.output_stream, "%s%s%s", x, y, CESTER_RESET_TERMINAL)
#define CESTER_DELEGATE_FPRINT_INT(x,y) fprintf(superTestInstance.output_stream, "%s%d%s", x, y, CESTER_RESET_TERMINAL)
#define CESTER_DELEGATE_FPRINT_DOUBLE(x,y) fprintf(superTestInstance.output_stream, "%s%f%s", x, y, CESTER_RESET_TERMINAL) 
#endif

static inline void cester_print_failed_assertion(char const* const expression, char const* const file_path, size_t const line_num) {
    char* file_name = cester_extract_name(file_path);
    if (superTestInstance.no_color == 1) {
        fprintf(superTestInstance.output_stream, ":");
    } else {
        //test4.c:95426: assertion in 'TestName' => (1 == 3) FAILED
        CESTER_DELEGATE_FPRINT_STR(default_color, file_name);
        CESTER_DELEGATE_FPRINT_STR(default_color, ":");
        CESTER_DELEGATE_FPRINT_INT(CESTER_FOREGROUND_YELLOW, line_num);
        CESTER_DELEGATE_FPRINT_STR(default_color, ":");
        CESTER_DELEGATE_FPRINT_STR(default_color, " assertion in '");
        CESTER_DELEGATE_FPRINT_STR(CESTER_FOREGROUND_CYAN, "TestName");
        if (superTestInstance.minimal == 0) {
            CESTER_DELEGATE_FPRINT_STR(default_color, " => ");
            CESTER_DELEGATE_FPRINT_STR(CESTER_FOREGROUND_CYAN, expression);
        }
        //CESTER_DELEGATE_FPRINT_STR(default_color, "'\n");
    }
}

static inline void print_test_result(double time_spent) {
    CESTER_DELEGATE_FPRINT_STR(default_color, "\nRan ");
    CESTER_DELEGATE_FPRINT_INT(default_color, superTestInstance.total_tests_count);
    CESTER_DELEGATE_FPRINT_STR(default_color, " test(s) in ");
    CESTER_DELEGATE_FPRINT_DOUBLE(default_color, (time_spent > 60 ? (time_spent / 60) : time_spent) );
    CESTER_DELEGATE_FPRINT_STR(default_color, (time_spent > 60 ? " Minutes\n" : " Seconds\n" ));
}

static inline void cester_evaluate_expression(int eval_result, char const* const expression, char const* const file_path, size_t const line_num) {
    ++superTestInstance.total_tests_count;
    if (eval_result == 0) {
        ++superTestInstance.total_failed_tests_count;
        cester_print_failed_assertion(expression, file_path, line_num);
    }
}

static inline int cester_run_all_test(int argc, char **argv) {
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
    TestInstance *test_instance = malloc(sizeof(TestInstance*));
    test_instance->argc = argc;
    test_instance->argv = argv;
    cester_before_all_test(test_instance);
    
    int i = 0; 
    clock_t tic = clock();
    for (; i < superTestInstance.test_function_count; i++) {
        TestCase *a_test_case = superTestInstance.test_cases[i];
        cester_before_each_test(test_instance, a_test_case->name, i);
        ((cester_test)a_test_case->function)(test_instance);
        cester_after_each_test(test_instance, a_test_case->name, i);
        free(a_test_case);
    }
    clock_t tok = clock();
    double time_spent = (double)(tok - tic) / CLOCKS_PER_SEC;
    
    cester_after_all_test(test_instance);
    print_test_result(time_spent);
    
    #ifdef _WIN32
        SetConsoleTextAttribute(hConsole, default_color);
    #endif
    return EXIT_SUCCESS;
}

#ifdef __cplusplus
}
#endif


#endif