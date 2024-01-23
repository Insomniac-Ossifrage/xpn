#[[
    POSIX feature test macros
    https://linux.die.net/man/7/feature_test_macros

    _XOPEN_SOURCE
    Since glibc 2.10) The value 700 or greater additionally exposes definitions for SUSv4
    (i.e., the POSIX.1-2008 base specification plus the XSI extension).
#]]

find_package(MPI REQUIRED)

add_compile_options("-DNOT_TO_USE_FCNTL_H" "-DNOT_TO_USE_STDLIB_H")

add_library(xpn_bypass SHARED xpn_bypass.c)

target_include_directories(xpn_bypass PRIVATE
        "${PROJECT_SOURCE_DIR}/include"
        "${PROJECT_SOURCE_DIR}/include/bypass"
        "${PROJECT_SOURCE_DIR}/include/xpn_client"
)

target_include_directories(xpn_bypass PRIVATE "${PROJECT_SOURCE_DIR}/include/base") # Side effect of including debug_message.h
target_include_directories(xpn_bypass PRIVATE "${MPI_C_HEADER_DIR}") # Side effect of including mpi.h

target_compile_options(xpn_bypass PRIVATE -Wall -Wextra)