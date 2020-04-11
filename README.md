# libcester
A header only unit testing framework for C.


 - [ ] can select test from command line arg
 - [ ] enable disable output coloring
 - [ ] print cester version 
 - [ ] set super instance attr from command line
 - [ ] --cester-verbose option to print test line by line and show if passed or failed
 - [x] --cester-minimal to not print expression in result
 - [x] --cester-nocolor to not print info in the stream with color
 
Any command line option starting with `--cester-*` will be parsed as 
cester option.
 
Execution time measurement starts immediately before test cases not when the program 
starts