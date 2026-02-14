# Reaction 测试用例项目

这是一个用于测试 Reaction 响应式编程框架的示例项目。

## 项目结构

```
reaction/test_cases/
├── CMakeLists.txt          # CMake 构建配置文件
├── build.sh                # 构建脚本
├── README.md               # 本文件
├── BUILD.md                # 详细构建说明
├── include/                # 项目头文件目录
└── tests/                  # 测试源文件目录
    └── test_basic.cpp      # 基础功能测试
```

## 快速开始

### 前置要求

- C++20 兼容的编译器（GCC 10+, Clang 12+, MSVC 19.30+）
- CMake 3.15 或更高版本
- 可选：GTest（会自动下载）

### 构建和运行测试

使用提供的构建脚本：

```bash
# 方式 1: 使用构建脚本（推荐）
chmod +x build.sh
./build.sh

# 清理并重新构建
./build.sh clean

# 方式 2: 手动使用 CMake
mkdir -p build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON
cmake --build . -j$(nproc)
ctest --output-on-failure
```

## CMake 集成方式

本项目演示了如何将 Reaction 作为第三方库集成到您的项目中。主要有以下几种方式：

### 方式 1: 直接包含头文件（推荐 - 最简单）

```cmake
set(REACTION_ROOT_DIR "/path/to/reaction")
set(REACTION_INCLUDE_DIR "${REACTION_ROOT_DIR}/include")
include_directories(${REACTION_INCLUDE_DIR})
```

### 方式 2: 使用 add_subdirectory

```cmake
add_subdirectory(/path/to/reaction ${CMAKE_BINARY_DIR}/reaction)
target_link_libraries(your_target PRIVATE reaction::reaction)
```

### 方式 3: 使用 find_package（需要先安装）

```cmake
find_package(reaction REQUIRED)
target_link_libraries(your_target PRIVATE reaction::reaction)
```

## 代码示例

```cpp
#include <reaction/reaction.h>
#include <iostream>

int main() {
    using namespace reaction;
    
    // 创建响应式变量
    auto a = var(10);
    auto b = var(20);
    
    // 创建派生计算
    auto sum = calc([&]() {
        return a() + b();
    });
    
    // 创建响应式动作
    auto logger = action([&]() {
        std::cout << "Sum: " << sum() << std::endl;
    });
    
    // 修改变量，自动触发更新
    a.value(15);  // 输出: Sum: 35
    b.value(25);  // 输出: Sum: 40
    
    return 0;
}
```

## 测试内容

- ✅ 基本响应式变量操作
- ✅ 计算表达式（calc）
- ✅ 声明式表达式（expr）
- ✅ 响应式动作（action）
- ✅ 链式依赖
- ✅ 字符串操作
- ✅ 数学运算
- ✅ 参数绑定

## 相关资源

- [Reaction GitHub 仓库](https://github.com/lumia431/reaction)
- [Reaction 中文文档](../../../third_patry_project/reaction/README.zh-CN.md)
- [Reaction 英文文档](../../../third_patry_project/reaction/README.md)

## 许可证

请参阅 Reaction 项目的 LICENSE 文件。

