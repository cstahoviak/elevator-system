cmake_minimum_required(VERSION 3.10.2)

project(elevator_system)
set(CMAKE_CXX_STANDARD 17)

include_directories(include)

# find all executables
file(GLOB project_SRCS src/*.cpp)

# add project executable
add_executable(elevator_system ${project_SRCS})
