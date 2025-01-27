#!/bin/bash

./docker_setup.sh \
    "-DKokkos_ENABLE_SERIAL=ON \
     -DKokkos_ENABLE_COMPILE_AS_CMAKE_LANGUAGE=ON \
     -DKokkos_ENABLE_THREADS=ON \
     -DKokkos_ENABLE_CUDA=ON \
     -DKokkos_ARCH_AMPERE86=ON \
     -DKokkos_ENABLE_CUDA_CONSTEXPR=ON \
     -DKokkos_ENABLE_CUDA_LAMBDA=ON \
     -DCMAKE_BUILD_TYPE=Release \
     -DCMAKE_INSTALL_PREFIX=$(pwd)/../../kokkos"