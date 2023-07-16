cmake_minimum_required(VERSION 3.10)
project(EgyptianRat)

find_package(SFML 2.5 COMPONENTS graphics audio window system network REQUIRED)

set(CMAKE_BASE_DIR         ${CMAKE_SOURCE_DIR})  # Set Directories
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BASE_DIR})        # Generated files (libs and .out) will be created here.
set(LIBRARY_OUTPUT_PATH    ${CMAKE_BASE_DIR}/lib)

file(GLOB_RECURSE LIB_DIRS
    LIST_DIRECTORIES true
    "Initialize/src/*.cpp"
    "Game/src/*.cpp"
)

file(GLOB HEADER_DIRS
	Initialize/include
	Game/include
)

include_directories(
	${HEADER_DIRS} 
	${LIB_DIRS}
)

add_library(LIBFILES
	${LIB_DIRS}
)

add_executable(Main.out main.cpp)

target_link_libraries(Main.out LIBFILES sfml-graphics sfml-audio)