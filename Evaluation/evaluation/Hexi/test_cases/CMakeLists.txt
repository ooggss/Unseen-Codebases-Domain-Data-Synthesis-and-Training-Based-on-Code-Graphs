cmake_minimum_required(VERSION 3.23)

# ============================================
# 重要：必须在 project() 之前设置相关配置
# ============================================
set(HEXI_ROOT_DIR "/data/workspace/Private-Model-Evaluation-hexi/third_patry_project/Hexi")

# 配置本项目选项
option(BUILD_TESTS "Build test cases" ON)

project(hexi_test_cases VERSION 1.0.0 LANGUAGES CXX)

# ============================================
# 设置 C++ 标准为 C++23（Hexi 需要 C++23）
# ============================================
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_compile_options(-w)

# ============================================
# 集成 Hexi 库（使用 single_include 方式 - 最简单）
# ============================================
# Hexi 是 header-only 库，直接包含 single_include 目录
set(HEXI_INCLUDE_DIR "${HEXI_ROOT_DIR}/include")

if(EXISTS "${HEXI_INCLUDE_DIR}/hexi/hexi.h")
    message(STATUS "Found Hexi at: ${HEXI_ROOT_DIR}")
    message(STATUS "Using Hexi single header from: ${HEXI_INCLUDE_DIR}")
    include_directories(${HEXI_INCLUDE_DIR})
else()
    message(FATAL_ERROR "Cannot find hexi.h at ${HEXI_INCLUDE_DIR}")
endif()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# ============================================
# 使用 GTest 构建单元测试
# ============================================
if(BUILD_TESTS)
    enable_testing()
    
    # 查找或获取 GTest 包
    find_package(GTest QUIET)
    
    if(NOT GTest_FOUND)
        message(STATUS "GTest not found, fetching from GitHub...")
        include(FetchContent)
        FetchContent_Declare(
            googletest
            URL https://github.com/google/googletest/releases/download/v1.16.0/googletest-1.16.0.tar.gz
            URL_HASH SHA512=bec8dad2a5abbea8e9e5f0ceedd8c9dbdb8939e9f74785476b0948f21f5db5901018157e78387e106c6717326558d6642fc0e39379c62af57bf1205a9df8a18b
        )
        set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
        FetchContent_MakeAvailable(googletest)
    endif()
    
    message(STATUS "Building tests with GTest")
    
    # 测试可执行文件：test_hexi_basic
    add_executable(tests
        tests/tests.cpp
    )
    
    # 链接库：GTest（Hexi 是 header-only，无需链接）
    target_link_libraries(tests PRIVATE 
        GTest::gtest
        GTest::gtest_main
    )
    
    # 添加包含目录
    target_include_directories(tests PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    )
    
    # 注册测试到 CTest
    add_test(NAME tests COMMAND tests)
    
    # 如果需要添加更多测试用例：
    # add_executable(test_hexi_advanced tests/test_advanced.cpp)
    # target_link_libraries(test_hexi_advanced PRIVATE hexi GTest::gtest GTest::gtest_main)
    # target_include_directories(test_hexi_advanced PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    # add_test(NAME test_hexi_advanced COMMAND test_hexi_advanced)
endif()

