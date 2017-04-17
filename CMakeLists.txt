cmake_minimum_required(VERSION 3.1 FATAL_ERROR)

project(aldente)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

# Helpers
macro (create_test target)
  add_test (NAME ${target} COMMAND $<TARGET_FILE:${target}>)
endmacro (create_test)

# Define folders
set(EXT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIB_DIR ${CMAKE_CURRENT_BINARY_DIR}/lib)

# Compiler settings
set(CMAKE_CXX_STANDARD 11)
set(warnings "-Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")

# Output
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIB_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
set(CMAKE_LEGACY_CYGWIN_WIN32 0)

# Dependencies
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/modules/)

# Catch
find_package(Catch REQUIRED)
include_directories(${Catch_INCLUDE_DIRS})

# Boost
find_package(Boost COMPONENTS system thread regex REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

# Libraries
set(LIBS
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  ${Boost_REGEX_LIBRARY})

# Binaries
file(GLOB_RECURSE SOURCES ${SRC_DIR}/*.cpp)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})

# Tests
enable_testing()
file(GLOB_RECURSE TEST_SOURCES ${TEST_DIR}/*.cpp)
add_executable(run_tests ${TEST_SOURCES})
target_link_libraries(run_tests ${LIBS})
add_dependencies(run_tests catch)
create_test(run_tests)
