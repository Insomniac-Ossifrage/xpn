set(_header_path "${PROJECT_SOURCE_DIR}/include/xpn_client/nfi")

set(_headers
    "${_header_path}/nfi_ops.h"
    "${_header_path}/nfi_worker.h"
    "${_header_path}/nfi_worker_task.h"
)
set(_sources
    "nfi_ops.c"
    "nfi_worker.c"
)
enable_cpp(${_sources})

add_library(xpn_client_nfi_common OBJECT ${_sources} ${_headers})
target_include_directories(xpn_client_nfi_common PUBLIC
    "${PROJECT_SOURCE_DIR}/include/xpn_client"
    "${PROJECT_SOURCE_DIR}/include/xpn_client/nfi"
)
target_link_libraries(xpn_client_nfi_common PRIVATE XPN::Base)

add_library(XPN::Client::NFI::Common ALIAS xpn_client_nfi_common)