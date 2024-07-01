cmake_minimum_required(VERSION 3.10)

project(GStreamerExample)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

pkg_check_modules(GST_PLUGINS REQUIRED
    gstreamer-plugins-base-1.0
    gstreamer-plugins-good-1.0
    gstreamer-plugins-bad-1.0
)

MESSAGE("GST_INCLUDE_DIRS ${GST_INCLUDE_DIRS}")
MESSAGE("GST_LIBRARIES ${GST_LIBRARIES}")
MESSAGE("GST_CFLAGS_OTHER ${GST_CFLAGS_OTHER}")
add_executable(main ./src/main.cpp)
# target_include_directories(main PRIVATE ${GST_INCLUDE_DIRS} ${GST_PLUGINS_INCLUDE_DIRS})
# target_link_libraries(main PRIVATE ${GST_LIBRARIES} ${GST_PLUGINS_LIBRARIES})

target_include_directories(main PRIVATE ${GST_INCLUDE_DIRS}  ${GSTREAMER_INCLUDE_DIRS} ${GST_BASE_INCLUDE_DIRS} ${GST_GOOD_INCLUDE_DIRS} ${GST_BAD_INCLUDE_DIRS})
target_link_libraries(main ${GST_LIBRARIES} ${GSTREAMER_LIBRARIES} ${GST_BASE_LIBRARIES} ${GST_GOOD_LIBRARIES} ${GST_BAD_LIBRARIES})

target_compile_options(main PRIVATE ${GST_CFLAGS_OTHER})

