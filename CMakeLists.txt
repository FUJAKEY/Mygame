cmake_minimum_required(VERSION 3.10)
project(MyGame)

set(CMAKE_CXX_STANDARD 17)

add_library(GameCore
    src/Game.cpp
    src/Player.cpp
    src/FrozenBlock.cpp
    src/PlatformBlock.cpp
    src/GrapplingHook.cpp
    src/Level.cpp
    src/GameContactListener.cpp
)

add_executable(GameApp
    src/main.cpp
)

target_include_directories(GameCore PUBLIC include /usr/local/include $ENV{ANDROID_NDK_HOME}/sources/third_party/sfml/include)

find_package(SFML COMPONENTS graphics window system REQUIRED)

# Box2D might not provide a CMake config file on all systems
find_package(box2d REQUIRED)
target_link_libraries(GameCore PUBLIC box2d::box2d)

target_link_libraries(GameApp PRIVATE GameCore sfml-graphics sfml-window sfml-system)
