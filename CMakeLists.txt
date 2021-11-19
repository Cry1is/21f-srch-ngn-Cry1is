cmake_minimum_required(VERSION 3.17)
project(21f_srch_ngn)

set(CMAKE_CXX_STANDARD 14)

add_executable(21f_srch_ngn main.cpp AVLTree.h DocParser.cpp)
add_executable(21f_srch_ngn_test tests.cpp catch_setup.cpp AVLTree.h)