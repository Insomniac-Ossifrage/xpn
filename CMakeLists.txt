cmake_minimum_required(VERSION 3.21)
project(xpn)

# Language Options
enable_language(C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_VERBOSE_MAKEFILE ON)


# CMake Modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(enable_cpp)
option(XPN_ENABLE_CPP "Compile XPN as C++" ON)



# Compiler flags
# "-D_LARGE_FILE_SOURCE=1" "-D_FILE_OFFSET_BITS=64")
add_compile_options("-D_GNU_SOURCE") # Enable GNU extensions (e.g. off64_t)
add_compile_options("-D_POSIX_C_SOURCE=200809L") # Enable POSIX extensions



# XPN
add_subdirectory(src/base)
add_subdirectory(src/xpn_client)
add_subdirectory(src/mpi_server)
add_subdirectory(src/sck_server)

# XPN Bypass
add_subdirectory(src/bypass)



