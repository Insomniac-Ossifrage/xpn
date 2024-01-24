#[[
  Compile directives in Makefile:
  AM_CFLAGS = -DASYNC_CLOSE=1 -DFILESYSTEM_DLSYM=1
]]

add_subdirectory(nfi)
add_subdirectory(xpn/xpn_simple/policy)
add_subdirectory(xpn/xpn_simple/xpncore)

set(_headers
  "${PROJECT_SOURCE_DIR}/include/xpn_client/xpn.h"
  "${PROJECT_SOURCE_DIR}/include/xpn_client/xpn/xpn_simple/xpn_simple_lib.h"
)

set(_sources
  "xpn_stdio.c"
  "xpn_unistd.c"
)

add_library(xpn_client STATIC ${_sources} ${_headers})
target_link_libraries(xpn_client PRIVATE XPN::Base XPN::Client::Core XPN::Client::Policy XPN::Client::NFI::Local)
target_compile_options(xpn_client PRIVATE "-fpermissive")

