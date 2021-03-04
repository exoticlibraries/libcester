#!cmake CMakeLists.txt -G"Unix Makefiles"; make
cmake_minimum_required(VERSION 3.17)
project(libcester_tests VERSION 1.0)

set(FILE_EXT "")
set(CL_32 "echo")
set(VISUAL_STUDIO_BAT_CMD "")
set(WINDOWS_CMD_AND "")
set(INCLUDE_PATHS -I${PWD}/../../include/ -I${PWD}/../include/ -I../../include/ -I../include/)
set(CL_INCLUDE_PATHS /I${PWD}/../../include/ /I${PWD}/../include/ /I../../include/ /I../include/)
include_directories(${PWD}/../../include/ ${PWD}/../include/ ../../include/ ../include/)
add_executable(cester_test ./empty_c_file.c)
add_executable(vs_cester_test ./empty_c_file.c)
set_target_properties(cester_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./build/ )
set_target_properties(vs_cester_test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ./build/ )

IF (WIN32)
    set(FILE_EXT ".exe")
    set(WINDOWS_CMD_AND "&&")
    file(GLOB visual_studio_bats "C:/Program Files (x86)/Microsoft Visual Studio/*/BuildTools/*/Tools/VsDevCmd.bat")
    foreach(vs_filepath ${visual_studio_bats})
        message(STATUS "PATH VS: " ${vs_filepath}  )
        set(VISUAL_STUDIO_BAT_CMD call ${vs_filepath})
        set(CL_32 "cl")
        break()
    endforeach()
    
ENDIF()

