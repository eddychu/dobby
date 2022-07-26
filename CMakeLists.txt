cmake_minimum_required(VERSION 3.20)
project(dobby CXX)
set (CMAKE_CXX_STANDARD 20)

find_package(SDL2 REQUIRED)
find_package( assimp CONFIG REQUIRED )

file(GLOB_RECURSE CPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE HPP_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h)

include_directories(src)

add_executable(dobby main.cpp ${HPP_FILES} ${CPP_FILES})

target_link_libraries(dobby ${SDL2_LIBRARIES} assimp)
