#!/bin/bash

# ============================================
# Reaction Test Cases Build Script
# ============================================

# Exit on error
set -e

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

echo "======================================"
echo "Building Reaction Test Cases"
echo "======================================"

# Clean old build directory (optional)
if [ "$1" == "clean" ]; then
    echo "Cleaning build directory..."
    rm -rf build
fi

# Create build directory
mkdir -p build
cd build

# Run CMake configuration
echo "Configuring with CMake..."
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON

# Compile
# echo "Building..."
# cmake --build . -j$(nproc)

# # Run tests
# echo "======================================"
# echo "Running Tests"
# echo "======================================"
# ctest --output-on-failure

# echo "======================================"
# echo "Build and Test Completed Successfully!"
# echo "======================================"

# ENABLE_COVERAGE=${ENABLE_COVERAGE:-ON}
# # Only generate report when coverage is enabled
# if [ "$ENABLE_COVERAGE" = "ON" ]; then
#     echo ""
#     echo "======================================"
#     echo "Generating coverage report..."
#     echo "======================================"

#     # Detect GCC version and select appropriate gcov tool
#     GCC_VERSION=13
#     GCOV_TOOL="gcov-${GCC_VERSION}"

#     if ! command -v "$GCOV_TOOL" &> /dev/null; then
#         echo "Warning: $GCOV_TOOL not found, trying to use default gcov"
#         GCOV_TOOL="gcov"
#     fi

#     echo "Using tool: $GCOV_TOOL"

#     # Generate text summary
#     echo ""
#     echo "[Coverage Summary - tests directory]"
#     echo "Current directory: $(pwd)"
#     # Filter source files under tests directory using absolute path
#     gcovr --gcov-executable "$GCOV_TOOL" \
#           --root "$PROJECT_DIR" \
#           --filter "$PROJECT_DIR/tests/" \
#           --print-summary
# else
#     echo ""
#     echo -e "${YELLOW}Note: Code coverage not enabled. To generate coverage report, use:${NC}"
#     echo -e "  ${YELLOW}ENABLE_COVERAGE=ON CLEAN_BUILD=yes ./build.sh${NC}"
# fi