# Kokkos minimally requires 3.16 right now,
# but your project can set it higher
cmake_minimum_required(VERSION 3.16)

# Projects can safely mix languages - must have C++ support
# Kokkos flags will only apply to C++ files
project(Example CXX CUDA)

# Look for an installed Kokkos
find_package(Kokkos REQUIRED)

add_executable(example example.cpp)
set_target_properties(example PROPERTIES CUDA_ARCHITECTURES "86")
set_property(SOURCE example.cpp PROPERTY LANGUAGE CUDA)

# This is the only thing required to set up compiler/linker flags
target_link_libraries(example Kokkos::kokkos)