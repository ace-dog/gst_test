cmake_minimum_required(VERSION 3.10)

project(GStreamerExample)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GSTREAMER REQUIRED gstreamer-1.0)

add_executable(main ./src/main.cpp)
target_include_directories(main PRIVATE ${GST_INCLUDE_DIRS})
target_link_libraries(main PRIVATE ${GST_LIBRARIES})
target_compile_options(main PRIVATE ${GST_CFLAGS_OTHER})

