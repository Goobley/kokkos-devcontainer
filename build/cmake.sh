#!/bin/bash

./cmake_clean.sh

export PATH="$(pwd)/../kokkos/bin:${PATH}"

cmake \
    -DCMAKE_CXX_COMPILER="nvcc_wrapper" \
    -DCMAKE_CXX_FLAGS="-O0 -g -G"  \
    -DCMAKE_BUILD_TYPE="Release" \
    -DKokkos_ROOT="$(pwd)/../kokkos/" \
    -DCMAKE_PREFIX_PATH="$(pwd)/../kokkos/lib/cmake/" \
    ..