cmake_minimum_required(VERSION 3.27)
project(Assignment_1)
set(CMAKE_C_STANDARD 23)

add_executable(Assignment_1 main.c)

set(CMAKE_CXX_STANDARD 14)
find_package(MPI REQUIRED)

target_link_libraries(Assignment_1 PUBLIC MPI::MPI_CXX)