add_library(INITIALIZE_LIBS SHARED
    src/miscellaneous.cpp
)

target_include_directories(INITIALIZE_LIBS PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)
