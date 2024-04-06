cmake_minimum_required(VERSION 3.20)
project(socket_programming
        DESCRIPTION "Socket programming experiments (Windows/Linux)"
        HOMEPAGE_URL "https://github.com/wilricknl/socket_programming"
        LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

## Interpret source as utf-8 on Windows to ensure
## non-ascii characters are read properly.
add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

## Static builds on Windows
if (MSVC)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif ()

# -----------------------------------------------------------------------------
# LECTURE 01
# -----------------------------------------------------------------------------

if (NOT WIN32)
    add_executable(
            01_hello_server
            lecture01/hello_server.c)

    add_executable(
            01_hello_client
            lecture01/hello_client.c)
endif ()

# -----------------------------------------------------------------------------
# LECTURE 02
# -----------------------------------------------------------------------------

add_executable(
    02_server
    lecture02/server.cpp)

add_executable(
    02_client
    lecture02/client.cpp)
