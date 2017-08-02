cmake_minimum_required(VERSION 3.5.1)
project(OStor)

add_compile_options(-std=c++11)

SET(
	SOURCES
	src/process.cpp
	src/shell_process.cpp
	src/file_process.cpp
	src/compiler.cpp
	src/value.cpp
	src/expression.cpp
)

SET(
	TEST_SOURCES
	tests/compiler/compiler_test.cpp
	tests/expression/expression_test.cpp
	tests/process/process_test.cpp
)

# - - - - - - - [ Add tests
#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})
#add_executable(run_tests tests/run_tests.cpp ${SOURCES} ${TEST_SOURCES})
#target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread)

# - - - - - - - [ Generate executable
add_executable(ostor src/main.cpp ${SOURCES})
