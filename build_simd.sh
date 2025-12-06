#!/bin/bash
cmake -S . -B build_simd -DCMAKE_BUILD_TYPE=Release -DENABLE_SIMD=ON
cmake --build build_simd -j$(nproc)
