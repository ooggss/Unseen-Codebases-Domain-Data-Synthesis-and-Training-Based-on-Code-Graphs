

#include <gtest/gtest.h>
#include <tuple>

// include implementation
#include "test_thread_safety_function_implementation_3.hpp"

TEST(ThreadSafetyTest, ThreadRegistrationMechanism) {
    std::cout << "=== REACTION_REGISTER_THREAD Mechanism Test ===" << std::endl;

    size_t initialCount;
    size_t afterOperationCount;
    size_t threadCountAfterMulti;
    bool initialSafetyState;

    std::tie(initialCount,
             afterOperationCount,
             threadCountAfterMulti,
             initialSafetyState) =
        runThreadRegistrationMechanismScenario();

    std::cout << "Initial thread count: " << initialCount << std::endl;
    std::cout << "Thread count after operation: " << afterOperationCount << std::endl;
    std::cout << "Thread count after multi-thread: " << threadCountAfterMulti << std::endl;
    std::cout << "Initial thread safety state: "
              << (initialSafetyState ? "Enabled" : "Disabled") << std::endl;

    // Original test had no EXPECTs; this keeps behavior equivalent (no assertions).
    std::cout << "✅ REACTION_REGISTER_THREAD mechanism test passed" << std::endl;
}

