cmake_minimum_required(VERSION 3.10)
project("EgyptianRat")

find_package(SFML 2.5 COMPONENTS graphics audio window system network REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})     
set(LIBRARY_OUTPUT_PATH    ${CMAKE_BINARY_DIR}/lib)

add_executable(EgyptianRat.out main.cpp)

add_subdirectory(Initialize)
add_subdirectory(Game)

target_link_libraries(EgyptianRat.out PUBLIC
	GAME_LIBS
	INITIALIZE_LIBS
	sfml-graphics 
	sfml-audio
)