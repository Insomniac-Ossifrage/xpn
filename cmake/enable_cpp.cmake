function(enable_cpp)
  if(XPN_ENABLE_CPP)
    # Directory is needed to propagate the language to the parent scope
    set_source_files_properties(${ARGN} PROPERTIES LANGUAGE CXX DIRECTORY ${PROJECT_SOURCE_DIR})
  endif()
endfunction()