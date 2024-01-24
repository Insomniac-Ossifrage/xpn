set(_header_path "${PROJECT_SOURCE_DIR}/include/xpn_client/xpn/xpn_simple")

set(_headers
  "${_header_path}/xpn_policy_cwd.h"
  "${_header_path}/xpn_policy_init.h"
  "${_header_path}/xpn_policy_open.h"
  "${_header_path}/xpn_policy_opendir.h"
  "${_header_path}/xpn_policy_rw.h"
)

set(_sources
  "xpn_policy_cwd.c"
  "xpn_policy_init.c"
  "xpn_policy_open.c"
  "xpn_policy_opendir.c"
  "xpn_policy_rw.c"
)


add_library(xpn_client_policy STATIC ${_sources} ${_headers})
target_include_directories(xpn_client_policy PRIVATE
    "${PROJECT_SOURCE_DIR}/include/xpn_client"
)
target_link_libraries(xpn_client_policy PRIVATE
    XPN::Base # all_systems.h
    XPN::Client::NFI::Local # nfi.h depends on nfi_local.h
)

add_library(XPN::Client::Policy ALIAS xpn_client_policy)