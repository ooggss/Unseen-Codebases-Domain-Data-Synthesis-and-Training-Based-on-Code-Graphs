# Hexi 测试用例构建说明

本项目演示如何在 CMake 项目中集成和使用 Hexi 库。

## 前置要求

- CMake 3.23 或更高版本
- 支持 C++23 的编译器：
  - GCC 13+
  - Clang 17+
  - MSVC 17+

## 项目结构

```
test_cases/
├── CMakeLists.txt          # CMake 配置文件
├── BUILD.md                # 本文件
├── include/                # 项目头文件目录
├── tests/                  # 测试文件目录
│   └── test_basic.cpp      # 基本测试用例
└── build/                  # 构建目录（自动生成）
```

## 构建步骤

### 1. 创建构建目录

```bash
mkdir -p build
cd build
```

### 2. 配置 CMake

```bash
cmake ..
```

如果要禁用测试构建：

```bash
cmake .. -DBUILD_TESTS=OFF
```

### 3. 编译项目

```bash
cmake --build .
```

或使用 make：

```bash
make
```

### 4. 运行测试

```bash
ctest --output-on-failure
```

或直接运行测试可执行文件：

```bash
./test_hexi_basic
```

## CMake 集成 Hexi 的三种方式

### 方式 1: 使用 add_subdirectory（推荐，已在 CMakeLists.txt 中实现）

```cmake
set(HEXI_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../third_patry_project/Hexi")
add_subdirectory(${HEXI_SOURCE_DIR} ${CMAKE_BINARY_DIR}/hexi)

# 在可执行文件中链接
target_link_libraries(your_target PRIVATE hexi)
```

然后在代码中使用：
```cpp
#include <hexi/hexi.h>  // 注意：使用 hexi/hexi.h 路径
```

**优点**：
- 完全集成到 CMake 构建系统
- 自动处理依赖关系
- 支持 IDE 跳转和智能提示

### 方式 2: 直接包含 single_include 目录

```cmake
include_directories(${HEXI_SOURCE_DIR}/single_include)
```

然后在代码中：
```cpp
#include <hexi.h>
```

**优点**：
- 简单快速
- 单个头文件，编译更快

### 方式 3: 包含完整的 include 目录

```cmake
include_directories(${HEXI_SOURCE_DIR}/include)
```

然后在代码中：
```cpp
#include <hexi/hexi.h>
// 或者单独包含需要的头文件
#include <hexi/binary_stream.h>
#include <hexi/buffer_adaptor.h>
```

**优点**：
- 可以按需包含特定模块
- 编译时间可能更短（如果只使用部分功能）

## 使用示例

### 基本的序列化和反序列化

```cpp
#include <hexi/hexi.h>  // 使用 add_subdirectory 方式
// 或者
// #include <hexi.h>    // 使用 single_include 方式

#include <vector>
#include <cstdint>

struct Packet {
    uint32_t id;
    uint64_t timestamp;
};

// 序列化
std::vector<uint8_t> buffer;
hexi::buffer_adaptor adaptor(buffer);
hexi::binary_stream stream(adaptor, hexi::endian::little);

Packet packet{123, 1700000000};
stream << packet;

// 反序列化
hexi::buffer_adaptor read_adaptor(buffer);
hexi::binary_stream read_stream(read_adaptor, hexi::endian::little);

Packet decoded;
read_stream >> decoded;
```

### 带有自定义序列化的结构体

```cpp
struct UserData {
    uint32_t id;
    std::string name;
    
    // 序列化
    auto& operator<<(auto& stream) const {
        stream << id << hexi::null_terminated(name);
        return stream;
    }
    
    // 反序列化
    auto& operator>>(auto& stream) {
        stream >> id >> hexi::null_terminated(name);
        return stream;
    }
};
```

## 编译器支持

### GCC

```bash
cmake .. -DCMAKE_CXX_COMPILER=g++-13
cmake --build .
```

### Clang

```bash
cmake .. -DCMAKE_CXX_COMPILER=clang++-17
cmake --build .
```

## 常见问题

### 1. 编译器不支持 C++23

确保您的编译器版本足够新：
- GCC 13 或更高
- Clang 17 或更高
- MSVC 2022 (17.0) 或更高

### 2. 找不到 Hexi 源码

检查 `CMakeLists.txt` 中的 `HEXI_SOURCE_DIR` 路径是否正确：

```cmake
set(HEXI_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../third_patry_project/Hexi")
```

### 3. GTest 相关错误

项目会自动从 GitHub 下载 GTest。如果网络有问题，可以手动安装 GTest 或禁用测试：

```bash
cmake .. -DBUILD_TESTS=OFF
```

## 参考资源

- [Hexi GitHub 仓库](https://github.com/EmberEmu/hexi)
- [Hexi 文档](https://github.com/EmberEmu/hexi/tree/main/docs)
- 示例代码：`tests/test_basic.cpp`

## 许可证

Hexi 采用 MIT 和 Apache 2.0 双重许可。您可以选择您偏好的许可证使用。

