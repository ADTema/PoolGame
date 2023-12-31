cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project(pong)

set(PONG_SOURCES
        src/main.cpp
        src/Window.cpp
        src/utils.cpp
        src/Scene.cpp
        src/Camera.cpp
        src/Game.cpp
        src/GameObject.cpp
        src/Context.cpp
        game/ExitGameScript.cpp
        game/PlayerScript.cpp
        game/CameraScript.cpp
        game/prefabs/Rectangle.cpp
        game/prefabs/PowerRow.cpp)
set(PONG_HEADERS
        headers/Window.h
        headers/Log.h
        headers/Game.h
        headers/GameObject.h
        headers/Component.h
        headers/Scene.h
        headers/utils.h
        headers/Camera.h
        headers/Context.h
        game/ExitGameScript.h
        game/PlayerScript.h
        game/CameraScript.h
        game/prefabs/Rectangle.h
        game/prefabs/PowerRow.h game/prefabs/Collision.cpp game/prefabs/Collision.h game/prefabs/Hole.cpp game/prefabs/Hole.h game/prefabs/Ball.cpp game/prefabs/Ball.h src/templates/Button.cpp headers/templates/Button.h src/templates/Text.cpp headers/templates/Text.h game/prefabs/Score.cpp game/prefabs/Score.h game/InputText.cpp game/InputText.h)

add_executable(pong ${PONG_SOURCES} ${PONG_HEADERS})


# SFML
add_subdirectory(externals/SFML)
target_include_directories(pong PRIVATE externals/SFML)
target_link_libraries(pong PRIVATE sfml-audio sfml-graphics sfml-window sfml-system sfml-network)

# glm
add_subdirectory(externals/glm)
target_include_directories(pong PRIVATE externals/glm)
target_link_libraries(pong PRIVATE glm::glm)

# spdlog
add_subdirectory(externals/spdlog)
target_include_directories(pong PRIVATE externals/spdlog)
target_link_libraries(pong PRIVATE spdlog::spdlog)

# thread_pool
add_library(thread_pool externals/thread_pool/include/BS_thread_pool.hpp externals/thread_pool/include/BS_thread_pool.hpp)
set_target_properties(thread_pool PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(pong PRIVATE externals/thread_pool)
target_link_libraries(pong PRIVATE thread_pool)

#box_2d_lite
add_subdirectory(externals/box_2d)
target_include_directories(pong PRIVATE externals/box_2d)
target_link_libraries(pong PRIVATE box2d)

#json
add_subdirectory(externals/json)
target_include_directories(pong PRIVATE externals/json)
target_link_libraries(pong PRIVATE nlohmann_json::nlohmann_json)