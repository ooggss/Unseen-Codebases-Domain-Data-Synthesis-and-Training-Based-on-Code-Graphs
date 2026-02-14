

#include <gtest/gtest.h>
#include <tuple>

// include implementation
#include "test_thread_safety_function_implementation_4.hpp"

TEST(ThreadSafetyTest, ThreadSafetyVerification) {
    bool raceDetected;
    int readCount;
    int writeCount;
    int tearingCount;

    std::tie(raceDetected, readCount, writeCount, tearingCount) =
        runThreadSafetyVerificationScenario();

    std::cout << "=== Thread Safety Verification Result ===" << std::endl;
    std::cout << "Read operations: " << readCount << std::endl;
    std::cout << "Write operations: " << writeCount << std::endl;
    std::cout << "Tearing detected: " << tearingCount << std::endl;

    if (raceDetected) {
        FAIL() << "Thread safety protection failed! Tearing detected "
               << tearingCount << " times";
    }

    EXPECT_EQ(readCount, 20000);  // 2 readers * 10000
    EXPECT_EQ(writeCount, 10000); // 2 writers * 5000
    EXPECT_EQ(tearingCount, 0);   // no tearing expected
}

