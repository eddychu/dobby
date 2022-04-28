cmake_minimum_required(VERSION 3.20)
project(dobby)

find_package(SDL2 REQUIRED)

add_executable(dobby main.cpp)

target_link_libraries(dobby ${SDL2_LIBRARIES})