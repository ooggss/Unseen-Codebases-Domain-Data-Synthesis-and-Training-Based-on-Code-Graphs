# sqlgen 测试用例项目构建指南

## 项目结构

```
test_cases/
├── CMakeLists.txt       # CMake 配置文件
├── example_test.cpp     # 示例测试程序
└── BUILD.md            # 本文件
```

## 前置要求

1. **CMake** >= 3.23
2. **C++ 编译器**支持 C++20：
   - GCC >= 11
   - Clang >= 14
   - MSVC >= 17
3. **sqlgen 依赖**（会自动通过 vcpkg 下载）：
   - reflect-cpp
   - PostgreSQL (可选)
   - SQLite3 (默认启用)
   - MySQL/MariaDB (可选)

## 构建步骤

```bash
./build.sh
```

