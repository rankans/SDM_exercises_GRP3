# AGENTS.md - Development Guidelines for AI Coding Agents

This document provides guidelines for AI coding agents working on the SDM (Systems Development and Management) C++ exercises project. This is an academic project focused on database query optimization, SIMD processing, and parallel computing using IMDB data.

## Project Overview

- **Language**: C++23
- **Build System**: CMake (minimum 3.20)
- **Compiler**: Clang++ 19 
- **Domain**: Database query optimization, SIMD vectorization, multi-threading
- **Data**: IMDB dataset processing with AoS (Array of Structures) vs SoA (Structure of Arrays) layouts

## Build/Test Commands

### Standard Build Commands
```bash
# Release build (recommended)
./build.sh
# OR manually:
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release -j$(nproc)

# SIMD-optimized build (AVX2/FMA/BMI2)
./build_simd.sh
# OR manually:
cmake -S . -B build_simd -DCMAKE_BUILD_TYPE=Release -DENABLE_SIMD=ON
cmake --build build_simd -j$(nproc)

# Debug build
cmake -S . -B build_debug -DCMAKE_BUILD_TYPE=Debug
cmake --build build_debug --config Debug -j$(nproc)
```

### Individual Exercise Builds
```bash
# Build specific exercise (from build directory)
cd build
make exercise4_main     # Query optimization
make exercise6_main     # Iterator vs Batch processing
make exercise7_main     # SIMD implementations
make exercise8_main     # Multi-threading (MIMD)
```

### Running Executables
```bash
# From build directory
./src/exercise4/exercise4_main
./src/exercise6/exercise6_main
./src/exercise7_simd/mac/exercise7_main  # On macOS
./src/exercise8_mimd/exercise8_main
```

### Testing
- **No formal test framework** - this project uses benchmarking within executables
- Verification through performance measurement and correctness checks
- Manual testing by running executables and examining output

## Code Style Guidelines

### Naming Conventions
- **Classes/Structs**: `snake_case` (e.g., `title_record`, `keyword_record`)
- **Functions/Methods**: `snake_case` (e.g., `load_from_file()`, `split_line()`)
- **Variables**: `snake_case` (e.g., `max_year`, `distinct_keywords`)
- **Private Members**: `_snake_case` prefix (e.g., `_id`, `_title`, `_threadCount`)
- **Constants**: `ALL_CAPS` for preprocessor (e.g., `USE_AVX2`, `USE_NEON`)
- **Files**: `snake_case.hpp/.cpp` (e.g., `title.hpp`, `avx2_simd_filter.cpp`)

### Formatting Standards
- **Indentation**: 4 spaces (no tabs)
- **Braces**: Opening brace on same line
- **Line Length**: Keep under 120 characters
- **Spacing**: Single space around operators, after commas

### Header/Include Organization
```cpp
#include <iostream>        // System headers first
#include <vector>
#include <string>

#include "utils.hpp"       // Local headers second
#include "../commons/utils.hpp"
```
- Use `#pragma once` for header guards
- Group system includes, then local includes
- Use relative paths for local includes

### Type Usage
- Prefer **explicit types**: `std::int64_t` over `int64_t` or `long long`
- Use **auto** with structured bindings: `auto [ptr, ec] = std::from_chars(...)`
- Apply **const-correctness** extensively:
  ```cpp
  const std::vector<int64_t> &id() const noexcept { return _id; }
  ```
- **AVOID** `using namespace std;` - use explicit `std::` prefix

### Error Handling (C++23)
- Use **std::expected** for error handling:
  ```cpp
  std::expected<std::vector<std::string>, err_t>
  split_line(std::string_view line, size_t max_fields, char delim = '|');
  ```
- Return errors with `std::unexpected()`:
  ```cpp
  if (condition_failed) {
      return std::unexpected("Error message");
  }
  ```
- **NO exceptions** - use return-based error handling only

### Modern C++ Features
- **C++23**: `std::expected`, `std::string_view`
- **C++17**: Structured bindings, `std::from_chars`
- Use **range-based for loops**: `for (const auto &rec : records)`
- Apply **move semantics** in constructors: `std::move(parameter)`
- Mark functions **noexcept** where appropriate

### Documentation
- Add **brief comments** for complex algorithms, especially SIMD code
- Document **SQL equivalents** for database operations:
  ```cpp
  // SELECT title FROM title WHERE production_year < 2000 AND production_year >= 1970
  ```
- Include **database schema** comments when relevant:
  ```cpp
  // Table "public.title"
  //      Column      |         Type          | Nullable 
  ```

## Project Structure

### Source Organization
```
src/
├── commons/            # Shared utilities, CSV parsing
├── aos_table_defs/     # Array of Structures data layouts
├── soa_table_defs/     # Structure of Arrays data layouts
├── exercise2/          # SIMD filtering exercises
├── exercise4/          # Query optimization exercises
├── exercise6/          # Iterator vs Batch processing
├── exercise7_simd/     # Platform-specific SIMD (intel/mac)
└── exercise8_mimd/     # Multi-threading exercises
```

### CMake Structure
- Root `CMakeLists.txt` includes active exercises
- Each exercise has its own `CMakeLists.txt`
- Use `add_subdirectory()` to enable/disable exercises

## Platform-Specific Notes

### SIMD Support
- **Intel**: AVX2, FMA, BMI2 instructions in `exercise7_simd/intel/`
- **macOS**: ARM NEON instructions in `exercise7_simd/mac/`
- Build with `-DENABLE_SIMD=ON` for optimizations

### Development Environment
- **Docker**: Use `.devcontainer/` for consistent environment
- **VS Code**: Configured with C++ IntelliSense, Prettier formatting
- **Compiler**: Clang++ 19 preferred, GCC compatible

## Performance Considerations

- **Compiler Optimizations**: Release builds use `-O3`
- **Parallel Builds**: Use `-j$(nproc)` for faster compilation
- **SIMD Vectorization**: Enable for performance-critical code
- **Data Layout**: Prefer SoA (Structure of Arrays) for vectorized operations
- **Memory Access**: Consider cache-friendly access patterns

## Development Workflow

1. **Always build in Release mode** for performance testing
2. **Profile before optimizing** - measure actual bottlenecks
3. **Test both AoS and SoA** data layouts for comparison
4. **Verify correctness** before performance optimization
5. **Document performance characteristics** in code comments

## Common Patterns

### CSV Processing
```cpp
auto result = csv::split_line(line, max_fields, '|');
if (!result) {
    return std::unexpected(result.error());
}
```

### SIMD Conditional Processing  
```cpp
#ifdef USE_AVX2
    // AVX2 implementation
#else
    // Scalar fallback
#endif
```

### Thread Pool Usage
```cpp
std::vector<std::thread> threads;
for (size_t i = 0; i < thread_count; ++i) {
    threads.emplace_back([&, i] { /* work */ });
}
```

This codebase emphasizes **performance optimization** and **educational exploration** of different database processing techniques. Maintain these priorities when making changes.