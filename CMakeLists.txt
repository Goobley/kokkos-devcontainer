# Kokkos minimally requires 3.16 right now,
# but your project can set it higher
cmake_minimum_required(VERSION 3.16)

# Projects can safely mix languages - must have C++ support
# Kokkos flags will only apply to C++ files
project(Example CXX CUDA)

# Look for an installed Kokkos
find_package(Kokkos REQUIRED)
find_package(MPI REQUIRED)

add_executable(example example.cpp)
set_target_properties(example PROPERTIES CUDA_ARCHITECTURES ${Kokkos_CUDA_ARCHITECTURES})
target_include_directories(example PRIVATE ${MPI_CXX_INCLUDE_PATH})
set_property(SOURCE example.cpp PROPERTY LANGUAGE ${Kokkos_COMPILE_LANGUAGE})
message(${Kokkos_COMPILE_LANGUAGE})
message(${MPI_CXX_COMPILER})

# This is the only thing required to set up compiler/linker flags
target_link_libraries(example Kokkos::kokkos MPI::MPI_CXX)