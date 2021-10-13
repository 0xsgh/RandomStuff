cmake_minimum_required(VERSION 3.16)
project(StripAndSplit)

find_package(GTest REQUIRED CONFIG)

add_executable(test
               Main.cpp
               )
set_target_properties(test PROPERTIES CXX_STANDARD 11)

target_link_libraries(test PRIVATE GTest::gtest_main)