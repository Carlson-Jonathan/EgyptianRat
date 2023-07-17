add_library(GAME_LIBS SHARED
    src/placeHolder.cpp
)

target_include_directories(GAME_LIBS PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/headers
)
