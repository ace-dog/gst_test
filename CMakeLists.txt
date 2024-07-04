cmake_minimum_required(VERSION 3.10)

project(GStreamerExample)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 gstreamer-app-1.0)

pkg_check_modules(GST_PLUGINS REQUIRED
    gstreamer-plugins-base-1.0
    gstreamer-plugins-good-1.0
    gstreamer-plugins-bad-1.0
)

macro(create_exe project)
    add_executable(${project} ./src/${project}.cpp)
    target_include_directories(${project} PRIVATE ${GST_INCLUDE_DIRS}  ${GSTREAMER_INCLUDE_DIRS} ${GST_BASE_INCLUDE_DIRS} ${GST_GOOD_INCLUDE_DIRS} ${GST_BAD_INCLUDE_DIRS})
    target_link_libraries(${project} ${GST_LIBRARIES} ${GSTREAMER_LIBRARIES} ${GST_BASE_LIBRARIES} ${GST_GOOD_LIBRARIES} ${GST_BAD_LIBRARIES})
    target_compile_options(${project} PRIVATE ${GST_CFLAGS_OTHER})
endmacro()

set(APP_LIST 
    "dkt_to_srt" 
    "dkt_to_mpegts_appsink"
)

foreach(ITEM IN LISTS APP_LIST)
    create_exe(${ITEM})
endforeach()

