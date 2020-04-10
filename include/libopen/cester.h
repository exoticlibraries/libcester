
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

/**
    This structure manages the _BEFORE_ and _AFTER_ functions 
    for the test main ::test_instance. And also accounts for all the 
    registered test cases. This is for Cester internal use only.
*/
typedef struct super_test_instance {
    int has_before_all;         ///< if 1 the test instance has the CESTER_BEFORE_ALL function. For internal use only.
    int has_after_all;          ///< if 1 the test instance has the CESTER_AFTER_ALL function. For internal use only.
    int has_before;             ///< if 1 the test instance has the CESTER_BEFORE function. For internal use only.
    int has_after;              ///< if 1 the test instance has the CESTER_AFTER function. For internal use only.
    void **tests;               ///< all the tests in the instance. For internal use only.
} SuperTestInstance;

SuperTestInstance superTestInstance = { 
    0,
    0,
    0,
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
    Notify cester of the before all function. This is important as 
    cester does not magically know when CESTER_BEFORE_ALL function is 
    decalared. This should be in the main function before CESTER_RUN_ALL_TESTS.
*/
#define CESTER_REGISTER_BEFORE_ALL superTestInstance.has_before_all = 1;

/**
    The function that would be invoked before each test. You can only 
    have one of this function in a test file.
*/
#define CESTER_BEFORE_EACH(x,y) void CESTER_before_each_test(TestInstance* x, char* y)

/**
    The function that would be invoked once after running 
    all the tests in the test file. You can only have one of this function 
    in a test file.
*/
#define CESTER_AFTER_ALL(x) void CESTER_after_all_test(TestInstance* x)

/**
    Notify cester of the before all function. This is important as 
    cester does not magically know when CESTER_BEFORE_ALL function is 
    decalared. This should be in the main function before CESTER_RUN_ALL_TESTS.
*/
#define CESTER_REGISTER_AFTER_ALL superTestInstance.has_after_all = 1;

/**
    The functions that would be invoked after each test is 
    ran. You can only have one of this function in a test file.
*/
#define CESTER_AFTER_EACH(x,y) void CESTER_after_each_test(TestInstance* x, char* y)


/**

*/
#define CESTER_TEST(x,y) void x(TestInstance* y)

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

void CESTER_before_each_test(TestInstance* x, char* y);

void CESTER_after_each_test(TestInstance* x, char* y);

#include <stdio.h>
static inline int cester_run_all_test(int argc, char **argv) {
    TestInstance* test_instance = malloc(sizeof(TestInstance*));
    test_instance->argc = argc;
    test_instance->argv = argv;
    if (superTestInstance.has_before_all == 1) {
        CESTER_before_all_test(test_instance);
    }
    //for each test
    /*;
    if (1==0) {
        CESTER_before_test(test_instance, "test1");
        CESTER_after_test(test_instance, "test1");
    }*/
    if (superTestInstance.has_after_all == 1) {
        CESTER_after_all_test(test_instance);
    }
    return 0;
}

#ifdef __cplusplus
}
#endif


#endif