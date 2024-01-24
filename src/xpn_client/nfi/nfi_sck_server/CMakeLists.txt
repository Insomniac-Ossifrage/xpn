set(_header_path "${PROJECT_SOURCE_DIR}/include/xpn_client/nfi/nfi_sck_server")

set(_headers
  "${_header_path}/nfi_sck_server.h"
  "${_header_path}/nfi_sck_server_err.h"
  "${_header_path}/sck_server_comm.h"
  "${_header_path}/sck_server_conf.h"
  "${_header_path}/sck_server_ops.h"
  "${_header_path}/sck_server_params.h"
)
set(_sources
  "nfi_sck_server.c"
  "nfi_sck_server_err.c"
  "sck_server_comm.c"
)
enable_cpp(${_sources})

add_library(xpn_client_nfi_sck OBJECT ${_sources} ${_headers})

target_include_directories(xpn_client_nfi_sck PUBLIC
    "${PROJECT_SOURCE_DIR}/include/xpn_client/nfi/nfi_sck_server"
)

target_link_libraries(xpn_client_nfi_sck PRIVATE
    XPN::Base
    XPN::Client::NFI::Common
)

add_library(XPN::Client::NFI::SCK ALIAS xpn_client_nfi_sck)
