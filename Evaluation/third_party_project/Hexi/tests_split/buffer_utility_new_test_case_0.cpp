
#include <gtest/gtest.h>

// Include function definition (in actual projects, should be included via header file)
#include "buffer_utility_function_implementation_0.hpp"

/**
 * Test Case: src_dest_overlap_start
 *
 * Scenario:
 * - Source and destination regions are identical (same start, same length).
 * Expected:
 * - Overlap is detected (true).
 */
TEST(buffer_utility, src_dest_overlap_start) {
  const bool overlaps = src_dest_overlap_start_impl();
  ASSERT_TRUE(overlaps);
}
