cmake_minimum_required(VERSION 3.25)
project(ChessGame)

set(CMAKE_CXX_STANDARD 23)

add_executable(ChessGame ChessGame.cpp ChessGameGeneral.h Components/BoardTileComponent.cpp Components/BoardTileComponent.h Components/CameraStatsComponent.cpp Components/CameraStatsComponent.h Components/CameraZoomComponent.cpp Components/CameraZoomComponent.h Components/ChessBoardComponent.cpp Components/ChessBoardComponent.h Components/ChessPieceComponent.cpp Components/ChessPieceComponent.h Components/CollisionTestComponent.cpp Components/CollisionTestComponent.h Components/EngineStatsComponent.cpp Components/EngineStatsComponent.h Components/KeyboardMovementComponent.cpp Components/KeyboardMovementComponent.h)
target_link_libraries(ChessGame PRIVATE SimpleEngine)

add_custom_command(
        TARGET ChessGame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Game/Resources
        $<TARGET_FILE_DIR:ChessGame>/Resources
)