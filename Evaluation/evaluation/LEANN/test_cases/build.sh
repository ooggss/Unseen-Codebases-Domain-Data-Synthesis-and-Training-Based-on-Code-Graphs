#!/bin/bash

# LEANN Test Cases Build Script

set -e  # Exit on error

# Color output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

echo -e "${GREEN}========================================${NC}"
echo -e "${GREEN}LEANN Test Cases Build Script${NC}"
echo -e "${GREEN}========================================${NC}"

# Get project root directory
PROJECT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"

echo -e "\n${YELLOW}[Step 1/4]${NC} Checking Python environment..."
if ! command -v python3 &> /dev/null; then
    echo -e "${RED}Error: python3 not found${NC}"
    exit 1
fi
PYTHON_VERSION=$(python3 --version 2>&1 | awk '{print $2}')
echo -e "${GREEN}✓${NC} Python version: $PYTHON_VERSION"

echo -e "\n${YELLOW}[Step 2/4]${NC} Checking dependencies..."
if [ -f "$PROJECT_DIR/requirements.txt" ]; then
    # Check and fix NumPy version compatibility issue (PyTorch and FAISS require NumPy 1.x)
    echo "Checking NumPy version compatibility..."
    if python3 -c "import numpy" 2>/dev/null; then
        NUMPY_VERSION=$(python3 -c "import numpy; print(numpy.__version__)" 2>/dev/null)
        echo "Current NumPy version: $NUMPY_VERSION"
        
        # Check if NumPy 2.x (will cause "Numpy is not available" error)
        MAJOR_VERSION=$(python3 -c "import numpy; print(numpy.__version__.split('.')[0])" 2>/dev/null)
        if [ "$MAJOR_VERSION" = "2" ]; then
            echo -e "${YELLOW}Detected NumPy 2.x version, PyTorch and FAISS require NumPy 1.x${NC}"
            echo "Downgrading NumPy to 1.x version (this may take a few minutes)..."
            python3 -m pip install --upgrade "numpy>=1.20.0,<2.0.0" --force-reinstall --no-cache-dir || {
                echo -e "${RED}Error: NumPy downgrade failed, please manually run: pip install 'numpy>=1.20.0,<2.0.0' --force-reinstall${NC}"
                exit 1
            }
            echo -e "${GREEN}✓${NC} NumPy downgraded"
        else
            echo "NumPy version compatible (1.x)"
        fi
    else
        echo "NumPy not installed, will be installed with dependencies..."
    fi
    
    echo "Installing dependencies..."
    python3 -m pip install -q -r "$PROJECT_DIR/requirements.txt" || {
        echo -e "${YELLOW}Warning: Some dependencies failed to install, trying to continue...${NC}"
    }
    echo -e "${GREEN}✓${NC} Dependency check complete"
else
    echo -e "${YELLOW}Warning: requirements.txt not found${NC}"
fi

echo -e "\n${YELLOW}[Step 3/4]${NC} Verifying file structure..."
if [ ! -d "$PROJECT_DIR/include" ]; then
    echo -e "${RED}Error: include directory not found${NC}"
    exit 1
fi
if [ ! -d "$PROJECT_DIR/tests" ]; then
    echo -e "${RED}Error: tests directory not found${NC}"
    exit 1
fi
echo -e "${GREEN}✓${NC} File structure correct"

echo -e "\n${YELLOW}[Step 4/4]${NC} Running tests..."

# Add include directory to PYTHONPATH
export PYTHONPATH="$PROJECT_DIR/include:$PYTHONPATH"

# Set OpenMP and PyTorch related environment variables to avoid crashes (especially on macOS)
export OMP_NUM_THREADS=1
export MKL_NUM_THREADS=1
export KMP_DUPLICATE_LIB_OK=TRUE
export KMP_BLOCKTIME=0
export TOKENIZERS_PARALLELISM=false
export OMP_DISPLAY_ENV=FALSE

# Verify NumPy availability (solve "Numpy is not available" error)
echo -e "\n${YELLOW}Verifying NumPy availability...${NC}"
python3 -c "
import numpy as np
print(f'NumPy version: {np.__version__}')
print('NumPy is available: ✓')
" || {
    echo -e "${RED}Error: NumPy not available, please ensure it is properly installed${NC}"
    exit 1
}

# Run pytest
cd "$PROJECT_DIR"

# Check if specific test case is specified (parameter format: case1, case2, ... or test_case1, test_case2, ...)
if [ -n "$1" ]; then
    # Process parameter, ensure format is test_case{N}
    TEST_CASE="$1"
    if [[ ! "$TEST_CASE" =~ ^test_ ]]; then
        TEST_CASE="test_$TEST_CASE"
    fi
    TEST_FILE="tests/${TEST_CASE}.py"
    
    if [ -f "$TEST_FILE" ]; then
        echo -e "${GREEN}Running specified test: $TEST_FILE${NC}"
        python3 -m pytest "$TEST_FILE" -v --tb=short
    else
        echo -e "${RED}Error: Test file does not exist: $TEST_FILE${NC}"
        exit 1
    fi
else
    # Run all tests
    python3 -m pytest tests/ -v --tb=short
fi

echo -e "\n${GREEN}========================================${NC}"
echo -e "${GREEN}Tests complete!${NC}"
echo -e "${GREEN}========================================${NC}"

