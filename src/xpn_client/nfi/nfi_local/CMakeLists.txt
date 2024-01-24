set(_header_path "${PROJECT_SOURCE_DIR}/include/xpn_client/nfi/nfi_local/")

set(_headers
    "${_header_path}/nfi_local.h"
    "${_header_path}/nfi_local_err.h"
)
set(_sources
    "nfi_local.c"
    "nfi_local_err.c"
)

add_library(xpn_client_nfi_local STATIC ${_sources} ${_headers})
# TODO: Make PRIVATE. Currently PUBLIC due to nfi_lib.h dependency in parent.
target_include_directories(xpn_client_nfi_local PUBLIC
    "${PROJECT_SOURCE_DIR}/include/xpn_client/nfi/nfi_local"
)
# TODO: Make PRIVATE. Currently PUBLIC due to xpncore dependency in nfi_lib.h
target_link_libraries(xpn_client_nfi_local PUBLIC
  XPN::Client::NFI::Common
)
target_link_libraries(xpn_client_nfi_local PRIVATE
  XPN::Base
)
#add_library(xpn_client_nfi_local OBJECT ${_xpn_client_nfi_local_sources} ${_xpn_client_nfi_local_headers})
#target_include_directories(xpn_client_nfi_local PUBLIC # Private?
#    "${PROJECT_SOURCE_DIR}/include/xpn_client/nfi/nfi_local"
#)
#target_link_libraries(xpn_client_nfi_local PUBLIC # Private?
#    XPN::Base
#    XPN::Client::NFI::Common
#)
add_library(XPN::Client::NFI::Local ALIAS xpn_client_nfi_local)
