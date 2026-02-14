
#include <gtest/gtest.h>

// Include function definition (in actual projects, should be included via header file)
#include "buffer_utility_function_implementation_3.hpp"

/**
 * Test Case: src_dest_overlap_between
 *
 * Scenario:
 * - Destination is a 1-byte region starting inside the source buffer region.
 * Expected:
 * - Overlap is detected (true).
 */
TEST(buffer_utility, src_dest_overlap_between) {
  const bool overlaps = src_dest_overlap_between_impl();
  ASSERT_TRUE(overlaps);
}
