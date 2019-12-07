
cmake_minimum_required(VERSION 3.5)
project(BING_WALLPAPER VERSION 0.1.0)

option(BING_WALLPAPER_BUILD_TEST "whether or not to build the test" ON)

set(lib_dest "lib/bing-wallpaper")
set(include_dest "include")
set(tool_dest "bin")

# add external libraries
include(external/external.cmake)

if (MSVC)
    add_compile_options(
        # Disable warnings
        -D_CRT_SECURE_NO_WARNINGS
        -D_SCL_SECURE_NO_WARNINGS
        /wd4503 # decorated name length exceeded, name was truncated
        /MP # Multi-processor compilation
        )
endif()

# subdirectories
add_subdirectory(src)
if (BING_WALLPAPER_BUILD_TEST)
    add_subdirectory(test)
endif()

# install configuration
#install(EXPORT bing-wallpaper DESTINATION "${lib_dest}")
#install(FILES bing-wallpaper-config.cmake LICENSE DESTINATION "${lib_dest}")
