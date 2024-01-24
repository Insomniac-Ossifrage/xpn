add_subdirectory(common)
add_subdirectory(nfi_local)

#[[
  NFI Interface Library
]]

add_library(nfi INTERFACE)
target_sources(nfi INTERFACE
  $<TARGET_OBJECTS:XPN::Client::NFI::Common>
  $<TARGET_OBJECTS:XPN::Client::NFI::Local>
)
# Inject dependencies
target_link_libraries(nfi INTERFACE
  XPN::Client::NFI::Common
  XPN::Client::NFI::Local
)

add_library(XPN::Client::NFI ALIAS nfi)