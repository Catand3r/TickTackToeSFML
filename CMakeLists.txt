cmake_minimum_required(VERSION 3.22)
project(SFML_EXAMPLE)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -I"/Users/paulziemann/Documents/C++ Projects/SFML Example/")
#set(SFML_INCLUDE_DIR "./SFML/Library/Frameworks/include")
#set(SFML_DIR "/Users/paulziemann/Library/SFML")
#set(SFML_LIBRARY_DIR "/Users/paulziemann/Library/SFML/lib")

#link_directories(SFML_LIBRARY_DIR)
#include_directories(SFML_INCLUDE_DIR)

#find_package(SFML COMPONENTS system window graphics network audio)

add_executable(SFML_EXAMPLE main.cpp)

#target_link_libraries(SFML_EXAMPLE sfml-graphics sfml-window sfml-system)

target_link_libraries(SFML_EXAMPLE
    /Users/paulziemann/Library/SFML/lib/libsfml-system.2.6.1.dylib
    /Users/paulziemann/Library/SFML/lib/libsfml-window.2.6.1.dylib
    /Users/paulziemann/Library/SFML/lib/libsfml-graphics.2.6.1.dylib
#    /Users/paulziemann/Library/SFML/Frameworks/SFML.framework
#    /Users/paulziemann/Library/SFML/Frameworks/sfml-system.framework/sfml-system
#    /Users/paulziemann/Library/SFML/Frameworks/sfml-window.framework/sfml-window
#    /Users/paulziemann/Library/SFML/Frameworks/sfml-graphics.framework/sfml-graphics
)