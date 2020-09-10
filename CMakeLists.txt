cmake_minimum_required(VERSION 3.0)

project(ODE)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

add_executable(ODE 
    src/ode.cpp)

target_link_libraries(ODE Eigen3::Eigen)
