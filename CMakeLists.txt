cmake_minimum_required(VERSION 3.10.2)
set(CMAKE_CXX_STANDARD 17)

project(elevator_system)

include_directories(include)

file(GLOB LIB_SOURCES src/*.cpp)
file(GLOB LIB_HEADERS include/*.h)

# Create a library
add_library(elevatorLib ${LIB_SOURCES} ${LIB_HEADERS})

# Create the elevelator_system app (add project executable)
file( GLOB APP_SOURCES app/*.cpp )
add_executable(elevator_system ${APP_SOURCES})

# Make sure library is linked to each app
target_link_libraries(elevator_system elevatorLib)
