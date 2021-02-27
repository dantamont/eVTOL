# CMake build for the Joby test project

message( STATUS "---------Beginning cmake build of Joby Test---------")

# Project-level setup ====================================================
project( Joby ) # TODO: Set version
cmake_minimum_required( VERSION 3.16 )
set(TARGET_NAME "joby")
set(TEST_TARGET_NAME "joby_tests")

message (STATUS "--------- Set target ${TARGET_NAME}---------")

# Set compiler flags =====================================================
# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Multiprocess compiler, disable specific warnings
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /wd4577 /wd4467")

# Set build mode directory options ========================================
# add_definitions(-DAPPLETTUTORIAL1_LIBRARY)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_BINARY_DIR}/debug)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_BINARY_DIR}/release)

# Build EXE ===============================================================
# Note: While GLOB is not recommended by the creators of cmake since it does not auto-run when files
# are added or modified, this is still easier than manually editing the cmake file when modifications are made

# Get all of the source files to build the main application
message (STATUS "-------- Finding source, header, resource, UI files relative to  ${CMAKE_SOURCE_DIR} ---------")
file(GLOB_RECURSE MY_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp"  "src/*.h"
"resources/*.qrc" "ui/*.ui")

# Get all the source files to build the test suite
file(GLOB_RECURSE MY_TEST_SOURCES RELATIVE ${CMAKE_SOURCE_DIR} "src/*.cpp" "src/*.h" "resources/*.qrc" "ui/*.ui" "tests/*.cpp" "tests/*.h")
list(FILTER MY_TEST_SOURCES EXCLUDE REGEX "src/apps/eVTOL/main.cpp")

message (STATUS "=========== FOUND FILES =============")
message (STATUS "${MY_SOURCES}")
message (STATUS "${MY_TEST_SOURCES}")
message (STATUS "=========== END FILES ===============")

# Generate release PDB
# https://stackoverflow.com/questions/28178978/how-to-generate-pdb-files-for-release-build-with-cmake-flags/31264946
add_compile_options("$<$<NOT:$<CONFIG:Debug>>:/Zi>")
add_link_options("$<$<NOT:$<CONFIG:Debug>>:/DEBUG>")
add_link_options("$<$<NOT:$<CONFIG:Debug>>:/OPT:REF>")
add_link_options("$<$<NOT:$<CONFIG:Debug>>:/OPT:ICF>")

# Add executables to be built from source lists
add_executable(${TARGET_NAME} ${MY_SOURCES}) 
add_executable(${TEST_TARGET_NAME} ${MY_TEST_SOURCES})

# Pre-processor Defines ===================================================
# add_definitions(-DDEVELOP_MODE)

# Disable warnings about deprecated things, like using strcpy (sorry, not sorry)
if(MSVC)
    add_definitions(-D_CRT_SECURE_NO_WARNINGS)
endif()

# Command-line configuration ===================================================
set_target_properties(${TARGET_NAME} PROPERTIES VS_DEBUGGER_COMMAND_ARGUMENTS "${CMAKE_SOURCE_DIR}")

# Add additional include directories =======================================
# This is nice because it allows path specifications relative to the /src directory
target_include_directories(${TARGET_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src")
target_include_directories(${TEST_TARGET_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/src")

########### Iterate over all targets to link libraries #################
foreach(current_target ${TARGET_NAME} ${TEST_TARGET_NAME})

# Add compile definitions to the target ===================================
# Set options based on debug or release mode
set(DEBUG_DEFINITIONS "DEBUG_MODE")
set(RELEASE_DEFINITIONS "")
target_compile_definitions(${current_target} PUBLIC
    $<$<CONFIG:DEBUG>:${DEBUG_DEFINITIONS}>
    $<$<CONFIG:RELEASE>:${RELEASE_DEFINITIONS}>
)

endforeach()