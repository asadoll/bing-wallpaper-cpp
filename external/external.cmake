
#
# add curlpp
#
message(STATUS "Installing curlpp via submodule")
execute_process(COMMAND git submodule update --init -- external/curlpp
                WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(external/curlpp)

#
# add fmt
#
message(STATUS "Installing fmt via submodule")
execute_process(COMMAND git submodule update --init -- external/fmt
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(external/fmt)

#
# add pugixml
#
message(STATUS "Installing pugixml via submodule")
execute_process(COMMAND git submodule update --init -- external/pugixml
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
add_subdirectory(external/pugixml)
