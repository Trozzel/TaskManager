cmake_minimum_required(VERSION 3.15)
project(GTD)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# AUTO ADD DEFINITIONS TO CODE BASED UPON BUILD TYPE
IF(CMAKE_BUILD_TYPE STREQUAL "Release")
	ADD_COMPILE_DEFINITIONS(RUNMODE="prod")
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "Debug")
	ADD_COMPILE_DEFINITIONS(RUNMODE="dev")
ENDIF()

# SQLITE C++
################################################################################
include(FetchContent)
FetchContent_Declare(SQLiteCpp
        GIT_REPOSITORY https://github.com/SRombauts/SQLiteCpp
        GIT_TAG master
)

# GOOGLETEST
################################################################################
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# FMT
################################################################################
FetchContent_Declare(fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG master
)

# TOML
################################################################################
FetchContent_Declare(tomlplusplus
        URL https://github.com/marzer/tomlplusplus/archive/refs/tags/v3.4.0.zip
        DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(SQLiteCpp
        googletest
        fmt
        tomlplusplus
)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(gtd
        src/GtdHelper.cpp
        src/UpdateStack.cpp
        src/GtdBase.cpp
        src/Context.cpp
        src/Folder.cpp
        src/Completable.cpp
        src/Task.cpp
        src/Project.cpp
        src/main.cpp
)

target_link_libraries(gtd
        ${SQLite3_LIBRARIES}
        sqlite3
        fmt::fmt
		tomlplusplus::tomlplusplus
        pthread
        dl)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(tests
        src/GtdBase.cpp
        src/Completable.cpp
        src/GtdHelper.cpp
        src/UpdateStack.cpp
        src/Task.cpp
        src/Project.cpp
        src/Context.cpp
        src/Folder.cpp
        src/tests.cpp
)

target_link_libraries(tests gtest_main
        ${SQLite3_LIBRARIES}
        sqlite3
        fmt::fmt
        pthread
		tomlplusplus::tomlplusplus
        dl)

add_test(NAME example_test COMMAND tests)

# CREATE SYMBOLIC LINK TO compile_commands.json IN CMAKE_SOURCE_DIR
IF (NOT EXISTS ${CMAKE_SOURCE_DIR}/compile_commands.json)
	FILE(CREATE_LINK
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
        SYMBOLIC)
    MESSAGE("-- Created symlink: ${CMAKE_SOURCE_DIR}/compile_commands.json --> ${CMAKE_BINARY_DIR}/compile_commands.json")
ENDIF ()

