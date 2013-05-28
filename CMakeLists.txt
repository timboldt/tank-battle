cmake_minimum_required(VERSION 2.6)
project(tankbattle)
 
################################
# GTest (assumes that gtest-1.6.0 has been extracted to a subdirectory of this project)
################################
ADD_SUBDIRECTORY (gtest-1.6.0)
#ADD_SUBDIRECTORY (Box2D_v2.2.1)
find_package(Box2D REQUIRED)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall")

add_executable(runTests tank_test.cc tank.cc)
target_link_libraries(runTests gtest gtest_main pthread jpeg sfml-graphics sfml-audio sfml-window sfml-system)
add_test(runTests runTests)

add_executable(tank-battle tank-battle.cc world.cc tank.cc)
target_link_libraries(tank-battle gtest gtest_main pthread jpeg sfml-graphics sfml-audio sfml-window sfml-system Box2D)
