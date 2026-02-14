#!/bin/bash

# sqlgen test cases build script

set -e  # Exit on error

# Color output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}sqlgen Test Cases Build Script${NC}"
echo -e "${GREEN}========================================${NC}"

# Get project root directory
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
SQLGEN_DIR="/data/workspace/Private-Model-Evaluation-sqlgen/third_patry_project/sqlgen"
# SQLGEN_DIR="${PROJECT_DIR}/../../../third_patry_project/sqlgen"

echo -e "\n${YELLOW}[Step 1/5]${NC} Checking sqlgen directory..."
if [ ! -d "$SQLGEN_DIR" ]; then
    echo -e "${RED}Error: Cannot find sqlgen directory: $SQLGEN_DIR${NC}"
    exit 1
fi
echo -e "${GREEN}✓${NC} sqlgen directory exists"

echo -e "\n${YELLOW}[Step 2/5]${NC} Initializing vcpkg (if needed)..."
if [ ! -f "$SQLGEN_DIR/vcpkg/vcpkg" ]; then
    echo "Initializing vcpkg..."
    cd "$SQLGEN_DIR"
    git submodule update --init --recursive
    if [ ! -f "./vcpkg/bootstrap-vcpkg.sh" ]; then
        git clone https://github.com/microsoft/vcpkg.git vcpkg
    fi
    ./vcpkg/bootstrap-vcpkg.sh
    cd "$PROJECT_DIR"
    echo -e "${GREEN}✓${NC} vcpkg initialization complete"
else
    echo -e "${GREEN}✓${NC} vcpkg already initialized"
fi

echo -e "\n${YELLOW}[Step 3/5]${NC} Configuring build options..."

# Default options
BUILD_TYPE="${BUILD_TYPE:-Release}"
ENABLE_MYSQL="${ENABLE_MYSQL:-OFF}"
ENABLE_POSTGRES="${ENABLE_POSTGRES:-OFF}"
ENABLE_SQLITE="${ENABLE_SQLITE:-ON}"
BUILD_DIR="${BUILD_DIR:-build}"
CLEAN_BUILD="${CLEAN_BUILD:-no}"
ENABLE_COVERAGE="${ENABLE_COVERAGE:-ON}"

# If coverage is enabled, force Debug mode
if [ "$ENABLE_COVERAGE" = "ON" ] || [ "$ENABLE_COVERAGE" = "1" ] || [ "$ENABLE_COVERAGE" = "yes" ]; then
    ENABLE_COVERAGE="ON"
    BUILD_TYPE="Debug"
    echo -e "${YELLOW}Note: Coverage enabled, automatically switching to Debug mode${NC}"
fi

echo "  Build type: $BUILD_TYPE"
echo "  MySQL support: $ENABLE_MYSQL"
echo "  PostgreSQL support: $ENABLE_POSTGRES"
echo "  SQLite support: $ENABLE_SQLITE"
echo "  Build directory: $BUILD_DIR"
echo "  Clean rebuild: $CLEAN_BUILD"
echo "  Code coverage: $ENABLE_COVERAGE"

# If clean build is needed
if [ "$CLEAN_BUILD" = "yes" ] || [ "$CLEAN_BUILD" = "1" ]; then
    if [ -d "$PROJECT_DIR/$BUILD_DIR" ]; then
        echo -e "${YELLOW}Cleaning old build directory...${NC}"
        rm -rf "$PROJECT_DIR/$BUILD_DIR"
        echo -e "${GREEN}✓${NC} Build directory cleaned"
    fi
fi

echo -e "\n${YELLOW}[Step 4/5]${NC} Running CMake configuration..."
export CC=gcc
export CXX=g++
cmake -S "$PROJECT_DIR" -B "$PROJECT_DIR/$BUILD_DIR" \
    -G "Unix Makefiles" \
    -DCMAKE_MAKE_PROGRAM="$(command -v make)" \
    -DCMAKE_C_COMPILER="$(command -v gcc)" \
    -DCMAKE_CXX_COMPILER="$(command -v g++)" \
    -DCMAKE_CXX_STANDARD=20 \
    -DCMAKE_BUILD_TYPE="$BUILD_TYPE" \
    -DSQLGEN_MYSQL="$ENABLE_MYSQL" \
    -DSQLGEN_POSTGRES="$ENABLE_POSTGRES" \
    -DSQLGEN_SQLITE3="$ENABLE_SQLITE" \
    -DENABLE_COVERAGE="$ENABLE_COVERAGE"

echo -e "${GREEN}✓${NC} CMake configuration complete"

# echo -e "\n${YELLOW}[Step 5/5]${NC} Compiling project..."
# cmake --build "$PROJECT_DIR/$BUILD_DIR" -j "$(nproc 2>/dev/null || sysctl -n hw.ncpu 2>/dev/null || echo 4)"

# echo -e "\n${GREEN}========================================${NC}"
# echo -e "${GREEN}Build successful!${NC}"
# echo -e "${GREEN}========================================${NC}"

# List generated executables
# echo -e "\nGenerated executables:"
# find "$PROJECT_DIR/$BUILD_DIR" -maxdepth 1 -type f -executable -exec basename {} \; 2>/dev/null || \
# find "$PROJECT_DIR/$BUILD_DIR" -maxdepth 1 -type f -perm +111 -exec basename {} \; 2>/dev/null || \
# echo "  example_test (expected)"

# echo -e "\nRun example test:"
# echo -e "  ${YELLOW}cd $PROJECT_DIR${NC}"
# echo -e "  ${YELLOW}./$BUILD_DIR/example_test${NC}"

# echo -e "\nUsage help:"
# echo -e "  Set environment variables to customize build:"
# echo -e "    ${YELLOW}BUILD_TYPE=Debug ./build.sh${NC}          # Debug build"
# echo -e "    ${YELLOW}ENABLE_MYSQL=ON ./build.sh${NC}           # Enable MySQL"
# echo -e "    ${YELLOW}ENABLE_POSTGRES=ON ./build.sh${NC}        # Enable PostgreSQL"
# echo -e "    ${YELLOW}BUILD_DIR=my_build ./build.sh${NC}        # Custom build directory"
# echo -e "    ${YELLOW}CLEAN_BUILD=yes ./build.sh${NC}           # Clean and rebuild"
# echo -e "    ${YELLOW}ENABLE_COVERAGE=ON CLEAN_BUILD=yes ./build.sh${NC}  # Enable code coverage"

# echo -e "\n${RED}Starting tests...${NC}"
# cd build
# ctest --output-on-failure

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
