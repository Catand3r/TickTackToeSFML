cmake_minimum_required(VERSION 3.22)
project(SFML_EXAMPLE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -I"/Users/paulziemann/Documents/C++ Projects/SFML Example/")

add_executable(SFML_EXAMPLE main.cpp)



target_link_libraries(SFML_EXAMPLE
    /Users/paulziemann/Library/SFML/lib/libsfml-system.2.6.1.dylib
    /Users/paulziemann/Library/SFML/lib/libsfml-window.2.6.1.dylib
    /Users/paulziemann/Library/SFML/lib/libsfml-graphics.2.6.1.dylib
)