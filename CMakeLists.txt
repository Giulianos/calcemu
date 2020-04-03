cmake_minimum_required(VERSION 3.10)
project(calcemu)

set(CMAKE_CXX_STANDARD 14)

add_executable(calcemu
        libs/mathio/LineIO.cpp
        libs/mathio/MathIO.cpp
        libs/mathio/screenbuffer.cpp
        libs/mathio/screenbufferwindow.cpp
        main.cpp
        screen.cpp)

find_library(SDL2_LIBRARY SDL2 "path/to/your/library_bundle")

target_include_directories(calcemu PRIVATE libs/mathio/include)
target_include_directories(calcemu PRIVATE .)

find_package(SDL2 REQUIRED)
target_include_directories(calcemu PRIVATE ${SDL2_INCLUDE_DIR})

target_link_libraries(calcemu ${SDL2_LIBRARY})
