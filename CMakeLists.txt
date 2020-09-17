cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(ODE)

add_executable(ODE 
		src/main.cpp)

#includes CMAKE_SOURCE_DIR so that Eigen/* files are found, idiomatically
target_include_directories(ODE PRIVATE
		"${CMAKE_SOURCE_DIR}"
        "${CMAKE_SOURCE_DIR}/inc"
)
