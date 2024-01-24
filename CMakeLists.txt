cmake_minimum_required(VERSION 3.21)
project(XPN VERSION 0.1.0 LANGUAGES C CXX)

# CMake Modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

# Language Options
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_VERBOSE_MAKEFILE ON)


#[[
  XPN - Global Options
]]

# Compile XPN as C++
include(enable_cpp)
option(XPN_ENABLE_CPP "Compile XPN as C++" ON)

# Enable SCK support for NFI
option(XPN_ENABLE_NFI_SCK "Enable SCK NFI support" ON)
if (XPN_ENABLE_NFI_SCK)
  add_compile_definitions(ENABLE_SCK_SERVER) # nfi_lib.h xpn_policy_init.c
endif (XPN_ENABLE_NFI_SCK)

# Build XPN as shared library
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
if (BUILD_SHARED_LIBS)
  set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif (BUILD_SHARED_LIBS)


#[[
  XPN - Global Options
  TODO: Remove once they're isolated to individual targets
]]
# "-D_LARGE_FILE_SOURCE=1" "-D_FILE_OFFSET_BITS=64")
add_compile_options("-D_GNU_SOURCE") # Enable GNU extensions (e.g. off64_t)
add_compile_options("-D_POSIX_C_SOURCE=200809L") # Enable POSIX extensions


#[[
  XPN - Sources
]]

# XPN
add_subdirectory(src/base)
add_subdirectory(src/xpn_client)
add_subdirectory(src/mpi_server)
add_subdirectory(src/sck_server)

# XPN Bypass
add_subdirectory(src/bypass)



