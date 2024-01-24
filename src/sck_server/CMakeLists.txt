set(_header_path "${PROJECT_SOURCE_DIR}/include/sck_server")

set(_headers
    "${_header_path}/sck_server_comm.h"
    "${_header_path}/sck_server_conf.h" # Included by sck_server_params
    "${_header_path}/sck_server_d2xpn.h"
    "${_header_path}/sck_server_ops.h"
    "${_header_path}/sck_server_params.h"
)

set(_sources
  "sck_server.c"
  "sck_server_comm.c"
  "sck_server_d2xpn.c"
  "sck_server_ops.c"
  "sck_server_params.c"
)
enable_cpp(${_sources})

# TODO: Remove when files are fixed
if (XPN_ENABLE_CPP)
  set_source_files_properties(
      "sck_server.c"
      "sck_server_ops.c"
      COMPILE_FLAGS "-fpermissive"
  )
endif()

add_executable(xpn_sck_server ${_sources} ${_headers})
target_include_directories(xpn_sck_server PRIVATE
    "${PROJECT_SOURCE_DIR}/include/sck_server"

)
target_link_libraries(xpn_sck_server PRIVATE
    XPN::Base
    XPN::Client # Dependency from xpn.h (e.g. xpn_init)
)

#target_compile_options(xpn_sck_server PRIVATE "-D_REENTRANT" "-DPOSIX_THREADS" "-D_GNU_SOURCE" "-DHAVE_STRUCT_IOVEC")