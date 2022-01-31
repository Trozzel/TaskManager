cmake_minimum_required(VERSION 3.15)
project(GTD)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" )
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()

set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_STANDARD 17)

include_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/include
		/usr/local/include
)

# NECESSARY ON MAC
link_directories ( /usr/local/lib )

add_executable( gtd
	src/Context.cpp
        src/Folder.cpp
        src/Project.cpp
        src/main.cpp
        )

target_link_libraries( gtd
	dt )
