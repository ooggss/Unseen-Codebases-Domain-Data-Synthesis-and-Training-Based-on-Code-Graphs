# 构建说明

## Reaction 测试用例构建详细指南

本文档提供了构建 Reaction 测试用例项目的详细说明。

---

## 📋 系统要求

### 必需组件

| 组件 | 最低版本 | 推荐版本 | 说明 |
|------|---------|---------|------|
| CMake | 3.15 | 3.25+ | 构建系统生成器 |
| GCC | 10.0 | 12.0+ | 或其他 C++20 兼容编译器 |
| Clang | 12.0 | 15.0+ | 可选编译器 |
| MSVC | 19.30 | 最新 | Windows 平台 |

### 可选组件

- **GTest**: 单元测试框架（如果系统未安装，CMake 会自动下载）
- **Ninja**: 更快的构建工具（可选，替代 make）

---

## 🚀 快速构建

### Linux / macOS

```bash
# 1. 进入项目目录
cd /data/workspace/Private-Model-Evaluation/evaluation/reaction/test_cases

# 2. 使用构建脚本
chmod +x build.sh
./build.sh

# 3. 查看测试结果
# 测试会自动运行
```

### Windows

```powershell
# 1. 进入项目目录
cd C:\path\to\Private-Model-Evaluation\evaluation\reaction\test_cases

# 2. 创建构建目录
mkdir build
cd build

# 3. 配置项目
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON

# 4. 编译
cmake --build . --config Release

# 5. 运行测试
ctest -C Release --output-on-failure
```

---

## 🔧 详细构建步骤

### 步骤 1: 配置 CMake

```bash
# 创建独立的构建目录
mkdir -p build && cd build

# 基本配置
cmake .. -DCMAKE_BUILD_TYPE=Release

# 启用测试
cmake .. -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON

# 使用 Ninja（更快）
cmake .. -G Ninja -DCMAKE_BUILD_TYPE=Release -DBUILD_TESTS=ON

# 指定编译器
cmake .. -DCMAKE_CXX_COMPILER=g++-12 -DCMAKE_BUILD_TYPE=Release
```

### 步骤 2: 编译项目

```bash
# 使用所有 CPU 核心编译
cmake --build . -j$(nproc)

# 或者指定核心数
cmake --build . -j8

# Windows
cmake --build . --config Release -j8
```

### 步骤 3: 运行测试

```bash
# 运行所有测试
ctest --output-on-failure

# 详细输出
ctest -V

# 运行特定测试
ctest -R BasicTest

# 并行运行测试
ctest -j$(nproc)
```

---

## 🔬 CMake 配置选项

### 构建类型

| 选项 | 说明 |
|------|------|
| `-DCMAKE_BUILD_TYPE=Debug` | 调试版本，包含符号 |
| `-DCMAKE_BUILD_TYPE=Release` | 发布版本，优化性能 |
| `-DCMAKE_BUILD_TYPE=RelWithDebInfo` | 带调试信息的发布版本 |
| `-DCMAKE_BUILD_TYPE=MinSizeRel` | 最小体积发布版本 |

### 项目选项

| 选项 | 默认值 | 说明 |
|------|--------|------|
| `-DBUILD_TESTS=ON/OFF` | ON | 是否构建测试 |

### Reaction 库路径配置

如果 Reaction 库不在默认位置，可以通过以下方式指定：

```bash
# 方式 1: 修改 CMakeLists.txt 中的 REACTION_ROOT_DIR

# 方式 2: 使用 CMake 变量
cmake .. -DREACTION_ROOT_DIR=/path/to/reaction

# 方式 3: 使用环境变量
export REACTION_ROOT=/path/to/reaction
cmake ..
```

---

## 🐛 故障排除

### 问题 1: 找不到 Reaction 头文件

**错误信息:**
```
CMake Error: Cannot find reaction.h at /path/to/reaction/include/reaction
```

**解决方案:**
1. 检查 Reaction 库路径是否正确
2. 确认 `reaction.h` 文件存在于 `include/reaction/` 目录
3. 修改 `CMakeLists.txt` 中的 `REACTION_ROOT_DIR` 路径

### 问题 2: C++20 编译器支持

**错误信息:**
```
error: requested standard 'c++20' is not supported
```

**解决方案:**
1. 升级编译器到支持 C++20 的版本
2. GCC: `sudo apt install g++-12`
3. Clang: `sudo apt install clang-15`

### 问题 3: GTest 下载失败

**错误信息:**
```
Could not download googletest from GitHub
```

**解决方案:**
1. 检查网络连接
2. 手动安装 GTest:
   ```bash
   # Ubuntu/Debian
   sudo apt install libgtest-dev
   
   # macOS
   brew install googletest
   ```
3. 或使用代理下载

### 问题 4: 权限问题

**错误信息:**
```
Permission denied: build.sh
```

**解决方案:**
```bash
chmod +x build.sh
```

---

## 📊 构建输出

成功构建后，您应该看到类似以下的输出：

```
======================================
Building Reaction Test Cases
======================================
Configuring with CMake...
-- Found Reaction at: /path/to/reaction
-- Using Reaction headers from: /path/to/reaction/include
-- Building tests with GTest
...
Building...
[100%] Built target test_reaction_basic
======================================
Running Tests
======================================
Test project /path/to/build
    Start 1: test_reaction_basic
1/1 Test #1: test_reaction_basic ..........   Passed    0.02 sec

100% tests passed, 0 tests failed out of 1
======================================
Build and Test Completed Successfully!
======================================
```

---

## 🔍 验证构建

### 检查生成的可执行文件

```bash
# Linux/macOS
ls -lh build/test_reaction_basic

# 运行测试程序
./build/test_reaction_basic

# 查看详细测试输出
./build/test_reaction_basic --gtest_list_tests
./build/test_reaction_basic --gtest_filter=ReactionBasicTest.*
```

### 检查依赖项

```bash
# Linux
ldd build/test_reaction_basic

# macOS
otool -L build/test_reaction_basic
```

---

## 🎯 最佳实践

1. **使用独立构建目录**: 始终使用 `build/` 目录，不要在源码目录中构建
2. **并行编译**: 使用 `-j$(nproc)` 加速编译
3. **清理构建**: 定期清理构建目录 `rm -rf build`
4. **版本控制**: 不要将 `build/` 目录添加到 Git

---

## 📚 相关文档

- [CMake 官方文档](https://cmake.org/documentation/)
- [GTest 文档](https://google.github.io/googletest/)
- [Reaction 项目文档](../../../third_patry_project/reaction/README.zh-CN.md)

---

## 💡 提示

- 首次构建可能需要下载 GTest，请耐心等待
- Release 版本的性能比 Debug 版本快得多
- 使用 `ccache` 可以加速重复编译
- 推荐使用 Ninja 构建系统以获得更快的构建速度

