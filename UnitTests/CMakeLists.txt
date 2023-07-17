cmake_minimum_required(VERSION 3.10)
project("EgyptianRatUnitTests")

find_package(SFML 2.5 COMPONENTS graphics audio window system network REQUIRED)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

add_executable(UnitTests.out testHarness.cpp)
add_definitions(-DUNIT_TEST_MODE)

add_library(TEST_LIBS STATIC
    ../Initialize/src/miscellaneous.cpp
    miscellaneous_test.cpp 
)

include_directories(UnitTests.out PUBLIC
    ../Initialize/headers
    ../Game/headers
)

target_link_libraries(UnitTests.out PUBLIC 
    TEST_LIBS
    sfml-graphics 
    sfml-audio
)
