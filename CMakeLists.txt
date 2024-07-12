cmake_minimum_required(VERSION 3.6)
project(thall_client_server_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER mpicxx)

if(NOT DEFINED FUSE3_INCLUDE)
    message(FATAL_ERROR "Required variable FUSE3_INCLUDE is not defined. Please set -DFUSE3_INCLUDE=<path> when invoking CMake.")
endif()

if(NOT DEFINED FUSE3_LIB)
    message(FATAL_ERROR "Required variable FUSE3_LIB is not defined. Please set -DFUSE3_LIB=<path> when invoking CMake.")
endif()

link_directories(${FUSE3_LIB})

find_package(PkgConfig REQUIRED)

pkg_check_modules (MARGO REQUIRED IMPORTED_TARGET margo)
pkg_check_modules (THALLIUM REQUIRED IMPORTED_TARGET thallium)

include_directories(${MARGO_INCLUDE_DIRS})
include_directories(${THALLIUM_INCLUDE_DIRS})


add_executable(server src/server.cpp src/cu_stat.cpp)
add_executable(client src/client.cpp src/cu_stat.cpp)

# Link necessary libraries
target_include_directories(server PRIVATE "${FUSE3_INCLUDE}")
target_link_libraries(server PRIVATE PkgConfig::MARGO PkgConfig::THALLIUM fuse3)
target_link_libraries(client PRIVATE PkgConfig::MARGO PkgConfig::THALLIUM)
