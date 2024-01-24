# TODO: Remove globbing and add files manually
file(GLOB _xpn_base_headers "${PROJECT_SOURCE_DIR}/include/base/*.h")
file(GLOB _xpn_base_sources "*.c")

# Compile C files as C++
set_source_files_properties(${_xpn_base_sources}
    PROPERTIES
    LANGUAGE CXX
)

# TODO: Remove this flag
# There is a void * to char * conversion in syscall_proxies.c
set_source_files_properties(
    syscall_proxies.c
    COMPILE_FLAGS "-fpermissive"
)

#[[
  Target: XPN::base
]]

add_library(xpn_base OBJECT
  ${_xpn_base_headers}
  ${_xpn_base_sources}
)
target_include_directories(xpn_base PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/base"
)
add_library(XPN::Base ALIAS xpn_base)