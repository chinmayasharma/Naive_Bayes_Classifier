cmake_minimum_required(VERSION 3.5)
project(naivebayes)

set(CMAKE_CXX_STANDARD 14)

add_executable(main src/main.cpp src/image.h src/image.cpp src/model.cpp src/model.h src/digit.cpp src/digit.h)
add_executable(unit-tests test/naivebayes-tests.cpp src/image.h src/image.cpp src/model.cpp src/model.h src/digit.cpp src/digit.h)