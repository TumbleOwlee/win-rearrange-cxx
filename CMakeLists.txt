# Set version requirement
cmake_minimum_required(VERSION 3.20)

# Define project
project(win-rearrange-cxx
	VERSION 0.0.1
    DESCRIPTION "Tool to rearrange windows automatically"
	LANGUAGES C CXX)
   
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set default to Debug
if("${CMAKE_BUILD_TYPE}" STREQUAL "")
	set(CMAKE_BUILD_TYPE Debug)
endif()
message("Build type: ${CMAKE_BUILD_TYPE}")

# Set publisher name 
set(EXE "win-rearrange-cxx")
# Add executable
add_executable(${EXE} "src/main.cxx" "src/XSystem.cxx" "src/XWindow.cxx" "src/Handler.cxx" "src/Config.cxx" "src/Command.cxx")
target_include_directories(${EXE} PUBLIC ${CMAKE_SOURCE_DIR}/incl ${CMAKE_SOURCE_DIR}/deps/cereal/include)
target_link_libraries(${EXE} X11 pthread)

