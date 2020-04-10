
/**
    \copyright GNU General Public License v3.0 Copyright (c) 2019, Adewale Azeez 
    \author Adewale Azeez <azeezadewale98@gmail.com>
    \date 10 April 2020
    \file cester.h
*/


#ifndef LIBOPEN_CESTER_H
#define LIBOPEN_CESTER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>

/**
    The test instance that contains the command line argument 
    length and values, with void* pointer that can be used to 
    share data between unit tests.
*/
typedef struct test_instance {
    int argc;                   ///< the length of the command line arg
    char **argv;                ///< the command line arguments 
    void* arg;                  ///< pointer to an object that can be passed between unit tests
} TestInstance;


/**
    The functions that would be invoked once before running 
    any test in the test file.
*/
#define CESTER_BEFORE_ALL(x) void CESTER_before_all_test(TestInstance* x)

/**
    The functions that would be invoked before each test.
*/
#define CESTER_BEFORE(x,y) void CESTER_before_test(TestInstance* x, char* y)


/**
    The functions that would be invoked once after running 
    all the tests in the test file.
*/
#define CESTER_AFTER_ALL(x) void CESTER_after_all_test(TestInstance* x)


/**
    The functions that would be invoked after each test is 
    ran.
*/
#define CESTER_AFTER(x,y) void CESTER_after_test(TestInstance* x, char* y)


/**

*/
#define CESTER_RUN_ALL_TESTS(x,y) TestInstance* test_instance = malloc(sizeof(TestInstance*)); \
                                  test_instance->argc = x; \
                                  test_instance->argv = y; \
                                  CESTER_before_all_test(test_instance); \
                                  CESTER_before_test(test_instance, "test1"); \
                                  CESTER_after_test(test_instance, "test1"); \
                                  CESTER_after_all_test(test_instance);

#ifdef __cplusplus
}
#endif


#endif