project(Make_data_file
	LANGUAGES C)
cmake_minimum_required(VERSION 2.8)

add_subdirectory(cmake-btree)

add_executable(btCreateFromTxt btCreateFromTxt.c)
target_link_libraries(btCreateFromTxt bt)
