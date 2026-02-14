cmake_minimum_required(VERSION 3.15)

# ============================================
# 重要：必须在 project() 之前设置相关配置
# ============================================
set(REACTION_ROOT_DIR "/data/workspace/Private-Model-Evaluation-reaction/third_patry_project/reaction")

# 配置本项目选项
option(BUILD_TESTS "Build test cases" ON)

project(reaction_test_cases VERSION 1.0.0 LANGUAGES CXX)

# ============================================
# 设置 C++ 标准为 C++20（Reaction 需要 C++20）
# ============================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ============================================
# 集成 Reaction 库（header-only 库）
# ============================================
# 方式 1: 直接包含头文件目录（推荐 - 最简单）
set(REACTION_INCLUDE_DIR "${REACTION_ROOT_DIR}/include")

if(EXISTS "${REACTION_INCLUDE_DIR}/reaction/reaction.h")
    message(STATUS "Found Reaction at: ${REACTION_ROOT_DIR}")
    message(STATUS "Using Reaction headers from: ${REACTION_INCLUDE_DIR}")
    include_directories(${REACTION_INCLUDE_DIR})
else()
    message(FATAL_ERROR "Cannot find reaction.h at ${REACTION_INCLUDE_DIR}/reaction")
endif()

# ============================================
# 其他集成方式（可选）
# ============================================
# 方式 2: 使用 add_subdirectory（完整集成）
# add_subdirectory(${REACTION_ROOT_DIR} ${CMAKE_BINARY_DIR}/reaction)
# target_link_libraries(your_target PRIVATE reaction::reaction)
#
# 方式 3: 使用 find_package（需要先安装 Reaction）
# find_package(reaction REQUIRED)
# target_link_libraries(your_target PRIVATE reaction::reaction)

# ============================================
# 配置头文件包含目录
# ============================================
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# ============================================
# 编译器警告选项
# ============================================
if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

# ============================================
# 使用 GTest 构建单元测试
# ============================================
# ============================================
# Test Configuration
# ============================================

# Macro to add a reaction test
macro(add_reaction_test TEST_NAME)
    add_executable(${TEST_NAME} tests/${TEST_NAME}.cpp)
    target_link_libraries(${TEST_NAME} PRIVATE GTest::gtest GTest::gtest_main)
    target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endmacro()

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
    
    # add tests
    add_reaction_test(tests)
endif()

# ============================================
# 打印配置信息
# ============================================
message(STATUS "====================================")
message(STATUS "Project: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Reaction Root: ${REACTION_ROOT_DIR}")
message(STATUS "Reaction Include: ${REACTION_INCLUDE_DIR}")
message(STATUS "BUILD_TESTS: ${BUILD_TESTS}")
message(STATUS "====================================")

