set(_header_path "${PROJECT_SOURCE_DIR}/include/xpn_client/xpn/xpn_simple")

set(_headers
    "${_header_path}/xpn_cwd.h"
    "${_header_path}/xpn_dir.h"
    "${_header_path}/xpn_err.h"
    "${_header_path}/xpn_file.h"
    "${_header_path}/xpn_init.h"
    "${_header_path}/xpn_open.h"
    "${_header_path}/xpn_opendir.h"
    "${_header_path}/xpn_rw.h"
    "${_header_path}/xpn_stdio.h"
    "${_header_path}/xpn.h"
)

set(_sources
    "xpn_cwd.c"
    "xpn_dir.c"
    "xpn_err.c"
    "xpn_file.c"
    "xpn_init.c"
    "xpn_open.c"
    "xpn_opendir.c"
    "xpn_rw.c"
    "xpn_stdio.c"
)
enable_cpp(${_sources})

# TODO: Remove when xpn_stdio.c is fixed
if (XPN_ENABLE_CPP)
  set_source_files_properties(
      xpn_stdio.c
      COMPILE_FLAGS "-fpermissive"
  )
endif()

add_library(xpn_client_core INTERFACE)
target_sources(xpn_client_core INTERFACE ${_sources} ${_headers})

target_include_directories(xpn_client_core INTERFACE
    "${PROJECT_SOURCE_DIR}/include/xpn_client"
    "${PROJECT_SOURCE_DIR}/include/xpn_client/xpn/xpn_simple"
)
target_link_libraries(xpn_client_core INTERFACE
    XPN::Base # all_systems.h
    XPN::Client::NFI::Local # nfi.h depends on nfi_local.h
)

add_library(XPN::Client::Core ALIAS xpn_client_core)