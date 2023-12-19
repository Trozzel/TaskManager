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

# C++ Sqlite Library
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/SQLiteCpp)
find_package(SQLite3)

include_directories(
		${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/src/SQLiteCpp/include/
		/usr/local/include
		${SQLite3_INCLUDE_DIRS})

# NECESSARY ON MAC
link_directories ( /usr/local/lib ${CMAKE_CURRENT_SOURCE_DIR}/src/SQLiteCpp )

find_package(fmt)

# AUTO ADD DEFINITIONS TO CODE BASED UPON BUILD TYPE
IF(CMAKE_BUILD_TYPE STREQUAL "Release")
	ADD_COMPILE_DEFINITIONS(RUNMODE="prod")
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "Debug")
	ADD_COMPILE_DEFINITIONS(RUNMODE="dev")
ENDIF()

add_executable ( sqlplay
    src/sql_play.cpp
    src/Context.cpp
    src/Task.cpp
    src/Folder.cpp
    src/GtdHelper.cpp
    src/Project.cpp
    )
	
target_link_libraries ( sqlplay
    ${SQLite3_LIBRARIES}
	sqlite3
    fmt::fmt
    SqliteCpp
    pthread
    dl)

add_executable ( temp
	src/GtdHelper.cpp
	src/GtdBase.cpp
	src/UpdateStack.cpp
    src/Completable.cpp
	src/ImplHelpers.cpp
	src/Context.cpp
	src/Task.cpp
	src/Project.cpp
	src/Folder.cpp
    src/UpdateStack.cpp
    src/GtdBaseContainer.cpp
    src/CompleteableContainer.cpp
    src/ContextContainer.cpp
    src/FolderContainer.cpp
	temp.cpp)

target_link_libraries ( temp
	${SQLite3_LIBRARIES}
	sqlite3
	fmt::fmt
	SqliteCpp
	pthread
	dl)

IF( EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json" ) 
  EXECUTE_PROCESS( COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
    ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
  )
ENDIF()

