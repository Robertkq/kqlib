# This file handles building each task as sub-project.
#
# Each task becomes an independent project in which you can experiment.
#
# Tasks are added as separate sub-projects so as compilation errors in
# one task don't affect another task.


cmake_minimum_required(VERSION 3.12)

project(kqlib)

set(CMAKE_CXX_STANDARD 11)

set(MAIN_SOURCES
        include/main.cpp
        )
		
set(TEST_SOURCES
		kqlib.test/test.cpp
		)

add_executable(kqlib_main ${MAIN_SOURCES})
add_executable(kqlib_test ${TEST_SOURCES})