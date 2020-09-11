cmake_minimum_required(VERSION 3.0)

project(ODE)

add_executable(ODE 
		src/ode.cpp
		src/rungeKutta.cpp
)

#includes CMAKE_SOURCE_DIR so that Eigen/* files are found, idiomatically
target_include_directories(ODE PRIVATE
		"${CMAKE_SOURCE_DIR}"
)
