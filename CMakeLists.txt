cmake_minimum_required(VERSION 3.10)

project(CPU-RayTracer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CPU-RayTracer src/main.cc)
# add_executable(pi src/pi.cc)
# add_executable(integrate_x_sq src/integrate_x_sq.cc)
# add_executable(estimate_halfway src/estimate_halfway.cc)
add_executable(sphere_importance src/sphere_importance.cc)
# add_executable(sphere_plot src/sphere_plot.cc)
add_executable(cos_cubed.cc src/cos_cubed.cc)
# add_executable(cos_density.cc src/cos_density.cc)
