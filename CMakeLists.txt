cmake_minimum_required(VERSION 2.6)
project(tankbattle)
 
################################
# GTest (assumes that gtest-1.6.0 has been extracted to a subdirectory of this project)
################################
ADD_SUBDIRECTORY (gtest-1.6.0)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests tank_test.cc tank.cc)
target_link_libraries(runTests gtest gtest_main pthread jpeg sfml-graphics sfml-audio sfml-window sfml-system)
add_executable(tank-battle tank-battle.cc tank.cc)
target_link_libraries(tank-battle gtest gtest_main pthread jpeg sfml-graphics sfml-audio sfml-window sfml-system)
