cmake_minimum_required(VERSION 3.22)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(dle_internship LANGUAGES CXX C)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Rpass=inline -Winline -W4")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Winline /W4")
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /W4")
endif()
make_directory(${CMAKE_BINARY_DIR}/runtime_directory)

include("${CMAKE_CURRENT_SOURCE_DIR}/third_party/CMakeLists.txt")
include("${CMAKE_CURRENT_SOURCE_DIR}/engine/CMakeLists.txt")
include("${CMAKE_CURRENT_SOURCE_DIR}/d3d/CMakeLists.txt")
include("${CMAKE_CURRENT_SOURCE_DIR}/tests/CMakeLists.txt")
