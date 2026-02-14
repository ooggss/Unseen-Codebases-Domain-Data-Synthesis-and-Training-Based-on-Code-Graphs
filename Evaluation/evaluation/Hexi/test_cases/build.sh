#!/bin/bash

# Hexi Test Cases Build Script

set -e  # Exit on error

# Color definitions
GREEN='\033[0;32m'
BLUE='\033[0;34m'
RED='\033[0;31m'
NC='\033[0m' # No Color

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}Hexi Test Cases Build Script${NC}"
echo -e "${BLUE}========================================${NC}"

# Check if build directory exists
if [ -d "build" ]; then
    echo -e "${BLUE}Cleaning old build directory...${NC}"
    rm -rf build
fi

# Create build directory
echo -e "${BLUE}Creating build directory...${NC}"
mkdir -p build
cd build

# Run CMake configuration
echo -e "${BLUE}Running CMake configuration...${NC}"
cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DBUILD_TESTS=ON

# Compile
# echo -e "${BLUE}Starting compilation...${NC}"
# cmake --build . --config Release -j$(nproc)

# # Run tests
# echo -e "${GREEN}========================================${NC}"
# echo -e "${GREEN}Running tests...${NC}"
# echo -e "${GREEN}========================================${NC}"
# ctest --output-on-failure

# echo -e "${GREEN}========================================${NC}"
# echo -e "${GREEN}Build successful!${NC}"
# echo -e "${GREEN}========================================${NC}"
# echo -e "Test executable located at: ${BLUE}build/test_hexi_basic${NC}"
# echo -e "You can run directly: ${BLUE}./build/test_hexi_basic${NC}"

# echo ""
# echo "======================================"
# echo "Generating coverage report..."
# echo "======================================"

# # Detect GCC version and select appropriate gcov tool
# GCC_VERSION=13
# GCOV_TOOL="gcov-${GCC_VERSION}"

# if ! command -v "$GCOV_TOOL" &> /dev/null; then
#     echo "Warning: $GCOV_TOOL not found, trying to use default gcov"
#     GCOV_TOOL="gcov"
# fi

# echo "Using tool: $GCOV_TOOL"

# # Generate text summary
# echo ""
# echo "[Coverage Summary - tests directory only]"
# echo pwd: $(pwd)
# gcovr --gcov-executable "$GCOV_TOOL" --root .. --filter '../tests/.*' --print-summary