cmake_minimum_required (VERSION 2.8)
project(gtk)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
add_definitions(${GTK3_CFLAGS_OTHER})


include_directories(${CMAKE_SOURCE_DIR})


include_directories(include)
add_executable (demo resources/demo.c)
target_link_libraries(demo ${GTK3_LIBRARIES})

include_directories(include)
add_executable (demo1 resources/demo1.c)
target_link_libraries(demo1 ${GTK3_LIBRARIES})

include_directories(include)
add_executable (demo2 resources/demo2.c)
target_link_libraries(demo2 ${GTK3_LIBRARIES})
