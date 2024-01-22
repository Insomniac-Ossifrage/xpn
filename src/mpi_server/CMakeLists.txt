set(_header_path "${PROJECT_SOURCE_DIR}/include/mpi_server")

set(_headers
    "${_header_path}/mpi_server_comm.h"
    "${_header_path}/mpi_server_conf.h"
    "${_header_path}/mpi_server_d2xpn.h"
    "${_header_path}/mpi_server_ops.h"
    "${_header_path}/mpi_server_params.h"
)

set(_sources
  "mpi_server.c"
  "mpi_server_comm.c"
  "mpi_server_d2xpn.c"
  "mpi_server_ops.c"
  "mpi_server_params.c"
)
enable_cpp(${_sources})

# TODO: Remove when files are fixed
if (XPN_ENABLE_CPP)
  set_source_files_properties(
      "mpi_server.c"
      "mpi_server_ops.c"
      COMPILE_FLAGS "-fpermissive"
  )
endif()

find_package(MPI REQUIRED)

add_executable(xpn_mpi_server ${_sources} ${_headers})

target_include_directories(xpn_mpi_server PRIVATE
  "${PROJECT_SOURCE_DIR}/include/mpi_server"
)
target_link_libraries(xpn_mpi_server PRIVATE XPN::Base XPN::Client)


# Link against proper MPI library
if (XPN_ENABLE_CPP)
  target_link_libraries(xpn_mpi_server PRIVATE MPI::MPI_CXX)
else()
  target_link_libraries(xpn_mpi_server PRIVATE MPI::MPI_C)
endif()