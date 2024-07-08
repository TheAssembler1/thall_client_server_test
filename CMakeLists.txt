cmake_minimum_required(VERSION 3.6)
project(thall_client_server_test)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_COMPILER mpicxx)

find_package(PkgConfig REQUIRED)

pkg_check_modules (MARGO REQUIRED IMPORTED_TARGET margo)
pkg_check_modules (THALLIUM REQUIRED IMPORTED_TARGET thallium)

include_directories(${MARGO_INCLUDE_DIRS})
include_directories(${THALLIUM_INCLUDE_DIRS})


add_executable(server src/server.cpp)
add_executable(client src/client.cpp)

# Link necessary libraries
target_link_libraries(server PRIVATE PkgConfig::MARGO PkgConfig::THALLIUM)
target_link_libraries(client PRIVATE PkgConfig::MARGO PkgConfig::THALLIUM)
