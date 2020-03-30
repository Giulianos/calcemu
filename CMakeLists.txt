cmake_minimum_required(VERSION 3.15)
project(calcemu)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(libs/mathio)

add_executable(calcemu
        libs/mathio/fractionio.cpp
        libs/mathio/lineio.cpp
        libs/mathio/powerio.cpp
        libs/mathio/screenbuffer.cpp
        libs/mathio/screenbufferwindow.cpp
        main.cpp
        screen.cpp)


target_include_directories(calcemu PRIVATE libs/mathio/include)
target_include_directories(calcemu PRIVATE SDL2)

target_link_libraries(calcemu SDL2)
