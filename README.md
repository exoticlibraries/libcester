# libcester
A header only unit testing framework for C.


 - [x] can select test from command line arg
 - [x] enable disable output coloring
 - [x] print cester version 
 - [x] set super instance attr from command line
 - [x] --cester-verbose option to print test line by line and show if passed or failed
 - [x] --cester-minimal to not print expression in result
 - [x] --cester-nocolor to not print info in the stream with color
 - [x] --cester-test=Test,.. to select the test cases to run e.g --cester-test=Test1,Test2 to run only Test1 or Test2
 - [x] prints out name of each test case before running
 - [x] --cester-version to see cester version only
 - [x] --cester-help to view cester help messsage
 - [x] --cester-printversion to display cester version before running test
 
Any command line option starting with `--cester-*` will be parsed as 
cester option.
 
Execution time measurement starts immediately before test cases not when the program 
starts