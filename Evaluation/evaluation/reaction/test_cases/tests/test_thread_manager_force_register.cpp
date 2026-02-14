#include <gtest/gtest.h>

#include "test_thread_manager_force_register.hpp"

namespace test_reaction {

/**
 * Test Case: Test multi-thread based safety enabling via registerThread.
 *
 * Test Scenario:
 * - Reset ThreadManager to a clean state.
 * - Call registerThread on the main thread and verify safety is still disabled.
 * - Spawn a worker thread that also calls registerThread.
 * - Verify that thread safety becomes enabled after a second distinct thread is detected.
 */
TEST(reaction, test_thread_manager_force_register) {
  const auto snapshot = test_thread_manager_force_register();

  EXPECT_FALSE(snapshot.safetyBeforeForce);
  EXPECT_FALSE(snapshot.safetyAfterMainForce);
  EXPECT_TRUE(snapshot.safetyAfterWorkerForce);
}

}  // namespace test_reaction


