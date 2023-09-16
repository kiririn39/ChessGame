cmake_minimum_required(VERSION 3.25)
project(SimpleEngine)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        entt
        GIT_REPOSITORY https://github.com/skypjack/entt.git
        GIT_TAG v3.10.0
)
FetchContent_MakeAvailable(entt)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_library(SimpleEngine STATIC Engine.h EngineCore.cpp Object.cpp EngineCoreTemplates.h Logger.h GameObjectTemplates.h Object.h EngineCore.h Logger.cpp GameObject.h Engine.h Renderer.h Renderer.cpp GameObject.cpp Collisions/CollisionsDetector.cpp Components/Camera2dComponent.cpp Components/CollisionBaseComponent.cpp Components/GameObjectComponent.cpp Components/IReceiveCollisionUpdates.h Components/RectangleCollisionComponent.cpp Components/RectangleCollisionComponent.h Components/SpriteComponent.cpp Components/SpriteComponent.h Components/TransformComponent.cpp Components/TransformComponent.h Components/UIComponent.cpp Input/Input.cpp Input/Input.h Memory/MemoryPool.cpp Memory/MemoryPoolTemplates.h ${SOURCES} Utilities/Format.h GameEntities/GameEntity.cpp GameEntities/GameEntity.h Utilities/EngineTypeChecking.h GameEntities/GameComponent.cpp GameEntities/GameComponent.h GameEntities/GameComponentTemplates.h)
target_include_directories(SimpleEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(SimpleEngine PUBLIC raylib)
target_link_libraries(SimpleEngine PUBLIC EnTT::EnTT)
target_include_directories(SimpleEngine PUBLIC ${EnTT_SOURCE_DIR}/single_include/entt)