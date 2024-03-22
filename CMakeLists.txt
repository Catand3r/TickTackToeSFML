cmake_minimum_required(VERSION 3.22)
project(SFML_EXAMPLE)
enable_testing()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS -I"/Users/paulziemann/Documents/C++ Projects/SFML Example/")

add_executable(SFML_EXAMPLE main.cpp TicTacToe.cpp)



target_link_libraries(SFML_EXAMPLE
    /Users/paulziemann/Library/SFML/lib/libsfml-system.2.6.1.dylib
    /Users/paulziemann/Library/SFML/lib/libsfml-window.2.6.1.dylib
    /Users/paulziemann/Library/SFML/lib/libsfml-graphics.2.6.1.dylib
)

configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
    RESULT_VARIABLE result
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
    message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()


set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)


add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)


target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})

add_executable(${PROJECT_NAME}-ut tests/SFML-EXAMPLE-ut.cpp TicTacToe.cpp)
target_compile_options(${PROJECT_NAME}-ut PRIVATE ${FLAGS})
target_link_libraries(${PROJECT_NAME}-ut PUBLIC gtest_main
    /Users/paulziemann/Library/SFML/lib/libsfml-system.2.6.1.dylib
    /Users/paulziemann/Library/SFML/lib/libsfml-window.2.6.1.dylib
    /Users/paulziemann/Library/SFML/lib/libsfml-graphics.2.6.1.dylib
)

add_test(NAME SFMLExampleTests COMMAND ${PROJECT_NAME}-ut)