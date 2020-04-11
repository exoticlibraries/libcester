
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
    int test_count;             ///< the number of tests i the instance. For internal use only.
    TestCase **test_cases;      ///< all the test cases in the instance. For internal use only.
} SuperTestInstance;

SuperTestInstance superTestInstance = { 
    0,
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
    The function that would be invoked once before running 
    any test in the test file. You can only have one of this function 
    in a test file.
*/
#define CESTER_BEFORE_ALL(x) void CESTER_before_all_test(TestInstance* x)

/**
    Notify cester that there is no function to execute before running 
    all the tests.
*/
#define  CESTER_NO_BEFORE_ALL void CESTER_before_all_test(TestInstance* x) {}

/**
    The function that would be invoked before each test. You can only 
    have one of this function in a test file.
*/
#define CESTER_BEFORE_EACH(x,y,z) void CESTER_before_each_test(TestInstance* x, char * const y, int z)

/**
    Notify cester that there is no function to run before each of the 
    tests.
*/
#define CESTER_NO_BEFORE_EACH void CESTER_before_each_test(TestInstance* x, char * const y, int z) {}

/**
    The function that would be invoked once after running 
    all the tests in the test file. You can only have one of this function 
    in a test file.
*/
#define CESTER_AFTER_ALL(x) void CESTER_after_all_test(TestInstance* x)

/**
    Notify cester that there is no function to execute after running 
    all the tests.
*/
#define CESTER_NO_AFTER_ALL void CESTER_after_all_test(TestInstance* x) {}

/**
    The functions that would be invoked after each test is 
    ran. You can only have one of this function in a test file.
*/
#define CESTER_AFTER_EACH(x,y,z) void CESTER_after_each_test(TestInstance* x, char * const y, int z)

/**
    Notify cester that there is no function to run after each of the 
    tests.
*/
#define CESTER_NO_AFTER_EACH void CESTER_after_each_test(TestInstance* x, char * const y, int z) {}

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
#define CESTER_REGISTER(x) register_test(x, Cester_Test_##x)

/**
    Run all the test registered in cester, the TestInstance* pointer 
    will be initalized with the pointer to the string arguments from 
    cli and the length of the arguments. The `void* arg` pointer in the 
    TestInstance* can be initalized in the *_BEFORE_* function to share 
    data between the unit tests.
*/
#define CESTER_RUN_ALL_TESTS(x,y) cester_run_all_test(x,y)

void CESTER_before_all_test(TestInstance* x);

void CESTER_after_all_test(TestInstance* x);

void CESTER_before_each_test(TestInstance* x, char * const y, int z);

void CESTER_after_each_test(TestInstance* x, char * const y, int z);

#include <stdio.h>
void register_test(cester_test ctest, char * const test_name) { 
    if (superTestInstance.test_cases==NULL) {
        superTestInstance.test_cases = malloc(sizeof(TestCase **));
    }
    TestCase *a_test_case = malloc(sizeof(TestCase*));
    a_test_case->name = test_name;
    a_test_case->function = ctest;
    superTestInstance.test_cases[superTestInstance.test_count] = a_test_case;
    superTestInstance.test_count++; 
}

static inline int cester_run_all_test(int argc, char **argv) {
    TestInstance *test_instance = malloc(sizeof(TestInstance*));
    test_instance->argc = argc;
    test_instance->argv = argv;
    CESTER_before_all_test(test_instance);
    
    int i = 0; 
    for (; i < superTestInstance.test_count; i++) {
        TestCase *a_test_case = superTestInstance.test_cases[i];
        CESTER_before_each_test(test_instance, a_test_case->name, i);
        ((cester_test)a_test_case->function)(test_instance);
        CESTER_after_each_test(test_instance, a_test_case->name, i);
        free(a_test_case);
    }
    
    CESTER_after_all_test(test_instance);
    
    return EXIT_SUCCESS;
}

#ifdef __cplusplus
}
#endif


#endif