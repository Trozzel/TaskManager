cmake_minimum_required(VERSION 3.15)
project(GTD)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

find_package(SQLite3)

include_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/include
		/usr/local/include
		${SQLite3_INCLUDE_DIRS}
)
# NECESSARY ON MAC
link_directories ( /usr/local/lib )

find_package(fmt)

add_executable ( sqlplay
	src/sql_play.cpp
	src/Context.cpp
	src/Folder.cpp
	src/Status.cpp
	)
	
target_link_libraries ( sqlplay
	${SQLite3_LIBRARIES}
	fmt::fmt
	)
