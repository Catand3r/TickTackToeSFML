cmake_minimum_required(VERSION 3.22)
project(SFML_EXAMPLE)
enable_testing()

set(CMAKE_CXX_STANDARD 20)

include_directories(./)
link_directories(./lib/Linux)


add_executable(SFML_EXAMPLE main.cpp TicTacToe.cpp)

target_link_libraries(SFML_EXAMPLE
    libsfml-system.so.2.6.1
    libsfml-window.so.2.6.1
    libsfml-graphics.so.2.6.1
    libsfml-network.so.2.6.1
)

# target_link_libraries(SFML_EXAMPLE
#     libsfml-system.2.6.1.dylib
#     libsfml-window.2.6.1.dylib
#     libsfml-graphics.2.6.1.dylib
#     libsfml-network.2.6.1.dylib
# )

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
    libsfml-system.2.6.1.dylib
    libsfml-window.2.6.1.dylib
    libsfml-graphics.2.6.1.dylib
    libsfml-network.2.6.1.dylib
)

add_test(NAME SFMLExampleTests COMMAND ${PROJECT_NAME}-ut)