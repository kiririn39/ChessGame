cmake_minimum_required(VERSION 3.25)
project(SimpleEngine)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

# Also requires one of: libbfd (gnu binutils), libdwarf, libdw (elfutils)
FetchContent_Declare(backward
        GIT_REPOSITORY https://github.com/bombela/backward-cpp
        GIT_TAG v1.6)
FetchContent_MakeAvailable(backward)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS src/*.cpp)

add_library(SimpleEngine STATIC Engine.h EngineCore.cpp Object.cpp EngineCoreTemplates.h Logger.h GameObjectTemplates.h Object.h EngineCore.h Logger.cpp GameObject.h Engine.h Renderer.h Renderer.cpp GameObject.cpp Collisions/CollisionsDetector.cpp Components/Camera2dComponent.cpp Components/CollisionBaseComponent.cpp Components/GameObjectComponent.cpp Components/IReceiveCollisionUpdates.h Components/RectangleCollisionComponent.cpp Components/RectangleCollisionComponent.h Components/SpriteComponent.cpp Components/SpriteComponent.h Components/TransformComponent.cpp Components/TransformComponent.h Components/UIComponent.cpp Input/Input.cpp Input/Input.h Memory/MemoryPool.cpp Memory/MemoryPoolTemplates.h ${SOURCES} ${BACKWARD_ENABLE} Utilities/Backward.cpp Utilities/Backward.h Utilities/Format.h)
target_include_directories(SimpleEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

add_backward(SimpleEngine)
target_link_libraries(SimpleEngine PUBLIC raylib raylib_cpp)