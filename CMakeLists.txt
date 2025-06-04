cmake_minimum_required(VERSION 3.10)
project(MyGame)

set(CMAKE_CXX_STANDARD 17)

add_library(GameCore
    src/Game.cpp
    src/Player.cpp
    src/FrozenBlock.cpp
    src/Level.cpp
    src/GameContactListener.cpp
)

add_executable(GameApp
    src/main.cpp
)

target_include_directories(GameCore PUBLIC include)

find_package(SFML 2 COMPONENTS graphics window system REQUIRED)

# Box2D might not provide a CMake config file on all systems
find_package(Box2D)
if(Box2D_FOUND)
    target_link_libraries(GameCore PUBLIC Box2D)
else()
    target_link_libraries(GameCore PUBLIC box2d)
endif()

target_link_libraries(GameApp PRIVATE GameCore sfml-graphics sfml-window sfml-system)
