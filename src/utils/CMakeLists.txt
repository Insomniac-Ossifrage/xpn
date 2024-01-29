list(APPEND CMAKE_MESSAGE_INDENT "[XPN Utils] ")

find_package(MPI REQUIRED)


file(GLOB _utils "*.c")
foreach (_util ${_utils})
	# Get executable name
	get_filename_component(_name ${_util} NAME_WE)
	message(STATUS "Creating executable: ${_name}")

	enable_cpp(${_name})
	add_executable(${_name} ${_util})
	target_link_libraries(${_name} XPN::Base XPN::Client)

	if (XPN_ENABLE_CPP)
		target_link_libraries(${_name} MPI::MPI_CXX)
	else ()
		target_link_libraries(${_name} MPI::MPI_C)
	endif ()
endforeach ()

# TODO: Remove when files are fixed
if (XPN_ENABLE_CPP)
	set_source_files_properties(
			"xpncp.c"
			"xpncp_m.c"
			"xpncp_th.c"
			COMPILE_FLAGS "-fpermissive"
	)
endif()