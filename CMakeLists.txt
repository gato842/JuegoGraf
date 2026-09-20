cmake_minimum_required(VERSION 3.20) 
project(mi_juego LANGUAGES C CXX) 
 
set(CMAKE_CXX_STANDARD 17) 
set(CMAKE_CXX_STANDARD_REQUIRED ON) 
find_package(raylib CONFIG REQUIRED) 
 
add_executable(mi_juego 
    src/Juego/main.cpp
    src/Juego/src/Player.cpp
    src/Juego/src/Fire.cpp
    src/Juego/src/Bucket.cpp
    src/Juego/src/WaterBeam.cpp
    src/Juego/src/Game.cpp
    src/Juego/src/Level1.cpp
    src/Juego/src/Level2.cpp
    src/Juego/src/HelperNPC.cpp
    src/Juego/src/Menu.cpp
    src/Juego/src/Credits.cpp
    src/Juego/src/TextureUtils.cpp
    src/Juego/src/Intro.cpp
    src/Juego/src/HighScore.cpp
)
target_include_directories(mi_juego PRIVATE src/Juego/include)
target_link_libraries(mi_juego PRIVATE raylib)
