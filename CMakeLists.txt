cmake_minimum_required(VERSION 3.21)
project(xpn)
enable_language(C CXX)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_EXTENSIONS ON)

set(CMAKE_VERBOSE_MAKEFILE ON)

# Packages
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Source files
# SUBDIRS = src/base   src/xpn_client   src/utils   src/bypass   src/mpi_server  src/sck_server  src/tcp_server

# Compiler flags
add_compile_options("-D_GNU_SOURCE") # Enable GNU extensions (e.g. off64_t)
add_compile_options("-D_POSIX_C_SOURCE=200809L") # Enable POSIX extensions
# "-D_LARGE_FILE_SOURCE=1" "-D_FILE_OFFSET_BITS=64")

#[[
    XPN Base
]]

file(GLOB _base_sources "src/base/*.c")
add_library(xpn_base OBJECT ${_base_sources})
target_include_directories(xpn_base PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/base"
)
target_link_libraries(xpn_base PUBLIC Threads::Threads)


#[[
    XPN Client
]]

# NFI Variants
option(ENABLE_XPN_CLIENT_SCK "Enable SCK support for XPN client" ON)

if (ENABLE_XPN_CLIENT_SCK)
  file(GLOB _xpn_client_sck_sources "src/xpn_client/nfi/nfi_sck_server/*.c")
  list(APPEND _xpn_client_nfi_extra_sources ${_xpn_client_sck_sources})
  list(APPEND _xpn_client_nfi_extra_includes "${PROJECT_SOURCE_DIR}/include/xpn_client/nfi/nfi_sck_server")
endif (ENABLE_XPN_CLIENT_SCK)

# NFI Sources
file(GLOB _xpn_client_nfi_sources_common "src/xpn_client/nfi/common/*.c")
file(GLOB _xpn_client_nfi_sources_local "src/xpn_client/nfi/nfi_local/*.c")

# XPN Core
file(GLOB _xpn_client_core "src/xpn_client/xpn/xpn_simple/xpncore/*.c")
file(GLOB _xpn_client_policy "src/xpn_client/xpn/xpn_simple/policy/*.c")
file(GLOB _xpn_client_ep "src/xpn_client/*.c")

# Main library
# AM_CFLAGS         = -DASYNC_CLOSE=1 -DFILESYSTEM_DLSYM=1

# Compile C files as C++
set_source_files_properties(
    ${_base_sources}
    ${_xpn_client_core}
    ${_xpn_client_policy}
    ${_xpn_client_ep}
    PROPERTIES LANGUAGE CXX
)

set_source_files_properties(
    ${_xpn_client_nfi_sources_common}
    ${_xpn_client_nfi_sources_local}
    ${_xpn_client_nfi_extra_sources}
    PROPERTIES LANGUAGE CXX
)

add_library(xpn_client SHARED
    ${_base_sources}
    ${_xpn_client_core}
    ${_xpn_client_policy}
    ${_xpn_client_ep}
    ${_xpn_client_nfi_sources_common}
    ${_xpn_client_nfi_sources_local}
    ${_xpn_client_nfi_extra_sources}
)
target_include_directories(xpn_client PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/base"
    "${PROJECT_SOURCE_DIR}/include/xpn_client"
    "${PROJECT_SOURCE_DIR}/include/xpn_client/nfi"
    "${PROJECT_SOURCE_DIR}/include/xpn_client/nfi/nfi_local"
    "${PROJECT_SOURCE_DIR}/include/xpn_client/xpn/xpn_simple"
    ${_xpn_client_nfi_extra_includes}
)
target_compile_options(xpn_client PRIVATE "-fpermissive")

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
target_link_libraries(xpn_sck_server PUBLIC xpn_base xpn_client)
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
target_link_libraries(xpn_mpi_server PRIVATE xpn_base xpn_client MPI::MPI_C)

#[[
    XPN Bypass
]]
add_subdirectory(src/bypass)



