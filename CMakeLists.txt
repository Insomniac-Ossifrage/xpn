cmake_minimum_required(VERSION 3.21)
project(xpn)
enable_language(C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(enable_cpp)
option(XPN_ENABLE_CPP "Compile XPN as C++" ON)

# Packages
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)


# Compiler flags
add_compile_options("-D_GNU_SOURCE") # Enable GNU extensions (e.g. off64_t)
add_compile_options("-D_POSIX_C_SOURCE=200809L") # Enable POSIX extensions
# "-D_LARGE_FILE_SOURCE=1" "-D_FILE_OFFSET_BITS=64")


#[[
    Sources
]]
add_subdirectory(src/base)
add_subdirectory(src/xpn_client)

#[[
    XPN SCK Server
]]
file(GLOB _xpn_sck_server_sources "src/sck_server/*.c")
add_executable(xpn_sck_server ${_xpn_sck_server_sources})
target_include_directories(xpn_sck_server PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/base"
    "${PROJECT_SOURCE_DIR}/include/sck_server"
    "${PROJECT_SOURCE_DIR}/include/xpn_client"
)
target_link_libraries(xpn_sck_server PUBLIC XPN::Base xpn_client)
target_compile_options(xpn_sck_server PRIVATE "-D_REENTRANT" "-DPOSIX_THREADS" "-D_GNU_SOURCE" "-DHAVE_STRUCT_IOVEC")

#[[
    XPN MPI Server
]]
find_package(MPI REQUIRED)

file(GLOB _xpn_mpi_server_sources "src/mpi_server/*.c")
add_executable(xpn_mpi_server ${_xpn_mpi_server_sources})
target_include_directories(xpn_mpi_server PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/base"
    "${PROJECT_SOURCE_DIR}/include/mpi_server"
    "${PROJECT_SOURCE_DIR}/include/xpn_client"
)
target_link_libraries(xpn_mpi_server PRIVATE XPN::Base xpn_client MPI::MPI_C)

#[[
    XPN Bypass
]]
add_subdirectory(src/bypass)



