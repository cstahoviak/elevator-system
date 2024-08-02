cmake_minimum_required(VERSION 3.10.2)

# Get the test source files
file(GLOB TEST_SOURCES *.cpp)

set(TEST_NAME ${PROJECT_NAME}_tests)

# Create the test executable
add_executable(${TEST_NAME} ${TEST_SOURCES})

# Linking
target_link_libraries(${TEST_NAME} PUBLIC
  # link our tests against the googletest library
  gtest_main
  # link our tests against our own library
  elevatorSystemLib
)

# Add the tests
add_test(
  NAME ${TEST_NAME}
  COMMAND ${TEST_NAME}
)