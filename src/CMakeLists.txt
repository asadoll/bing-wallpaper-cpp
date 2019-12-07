
set(src
    main.cpp)

find_package(Boost REQUIRED)
add_executable(bing-wallpaper ${src})
set_target_properties(bing-wallpaper PROPERTIES CXX_STANDARD 17)
target_include_directories(bing-wallpaper PUBLIC
                                $<BUILD_INTERFACE:${BING_WALLPAPER_SOURCE_DIR}/include>
                                $<BUILD_INTERFACE:${BING_WALLPAPER_SOURCE_DIR}/external/curlpp/include>
                                $<BUILD_INTERFACE:${BING_WALLPAPER_SOURCE_DIR}/external/fmt/include>
                                $<BUILD_INTERFACE:${BING_WALLPAPER_SOURCE_DIR}/external/pugixml/src>
                                $<BUILD_INTERFACE:${Boost_INCLUDE_DIR}>
                                $<INSTALL_INTERFACE:${include_dest}>
                                $<INSTALL_INTERFACE:${include_dest}/comp>)
target_compile_definitions(bing-wallpaper PUBLIC
                                BING_WALLPAPER=1
                                BING_WALLPAPER_VERSION_MAJOR=${BING_WALLPAPER_VERSION_MAJOR}
                                BING_WALLPAPER_VERSION_MINOR=${BING_WALLPAPER_VERSION_MINOR})

# add threading support
find_package(Threads REQUIRED)
target_link_libraries(bing-wallpaper PUBLIC Threads::Threads)
target_link_libraries(bing-wallpaper PUBLIC ${Boost_LIBRARIES})
target_link_libraries(bing-wallpaper PUBLIC curlpp)
target_link_libraries(bing-wallpaper PUBLIC fmt)
target_link_libraries(bing-wallpaper PUBLIC pugixml)

# install library: TODO
#install(TARGETS bing-wallpaper EXPORT bing-wallpaper DESTINATION "${lib_dest}")
#install(FILES ${header} DESTINATION "${include_dest}/bing-wallpaper")
#install(FILES ${detail_header} DESTINATION "${include_dest}/bing-wallpaper/detail")
