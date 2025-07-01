cmake_minimum_required(VERSION 3.10)
project(CarFunctionalitySystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Add executable
add_executable(CarTest TestCar.cpp Car.cpp)

# Add test executable (if using a testing framework like Google Test)
# Uncomment and modify if you're using a testing framework
# find_package(GTest REQUIRED)
# include_directories(${GTEST_INCLUDE_DIRS})
# add_executable(CarUnitTests tests/CarTests.cpp Car.cpp)
# target_link_libraries(CarUnitTests ${GTEST_LIBRARIES} pthread)

# Install targets
install(TARGETS CarTest DESTINATION bin)
install(FILES Car.h DESTINATION include)