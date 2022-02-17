cmake_minimum_required(VERSION 3.1)
project(wordle VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 11)

add_executable(wordle src/main.cpp src/wordleio.cpp src/search.cpp src/solve.cpp)

target_include_directories(wordle PUBLIC include)
target_compile_options(wordle PUBLIC -O3 -Wall)

find_package(OpenMP)
if(OpenMP_FOUND)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
endif()
