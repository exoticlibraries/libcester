cmake_minimum_required(VERSION 3.10)
project(libcester_tests VERSION 1.0)

set(FILE_EXT "")
set(INCLUDE_PATHS -I${PWD}/../../include/ -I${PWD}/../include/ -I../../include/ -I../include/)
include_directories(${PWD}/../../include/ ${PWD}/../include/ ../../include/ ../include/)
add_executable(cester_test ./empty_c_file.c)
set_target_properties(cester_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./build/ )

IF (WIN32)
    set(FILE_EXT ".exe")
ENDIF()

# build and run the tests
# file(GLOB files "./test_mock_*.c")
file(GLOB files "./test_*.c")
foreach(filepath ${files})
    get_filename_component(filename ${filepath} NAME)
    get_filename_component(filenameonly ${filepath} NAME_WLE)
    
    set(mock_arg "")
    set(echo_var "")
    if("${filenameonly}" MATCHES "mock")
        set(mock_arg "-Wl,--wrap=multiply_by" "-Wl,--wrap=power_of")
        set(echo_var "echo")
    endif()
    
    add_custom_target(${filenameonly}_others
        
        COMMAND echo -------------------------------------------
        COMMAND echo Compiling ${filenameonly} 
        COMMAND echo -------------------------------------------
        
        # clang 
        COMMAND ${echo_var} clang -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_clang${FILE_EXT}
        COMMAND ${echo_var} clang -ansi -pedantic-errors -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_clang_ansi${FILE_EXT}
        COMMAND ${echo_var} clang++ -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_clang_cpp${FILE_EXT}
        COMMAND ${echo_var} clang++ -x c -ansi -pedantic-errors -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_clang_cpp_ansi${FILE_EXT}
    
        # gcc
        COMMAND gcc -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_gcc${FILE_EXT}
        COMMAND gcc -ansi -pedantic-errors -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_gcc_ansi${FILE_EXT}
        COMMAND ${echo_var} g++ -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_gcc_cpp${FILE_EXT}
        COMMAND ${echo_var} g++ -ansi -pedantic-errors -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_gcc_cpp_ansi${FILE_EXT}
    )
    
    add_custom_command(TARGET cester_test
        POST_BUILD
        
        COMMAND echo -------------------------------------------
        COMMAND echo Running ${filenameonly} 
        COMMAND echo -------------------------------------------
        
        # clang
        COMMAND ${echo_var} ./build/${filenameonly}_clang${FILE_EXT}
        COMMAND ${echo_var} ./build/${filenameonly}_clang_ansi${FILE_EXT} --cester-output=junitxml
        COMMAND ${echo_var} ./build/${filenameonly}_clang_cpp${FILE_EXT} --cester-output=tap
        COMMAND ${echo_var} ./build/${filenameonly}_clang_cpp_ansi${FILE_EXT} --cester-output=tapV13
        
        # gcc
        COMMAND ./build/${filenameonly}_gcc${FILE_EXT}
        COMMAND ./build/${filenameonly}_gcc_ansi${FILE_EXT} --cester-output=junitxml
        COMMAND ${echo_var} ./build/${filenameonly}_gcc_cpp${FILE_EXT} --cester-output=tap
        COMMAND ${echo_var} ./build/${filenameonly}_gcc_cpp_ansi${FILE_EXT} --cester-output=tapV13
    )
    
    add_dependencies(cester_test ${filenameonly}_others)
endforeach()

#cmake CMakeLists.txt -G"Unix Makefiles"
