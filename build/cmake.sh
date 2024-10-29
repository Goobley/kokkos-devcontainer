#!/bin/bash

./cmake_clean.sh

cmake -DCMAKE_CXX_COMPILER="nvcc_wrapper" ..