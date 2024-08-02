cmake_minimum_required(VERSION 3.10.2)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(elevator_system CXX)

# Add googletest
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

# Tell CMake that we'll have unit tests 
enable_testing()

include_directories(include)

# TODO: Better to list sources and headers explicitly rather than use GLOB?
file(GLOB LIB_SOURCES src/*.cpp)
file(GLOB LIB_HEADERS include/*.h)

# Create a library. Library can be STATIC or SHARED (default is STATIC)
add_library(elevatorSystemLib ${LIB_SOURCES} ${LIB_HEADERS})

# Create the elevelator_system app (add project executable)
file( GLOB APP_SOURCES app/*.cpp )
add_executable(${PROJECT_NAME} ${APP_SOURCES})

# Make sure library is linked to each app
target_link_libraries(${PROJECT_NAME} elevatorSystemLib)

# Add the tests
add_subdirectory(test)