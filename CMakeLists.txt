cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests tank_test.cc tank.cc)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread jpeg sfml-graphics sfml-audio sfml-window sfml-system)
add_executable(tank-battle tank-battle.cc tank.cc)
target_link_libraries(tank-battle ${GTEST_LIBRARIES} pthread jpeg sfml-graphics sfml-audio sfml-window sfml-system)
