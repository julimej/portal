cmake_minimum_required(VERSION 3.1)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set (CMAKE_CXX_FLAGS -pthread)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -g")
set(CMAKE_CXX_STANDARD 11)

# Tomar los archivos fuente del cliente (todos los *.cpp)
file(GLOB_RECURSE liblevelcreator_srcs *.cpp)
#add_directory(../modelo)

# Generar una libería estática con todo el cliente EXCEPTO el main
add_library(levelcreator ${liblevelcreator_srcs})
target_link_libraries(levelcreator servermodelo pthread TG::Box2D)