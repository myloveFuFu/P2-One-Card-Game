cmake_minimum_required(VERSION 3.10)

project(OneCard VERSION 1.0 LANGUAGES C)

set(CMAKE_C_STANDARD 11)

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

set(SOURCES
    src/main.c
    src/card.c 
    src/card_figure.c 
    src/init_game.c 
    src/main.c 
    src/player.c 
    src/one_play.c 
    src/one_round.c 
    src/print_card.c 
    src/tool_box.c
)

add_executable(OneCard ${SOURCES})


