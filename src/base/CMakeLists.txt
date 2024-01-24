set(_header_path "${PROJECT_SOURCE_DIR}/include/base")

set(_headers
  "${_header_path}/darray.h"
  "${_header_path}/debug_msg.h"
  "${_header_path}/dtable.h"
  "${_header_path}/filesystem.h"
  "${_header_path}/math_misc.h"
  "${_header_path}/ns.h"
  "${_header_path}/path_misc.h"
  "${_header_path}/string_misc.h"
  "${_header_path}/syscall_proxies.h"
  "${_header_path}/time_misc.h"
  "${_header_path}/trace_msg.h"
  "${_header_path}/trace_tags.h"
  "${_header_path}/urlstr.h"
  "${_header_path}/utils.h"
  "${_header_path}/workers.h"
  "${_header_path}/workers_common.h"
  "${_header_path}/workers_ondemand.h"
  "${_header_path}/workers_pool.h"

  "${PROJECT_SOURCE_DIR}/include/all_system.h"
)

set(_sources
  "darray.c"
  "debug_msg.c"
  "dtable.c"
  "filesystem.c"
  "math_misc.c"
  "ns.c"
  "path_misc.c"
  "string_misc.c"
  "syscall_proxies.c"
  "time_misc.c"
  "trace_msg.c"
  "urlstr.c"
  "utils.c"
  "workers.c"
  "workers_ondemand.c"
  "workers_pool.c"
)
enable_cpp(${_sources})

# TODO: Remove when files are fixed
if (XPN_ENABLE_CPP)
  set_source_files_properties(
      "syscall_proxies.c"
      COMPILE_FLAGS "-fpermissive"
  )
endif()

add_library(xpn_base OBJECT ${_sources} ${_headers})

target_include_directories(xpn_base PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "${PROJECT_SOURCE_DIR}/include/base"
)

add_library(XPN::Base ALIAS xpn_base)