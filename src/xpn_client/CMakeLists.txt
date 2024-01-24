#[[
  Compile directives in Makefile:
  AM_CFLAGS = -DASYNC_CLOSE=1 -DFILESYSTEM_DLSYM=1
]]

add_subdirectory(nfi)
# Interface library
add_subdirectory(xpn/xpn_simple/policy)
add_subdirectory(xpn/xpn_simple/xpncore)

set(_header_path "${PROJECT_SOURCE_DIR}/include/xpn_client/")

set(_headers
  "${_header_path}/nfi/nfi.h"     # Included by nfi_lib.h
  "${_header_path}/nfi/nfi_lib.h" # Included by xpn_simple/xpn.h
  "${_header_path}/xpn.h"
  "${_header_path}/xpn/xpn_simple/xpn_simple_lib.h"
)

set(_sources
  "xpn_stdio.c"
  "xpn_unistd.c"
)
enable_cpp(${_sources})

add_library(xpn_client ${_sources} ${_headers})

target_include_directories(xpn_client PUBLIC "${PROJECT_SOURCE_DIR}/include/xpn_client")
target_link_libraries(xpn_client PRIVATE XPN::Base XPN::Client::Core XPN::Client::Policy XPN::Client::NFI)

add_library(XPN::Client ALIAS xpn_client)
