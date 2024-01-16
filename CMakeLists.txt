cmake_minimum_required(VERSION 3.15)
project(GTD)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )
ENDIF ()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# C++ Sqlite Library
find_package(SQLite3)
find_package(SQLiteCpp REQUIRED)
find_package(fmt REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# AUTO ADD DEFINITIONS TO CODE BASED UPON BUILD TYPE
IF (CMAKE_BUILD_TYPE STREQUAL "Release")
    ADD_COMPILE_DEFINITIONS(RUNMODE="prod")
ELSEIF (CMAKE_BUILD_TYPE STREQUAL "Debug")
    ADD_COMPILE_DEFINITIONS(RUNMODE="dev")
ENDIF ()

add_executable(runtime
        src/GtdBase.cpp
        src/Completable.cpp
        src/GtdHelper.cpp
        src/UpdateStack.cpp
        src/Task.cpp
        src/Project.cpp
        src/Context.cpp
        src/Folder.cpp
        src/main.cpp
)

target_link_libraries(runtime
        SQLite::SQLite3
        fmt::fmt
        SQLiteCpp)

IF (EXISTS "${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json")
    EXECUTE_PROCESS(COMMAND ${CMAKE_COMMAND} -E copy_if_different
            ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
            ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json
    )

ENDIF ()