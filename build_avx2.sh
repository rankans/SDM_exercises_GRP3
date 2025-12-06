cmake --preset release-avx2
cmake --build --preset release-avx2 -j"$(nproc)"
