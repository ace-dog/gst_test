cmake_minimum_required(VERSION 3.10)

project(GStreamerExample)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0 gstreamer-app-1.0)

pkg_check_modules(GST_PLUGINS REQUIRED
    gstreamer-plugins-base-1.0
    gstreamer-plugins-good-1.0
    gstreamer-plugins-bad-1.0
)

MESSAGE("GST_INCLUDE_DIRS ${GST_INCLUDE_DIRS}")
MESSAGE("GST_LIBRARIES ${GST_LIBRARIES}")
MESSAGE("GST_CFLAGS_OTHER ${GST_CFLAGS_OTHER}")

SET(APP_NAME dkt_to_srt)
add_executable(${APP_NAME} ./src/${APP_NAME}.cpp)
target_include_directories(${APP_NAME} PRIVATE ${GST_INCLUDE_DIRS}  ${GSTREAMER_INCLUDE_DIRS} ${GST_BASE_INCLUDE_DIRS} ${GST_GOOD_INCLUDE_DIRS} ${GST_BAD_INCLUDE_DIRS})
target_link_libraries(${APP_NAME} ${GST_LIBRARIES} ${GSTREAMER_LIBRARIES} ${GST_BASE_LIBRARIES} ${GST_GOOD_LIBRARIES} ${GST_BAD_LIBRARIES})
target_compile_options(${APP_NAME} PRIVATE ${GST_CFLAGS_OTHER})


SET(APP_NAME dkt_to_appsink)
add_executable(${APP_NAME} ./src/${APP_NAME}.cpp)
target_include_directories(${APP_NAME} PRIVATE ${GST_INCLUDE_DIRS}  ${GSTREAMER_INCLUDE_DIRS} ${GST_BASE_INCLUDE_DIRS} ${GST_GOOD_INCLUDE_DIRS} ${GST_BAD_INCLUDE_DIRS})
target_link_libraries(${APP_NAME} ${GST_LIBRARIES} ${GSTREAMER_LIBRARIES} ${GST_BASE_LIBRARIES} ${GST_GOOD_LIBRARIES} ${GST_BAD_LIBRARIES})
target_compile_options(${APP_NAME} PRIVATE ${GST_CFLAGS_OTHER})