# build and run the tests
# file(GLOB files "./test_mock_*.c")
file(GLOB files "./test_*.c")
foreach(filepath ${files})
    message(STATUS "FilePath: " ${filepath}  )
    get_filename_component(filename ${filepath} NAME)
    get_filename_component(filenameonly ${filepath} NAME_WLE)
    
    set(mock_arg "")
    set(echo_var "")
    set(echo_var2 "")
    set(address_sanitizer "")
    set(clang_m32 "-m32")
    set(ms_cl_echo "echo")
    set(mac_comment_32 "")
    set(skip_cpp_ansi "")
    if(UNIX)
        set(address_sanitizer "-fsanitize=address")
        set(skip_cpp_ansi "--cester-test=")
    endif (UNIX)
    if(WIN32)
        set(clang_m32 "")
        set(ms_cl_echo "")
    endif (WIN32)
    if("${filenameonly}" MATCHES "mock")
        set(mock_arg "-Wl,--wrap=multiply_by" "-Wl,--wrap=power_of")
        set(echo_var "echo")
        if(APPLE)
            set(echo_var2 "echo")
        endif()
    endif()
    if("${filenameonly}" MATCHES "stream")
        set(ms_cl_echo "echo")
    endif()
    if("${filenameonly}" MATCHES "segfault" OR "${filenameonly}" MATCHES "stream_" OR "${filenameonly}" MATCHES "should_fail" OR "${filenameonly}" MATCHES "mem_leak_detection")
        set(address_sanitizer "")
    endif()
    if(APPLE)
        set(mac_comment_32 "echo")
        set(mock_arg "")
    endif (APPLE)
    
    add_custom_target(${filenameonly}__
        
        COMMAND echo -------------------------------------------
        COMMAND echo Compiling ${filenameonly}
        COMMAND echo -------------------------------------------
        
        # clang 
        COMMAND ${echo_var} ${echo_var2} clang -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_clang${FILE_EXT}
        COMMAND ${echo_var} ${echo_var2} clang -ansi -pedantic-errors -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_clang_ansi${FILE_EXT}
        COMMAND ${echo_var} ${echo_var2} clang++ -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_clang_cpp${FILE_EXT}
        COMMAND ${echo_var} ${echo_var2} clang++ -ansi -pedantic-errors -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_clang_cpp_ansi${FILE_EXT}
        COMMAND ${echo_var} ${mac_comment_32} ${echo_var2} clang ${clang_m32} -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_clang_32${FILE_EXT}
        COMMAND ${echo_var} ${mac_comment_32} ${echo_var2} clang ${clang_m32} -ansi -pedantic-errors -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_clang_ansi_32${FILE_EXT}
        COMMAND ${echo_var} ${mac_comment_32} ${echo_var2} clang++ ${clang_m32} -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_clang_cpp_32${FILE_EXT}
        COMMAND ${echo_var} ${mac_comment_32} ${echo_var2} clang++ -ansi -pedantic-errors ${clang_m32} -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_clang_cpp_ansi_32${FILE_EXT}
    
        # gcc
        COMMAND ${echo_var2} gcc -I. ${address_sanitizer} ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_gcc${FILE_EXT}
        COMMAND ${echo_var2} gcc -ansi -pedantic-errors ${address_sanitizer} -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_gcc_ansi${FILE_EXT}
        COMMAND ${echo_var} ${echo_var2} g++ ${address_sanitizer} -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_gcc_cpp${FILE_EXT}
        COMMAND ${echo_var} ${echo_var2} g++ -ansi -pedantic-errors ${address_sanitizer} -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_gcc_cpp_ansi${FILE_EXT}
        COMMAND ${mac_comment_32} ${echo_var2} gcc -m32 ${address_sanitizer} -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_gcc_32${FILE_EXT}
        COMMAND ${mac_comment_32} ${echo_var2} gcc -m32 -ansi -pedantic-errors ${address_sanitizer} -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_gcc_ansi_32${FILE_EXT}
        COMMAND ${mac_comment_32} ${echo_var} ${echo_var2} g++ -m32 ${address_sanitizer} -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_gcc_cpp_32${FILE_EXT}
        COMMAND ${mac_comment_32} ${echo_var} ${echo_var2} g++ -ansi -pedantic-errors -m32 ${address_sanitizer} -I. ${INCLUDE_PATHS} ${filepath} ${mock_arg} -o ./build/${filenameonly}_gcc_cpp_ansi_32${FILE_EXT}

        # cl
        COMMAND ${ms_cl_echo} ${echo_var} ${VISUAL_STUDIO_BAT_CMD} ${WINDOWS_CMD_AND} ${ms_cl_echo} ${echo_var} ${CL_32} /D__BASE_FILE__=\\\"${filepath}\\\" /I. ${CL_INCLUDE_PATHS} ${filepath} /Fe./build/${filenameonly}_cl${FILE_EXT}
    )
    
    add_custom_command(TARGET cester_test
        POST_BUILD
        
        COMMAND echo -------------------------------------------
        COMMAND echo Running ${filenameonly} 
        COMMAND echo -------------------------------------------
        
        # clang
        COMMAND ${echo_var} ${echo_var2} ./build/${filenameonly}_clang${FILE_EXT}
        COMMAND ${echo_var} ${echo_var2} ./build/${filenameonly}_clang_ansi${FILE_EXT} --cester-output=junitxml
        COMMAND ${echo_var} ${echo_var2} ./build/${filenameonly}_clang_cpp${FILE_EXT} --cester-output=tap
        COMMAND ${echo_var} ${echo_var2} ./build/${filenameonly}_clang_cpp_ansi${FILE_EXT} ${skip_cpp_ansi}
        COMMAND ${echo_var} ${echo_var2} ${mac_comment_32} ./build/${filenameonly}_clang_32${FILE_EXT} --cester-output=tapV13
        COMMAND ${echo_var} ${echo_var2} ${mac_comment_32} ./build/${filenameonly}_clang_ansi_32${FILE_EXT} --cester-output=text
        COMMAND ${echo_var} ${echo_var2} ${mac_comment_32} ./build/${filenameonly}_clang_cpp_32${FILE_EXT}
        COMMAND ${echo_var} ${echo_var2} ${mac_comment_32} ./build/${filenameonly}_clang_cpp_ansi_32${FILE_EXT} ${skip_cpp_ansi}
        
        # gcc
        COMMAND ${echo_var} ${echo_var2} ./build/${filenameonly}_gcc${FILE_EXT}
        COMMAND ${echo_var} ${echo_var2} ./build/${filenameonly}_gcc_ansi${FILE_EXT} --cester-output=junitxml
        COMMAND ${echo_var} ${echo_var2} ./build/${filenameonly}_gcc_cpp${FILE_EXT} --cester-output=tap
        COMMAND ${echo_var} ${echo_var2} ./build/${filenameonly}_gcc_cpp_ansi${FILE_EXT} --cester-output=tapV13 ${skip_cpp_ansi}
        COMMAND ${echo_var} ${echo_var2} ${mac_comment_32} ./build/${filenameonly}_gcc_32${FILE_EXT} --cester-output=tapV13
        COMMAND ${echo_var} ${echo_var2} ${mac_comment_32} ./build/${filenameonly}_gcc_ansi_32${FILE_EXT} --cester-output=text
        COMMAND ${echo_var} ${echo_var2} ${mac_comment_32} ./build/${filenameonly}_gcc_cpp_32${FILE_EXT}
        COMMAND ${echo_var} ${echo_var2} ${mac_comment_32} ./build/${filenameonly}_gcc_cpp_ansi_32${FILE_EXT} ${skip_cpp_ansi}

        # cl
        COMMAND ${ms_cl_echo} ${echo_var} ./build/${filenameonly}_cl${FILE_EXT}
    )
    
    add_dependencies(cester_test ${filenameonly}__)
endforeach()

