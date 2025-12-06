#!/bin/bash
# cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
# cmake --build build --config Release -j$(nproc)

cmake --preset release-scalar
cmake --build --preset release-scalar -j"$(nproc)"