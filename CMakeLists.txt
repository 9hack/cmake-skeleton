cmake_minimum_required(VERSION 2.4 FATAL_ERROR)

project(aldente)
set(VERSION_MAJOR 0)
set(VERSION_MINOR 0)
set(VERSION_PATCH 1)

# Define folders
set(EXT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ext)
set(INC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)
set(BIN_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)

# Make warnings into errors
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU" OR
    "${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    set(warnings "-Wall -Wextra -Werror")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    set(warnings "/W4 /WX /EHsc")
endif()
set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${warnings}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${warnings}")

# Output
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

# Project
set(PROJECT_LIBRARY ${CMAKE_PROJECT_NAME}-src)
file(GLOB SOURCES ${SRC_DIR}/*.cpp)
add_library(${PROJECT_LIBRARY} ${SOURCES})
include_directories(${INC_DIR})

# Libraries
set(LIBS
  ${PROJECT_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  ${Boost_REGEX_LIBRARY})

# Binaries
add_executable(${CMAKE_PROJECT_NAME} main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME} ${LIBS})

# Tests
enable_testing()
file(GLOB TEST_SOURCES ${TEST_DIR}/*.cpp)
add_executable(test_main ${TEST_SOURCES})
target_link_libraries(test_main ${Catch_LIBRARY} ${LIBS})
add_test(all_tests test_main)
