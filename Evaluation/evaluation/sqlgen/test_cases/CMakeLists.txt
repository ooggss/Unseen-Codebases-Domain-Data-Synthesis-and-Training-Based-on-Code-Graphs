cmake_minimum_required(VERSION 3.23)

# ============================================
# 重要：必须在 project() 之前设置 vcpkg toolchain 和 features
# ============================================
set(SQLGEN_SOURCE_DIR "/data/workspace/Private-Model-Evaluation-sqlgen/third_patry_project/sqlgen")
# set(SQLGEN_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../third_patry_project/sqlgen")

# 配置 sqlgen 选项（根据需要启用/禁用）
option(SQLGEN_MYSQL "Enable MySQL support" OFF)
option(SQLGEN_POSTGRES "Enable PostgreSQL support" OFF)
option(SQLGEN_SQLITE3 "Enable SQLite3 support" ON)
option(SQLGEN_BUILD_TESTS "Build sqlgen tests" OFF)
option(SQLGEN_BUILD_SHARED "Build shared library" OFF)

# 配置本项目选项
option(BUILD_TESTS "Build test cases" ON)
option(ENABLE_COVERAGE "Enable code coverage" OFF)

# 设置 vcpkg manifest features（必须在 project() 之前）
if(SQLGEN_MYSQL)
    list(APPEND VCPKG_MANIFEST_FEATURES "mysql")
endif()

if(SQLGEN_POSTGRES)
    list(APPEND VCPKG_MANIFEST_FEATURES "postgres")
endif()

if(SQLGEN_SQLITE3)
    list(APPEND VCPKG_MANIFEST_FEATURES "sqlite3")
endif()

# 如果启用测试，添加 tests feature（包含 GTest）
if(BUILD_TESTS)
    list(APPEND VCPKG_MANIFEST_FEATURES "tests")
endif()

# 设置 vcpkg manifest 目录指向 sqlgen 项目
set(VCPKG_MANIFEST_DIR "${SQLGEN_SOURCE_DIR}" CACHE STRING "vcpkg manifest directory")

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "${SQLGEN_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
    message(STATUS "Setting vcpkg toolchain: ${CMAKE_TOOLCHAIN_FILE}")
endif()

project(sqlgen_test_cases VERSION 1.0.0 LANGUAGES CXX)

# 设置 C++ 标准为 C++20（sqlgen 需要）
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================
# 代码覆盖率配置
# ============================================
if(ENABLE_COVERAGE)
    message(STATUS "Code coverage enabled")
    # 添加覆盖率编译和链接标志
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -fprofile-arcs -ftest-coverage")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
endif()

# ============================================
# 方法 1: 使用 add_subdirectory 引入 sqlgen
# ============================================
# sqlgen 选项已经在前面定义了

# 添加 sqlgen 子目录
# SQLGEN_SOURCE_DIR 已经在前面定义了
if(EXISTS "${SQLGEN_SOURCE_DIR}/CMakeLists.txt")
    message(STATUS "Found sqlgen at: ${SQLGEN_SOURCE_DIR}")
    add_subdirectory(${SQLGEN_SOURCE_DIR} ${CMAKE_BINARY_DIR}/sqlgen)
else()
    message(FATAL_ERROR "Cannot find sqlgen at ${SQLGEN_SOURCE_DIR}")
endif()

# ============================================
# 配置头文件包含目录
# ============================================
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# ============================================
# 使用 GTest 构建单元测试
# ============================================
if(BUILD_TESTS)
    enable_testing()
    
    # 查找 GTest 包
    find_package(GTest CONFIG REQUIRED)
    
    message(STATUS "Building tests with GTest")
    
    # 测试可执行文件：test_aggregations
    add_executable(test_aggregations tests/tests.cpp)
    
    # 链接库：sqlgen + GTest
    target_link_libraries(test_aggregations PRIVATE 
        sqlgen
        GTest::gtest
        GTest::gtest_main
    )
    
    # 添加包含目录
    target_include_directories(test_aggregations PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    
    # 注册测试到 CTest
    add_test(NAME test_aggregations COMMAND test_aggregations)
    

endif()

# ============================================
# 打印配置信息
# ============================================
message(STATUS "====================================")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "SQLGEN_MYSQL: ${SQLGEN_MYSQL}")
message(STATUS "SQLGEN_POSTGRES: ${SQLGEN_POSTGRES}")
message(STATUS "SQLGEN_SQLITE3: ${SQLGEN_SQLITE3}")
message(STATUS "BUILD_TESTS: ${BUILD_TESTS}")
message(STATUS "ENABLE_COVERAGE: ${ENABLE_COVERAGE}")
message(STATUS "====================================")
