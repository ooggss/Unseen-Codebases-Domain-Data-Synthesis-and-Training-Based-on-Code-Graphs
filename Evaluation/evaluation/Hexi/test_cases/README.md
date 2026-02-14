# Hexi 库集成示例

这是一个完整的示例项目，展示如何在 CMake 项目中集成和使用 Hexi 二进制流处理库。

## 快速开始

### 一键构建和测试

```bash
./build.sh
```

### 手动构建

```bash
mkdir build && cd build
cmake ..
cmake --build .
ctest --output-on-failure
```

## 文件说明

| 文件 | 说明 |
|------|------|
| `CMakeLists.txt` | CMake 配置文件，展示如何集成 Hexi 库 |
| `tests/test_basic.cpp` | 完整的测试用例，涵盖 Hexi 的主要功能 |
| `build.sh` | 自动化构建脚本 |
| `BUILD.md` | 详细的构建说明和使用指南 |

## 主要特性演示

本项目的测试用例涵盖了 Hexi 的以下功能：

1. ✅ **基本的序列化和反序列化** - 简单结构体的读写
2. ✅ **自定义序列化函数** - 为复杂类型定义序列化逻辑
3. ✅ **字节序处理** - 大端序和小端序转换
4. ✅ **错误处理** - 安全的缓冲区溢出检测
5. ✅ **字符串处理** - null 终止字符串的读写
6. ✅ **容器序列化** - vector 等 STL 容器的处理

## CMakeLists.txt 核心配置

### 1. 设置 Hexi 源码路径

```cmake
set(HEXI_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../third_patry_project/Hexi")
```

### 2. 设置 C++23 标准

```cmake
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
```

### 3. 添加 Hexi 作为子项目

```cmake
add_subdirectory(${HEXI_SOURCE_DIR} ${CMAKE_BINARY_DIR}/hexi)
```

### 4. 链接 Hexi 库

```cmake
target_link_libraries(test_hexi_basic PRIVATE hexi)
```

## 代码示例

### 简单使用

```cpp
#include <hexi/hexi.h>  // 使用 add_subdirectory 方式
#include <vector>

// 定义数据结构
struct Message {
    uint32_t id;
    uint64_t timestamp;
};

// 序列化
std::vector<uint8_t> buffer;
hexi::buffer_adaptor adaptor(buffer);
hexi::binary_stream stream(adaptor, hexi::endian::little);

Message msg{123, 1700000000};
stream << msg;

// 反序列化
Message decoded;
stream >> decoded;
```

### 自定义序列化

```cpp
struct Packet {
    uint32_t id;
    std::string data;
    
    auto& operator<<(auto& stream) const {
        stream << id << hexi::null_terminated(data);
        return stream;
    }
    
    auto& operator>>(auto& stream) {
        stream >> id >> hexi::null_terminated(data);
        return stream;
    }
};
```

## 系统要求

- **CMake**: 3.23+
- **编译器**: 
  - GCC 13+
  - Clang 17+
  - MSVC 17+ (Visual Studio 2022)
- **C++ 标准**: C++23

## 更多信息

详细的构建说明和故障排除，请参阅 [BUILD.md](BUILD.md)。

## 许可证

Hexi 采用 MIT 和 Apache 2.0 双重许可。

