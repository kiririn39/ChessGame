cmake_minimum_required(VERSION 3.25)
project(ChessGame)

set(CMAKE_CXX_STANDARD 20)

include_directories(${Boost_INCLUDE_DIRS})
list(APPEND CMAKE_MODULE_PATH Backward)

add_subdirectory(SimpleEngine)
add_subdirectory(Game)
