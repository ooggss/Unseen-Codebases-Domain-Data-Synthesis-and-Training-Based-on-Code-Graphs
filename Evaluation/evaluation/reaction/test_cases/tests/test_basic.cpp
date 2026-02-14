#include <reaction/reaction.h>
#include <gtest/gtest.h>
#include <string>
#include <cmath>

// 测试基本的响应式变量
TEST(ReactionBasicTest, VarBasicOperations) {
    using namespace reaction;
    
    // 创建响应式变量
    auto a = var(10);
    auto b = var(20);
    
    // 测试初始值
    EXPECT_EQ(a.get(), 10);
    EXPECT_EQ(b.get(), 20);
    
    // 测试赋值
    a.value(15);
    EXPECT_EQ(a.get(), 15);
    
    // 测试使用 () 运算符获取值
    EXPECT_EQ(a(), 15);
    EXPECT_EQ(b(), 20);
}

// 测试计算表达式
TEST(ReactionBasicTest, CalcExpression) {
    using namespace reaction;
    
    auto a = var(10);
    auto b = var(20);
    
    // 使用 calc 创建派生计算
    auto sum = calc([&]() {
        return a() + b();
    });
    
    // 验证初始计算
    EXPECT_EQ(sum.get(), 30);
    
    // 修改源变量，验证自动更新
    a.value(15);
    EXPECT_EQ(sum.get(), 35);
    
    b.value(25);
    EXPECT_EQ(sum.get(), 40);
}

// 测试表达式语法
TEST(ReactionBasicTest, ExprSyntax) {
    using namespace reaction;
    
    auto a = var(5);
    auto b = var(3);
    
    // 使用 expr 创建声明式表达式
    auto result = expr(a * 2 + b);
    
    EXPECT_EQ(result.get(), 13);  // 5 * 2 + 3 = 13
    
    a.value(10);
    EXPECT_EQ(result.get(), 23);  // 10 * 2 + 3 = 23
    
    b.value(7);
    EXPECT_EQ(result.get(), 27);  // 10 * 2 + 7 = 27
}

// 测试响应式动作
TEST(ReactionBasicTest, ActionCallback) {
    using namespace reaction;
    
    auto counter = var(0);
    int sideEffect = 0;
    
    // 创建 action 监听变量变化
    auto monitor = action([&]() {
        sideEffect = counter();
    });
    
    // 验证初始触发
    EXPECT_EQ(sideEffect, 0);
    
    // 修改变量，验证 action 触发
    counter.value(5);
    EXPECT_EQ(sideEffect, 5);
    
    counter.value(10);
    EXPECT_EQ(sideEffect, 10);
}

// 测试复杂的链式依赖
TEST(ReactionBasicTest, ChainedDependencies) {
    using namespace reaction;
    
    auto a = var(2);
    auto b = calc([&]() { return a() * 2; });
    auto c = calc([&]() { return b() + 10; });
    auto d = expr(c * 3);
    
    // 初始值: a=2, b=4, c=14, d=42
    EXPECT_EQ(a.get(), 2);
    EXPECT_EQ(b.get(), 4);
    EXPECT_EQ(c.get(), 14);
    EXPECT_EQ(d.get(), 42);
    
    // 修改 a，验证链式更新
    a.value(5);
    EXPECT_EQ(b.get(), 10);  // 5 * 2
    EXPECT_EQ(c.get(), 20);  // 10 + 10
    EXPECT_EQ(d.get(), 60);  // 20 * 3
}

// 测试字符串操作
TEST(ReactionBasicTest, StringOperations) {
    using namespace reaction;
    
    auto firstName = var(std::string("John"));
    auto lastName = var(std::string("Doe"));
    
    auto fullName = calc([&]() {
        return firstName() + " " + lastName();
    });
    
    EXPECT_EQ(fullName.get(), "John Doe");
    
    firstName.value("Jane");
    EXPECT_EQ(fullName.get(), "Jane Doe");
    
    lastName.value("Smith");
    EXPECT_EQ(fullName.get(), "Jane Smith");
}

// 测试数学运算
TEST(ReactionBasicTest, MathOperations) {
    using namespace reaction;
    
    auto radius = var(5.0);
    
    auto area = calc([&]() {
        return M_PI * radius() * radius();
    });
    
    auto circumference = calc([&]() {
        return 2 * M_PI * radius();
    });
    
    EXPECT_NEAR(area.get(), 78.54, 0.01);
    EXPECT_NEAR(circumference.get(), 31.42, 0.01);
    
    radius.value(10.0);
    EXPECT_NEAR(area.get(), 314.16, 0.01);
    EXPECT_NEAR(circumference.get(), 62.83, 0.01);
}

// 测试参数绑定风格
TEST(ReactionBasicTest, ParameterBinding) {
    using namespace reaction;
    
    auto a = var(10);
    auto b = var(20);
    
    // 使用参数绑定风格（高性能）
    auto product = calc([](auto aa, auto bb) {
        return aa * bb;
    }, a, b);
    
    EXPECT_EQ(product.get(), 200);
    
    a.value(5);
    EXPECT_EQ(product.get(), 100);
    
    b.value(30);
    EXPECT_EQ(product.get(), 150);
}

// 主函数（GTest 会自动提供）
// int main(int argc, char **argv) {
//     ::testing::InitGoogleTest(&argc, argv);
//     return RUN_ALL_TESTS();
// }

